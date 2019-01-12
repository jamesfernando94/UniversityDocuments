
#include "mbed.h"
#include "http_request.h"
#include "network-helper.h"
#include "mbed_mem_trace.h"
#include <string>
#include "C12832.h"
#include "MbedJSONValue.h"
#include <sstream>
 
// LCD
C12832 lcd(D11, D13, D12, D7, D10);
// Joystick Inputs
InterruptIn joy_up(A2);
InterruptIn joy_down(A3);

// Global Variables with inital values
int position = 0;
string ipAddress = "waiting...";
string latitude = "waiting...";
string longitude = "waiting...";
string temprature = "waiting...";
string weatherDescription = "waiting...";
EventQueue queue;

// Constants
const int MAX_POSITIONS = 4;

// Method Declarations
void display_data();
void up();
void down();
void display_ip_address();
void display_location();
void display_temprature();
void display_weather();
void set_ip_address(NetworkInterface *network);
void set_location(NetworkInterface *network);
void set_weather(NetworkInterface *network);
void dump_response(HttpResponse *res);

int main()
{
    Thread eventThread; // Set up thread to add events to
    eventThread.start(callback(&queue, &EventQueue::dispatch_forever)); // add queue to thread
    
    display_data();
    joy_up.rise(queue.event(&up)); // This adds the up function to the queue when the interrupt is called
    joy_down.rise(queue.event(&down)); // This adds the down function to the queue when the interrupt is called
    // Connect to the network with the default networking interface
    // if you use WiFi: see mbed_app.json for the credentials
    NetworkInterface *network = connect_to_default_network_interface();
    if (!network)
    {
        printf("Cannot connect to the network, see serial output\n");
        return 1;
    }

    // Set data values
    set_ip_address(network);
    set_location(network);
    set_weather(network);
    
    // Wait forever note as the interrupts work on a different thread this is fine
    wait(osWaitForever);
}

/**
*   This function displays the correct data depending on the position variable.
*/
void display_data(){
    switch (position){
        case 0:
            display_ip_address();
            break;
        case 1:
            display_location();
            break;
        case 2:
            display_temprature();
            break;
        case 3:
            display_weather();
        default:
            break;
    }
}

/*
*   This function is the up funciton it decrements the position value or goes round if zero
*/
void up()
{
    printf("\n Called Up");
    if (position <= 0)
    {
        position = MAX_POSITIONS - 1;
    }
    else
    {
        position--;
    }
    display_data();
}

/*
*   This function increments the position value up to MAX_POSITIONS
*/
void down()
{
    printf("\n Called Down");
    position++;
    position %= MAX_POSITIONS;
    display_data();
}

/*
*   This function displays the IP Address
*/
void display_ip_address()
{
    lcd.cls();
    lcd.locate(0, 3);
    lcd.printf("IP Address: %s", ipAddress.c_str());
}

/*
*   This function displays the Latitude and logitude
*/
void display_location()
{
    lcd.cls();
    lcd.locate(0, 3);
    lcd.printf("Latitude: %s\n", latitude.c_str());
    lcd.printf("Longitude: %s", longitude.c_str());
}

/*
*   This function displays the temprature
*/
void display_temprature()
{
    lcd.cls();
    lcd.locate(0, 3);
    lcd.printf("Current Temprature: %s", temprature.c_str());
}

/*
* This function displays the wether description
*/
void display_weather(){
    lcd.cls();
    lcd.locate(0, 3);
    lcd.printf("Weather Description: %s", weatherDescription.c_str());
}

/*
*   This function gets the current IP Address and stores it in the ipAddress variable
*/
void set_ip_address(NetworkInterface *network)
{
    HttpRequest *request = new HttpRequest(network, HTTP_GET, "http://api.ipify.org/"); // Setup http Request
    request->set_header("Content-Type", "application/json");
    HttpResponse *response = request->send(); // send off request and store response in response vairable
    dump_response(response);
    ipAddress = response->get_body_as_string(); // get the body of the response which contains the IP Address
    delete request; // also clears out the response
    display_data();
}

/*
*   This function gets the location based on the IP Address and stores it in the latitude and logitude variables
*/
void set_location(NetworkInterface *network){
    MbedJSONValue location;
    string url = "http://api.ip2location.com/?ip=" + ipAddress + "&key=UMJGR0FYSZ&package=WS5&format=json"; // build request url
    HttpRequest *request = new HttpRequest(network, HTTP_GET, url.c_str());// Setup http Request
    request->set_header("Content-Type", "application/json");
    HttpResponse *response = request->send(); // send off request and store response in response vairable
    dump_response(response);
    parse(location, response->get_body_as_string().c_str()); // convert body from JSON string to Json object
    latitude = location["latitude"].get<string>(); // Get latitude from JSON object
    longitude = location["longitude"].get<string>(); // Get longitude from JSON object
    delete request; // also clears out the response
    display_data();
}

/*
*   This function gets the weather information based on the location information and stores it in the global variables
*/
void set_weather(NetworkInterface *network){
    MbedJSONValue weather;
    string url = "http://api.openweathermap.org/data/2.5/weather?lat=" + latitude + "&lon=" + longitude + "&appid=8218d0e6eee9e8b53f74a4a646145ea5&units=metric"; // build request url
    HttpRequest *request = new HttpRequest(network, HTTP_GET, url.c_str()); // Setup http Request
    request->set_header("Content-Type", "application/json");
    HttpResponse *response = request->send(); // send off request and store response in response vairable
    dump_response(response);
    parse(weather, response->get_body_as_string().c_str()); // convert body from JSON string to Json object
    double temp = weather["main"]["temp"].get<double>(); // Get Temprature as doble and store it in tempoary variable
    // Convert double to string and append " C" to the end
    std::ostringstream strs;
    strs << temp;
    strs << " C";
    temprature = strs.str();
    
    weatherDescription = weather["weather"][0]["description"].get<string>(); // Store Weather description in variable
    delete request; // also clears out the response
    display_data();
}

/*
*   This function dumps the HTTPResponse object to the console connected to the debug port
*/
void dump_response(HttpResponse *res)
{
    printf("Status: %d - %s\n", res->get_status_code(), res->get_status_message().c_str());

    printf("Headers:\n");
    for (size_t ix = 0; ix < res->get_headers_length(); ix++)
    {
        printf("\t%s: %s\n", res->get_headers_fields()[ix]->c_str(), res->get_headers_values()[ix]->c_str());
    }
    printf("\nBody (%d bytes):\n\n%s\n", res->get_body_length(), res->get_body_as_string().c_str());
}
