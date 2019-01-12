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