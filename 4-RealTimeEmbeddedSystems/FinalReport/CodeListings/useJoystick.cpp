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