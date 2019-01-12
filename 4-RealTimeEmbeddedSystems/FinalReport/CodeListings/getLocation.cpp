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