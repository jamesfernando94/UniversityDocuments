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
