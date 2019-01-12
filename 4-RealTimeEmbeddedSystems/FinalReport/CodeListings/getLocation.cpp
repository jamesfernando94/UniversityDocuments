char* get_ip_address()
{
        
    HttpRequest* request = new HttpRequest(network, HTTP_GET, "http://api.ipify.org/");
    request->set_header("Content-Type", "application/json");
    HttpResponse* response = request->send(body, strlen(body));
    // if response is NULL, check response->get_error()
    
    pc.printf("status is %d - %s\n", response->get_status_code(), response->get_status_message());
    char* ipAddress = response->get_body_as_string().c_str();
    pc.printf("body is:\n%s\n", ipAddress);
    
    delete request; // also clears out the response
    return ipAddress;
}