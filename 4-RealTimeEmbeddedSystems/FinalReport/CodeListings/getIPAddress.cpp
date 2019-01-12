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