/*--INCLUDES----------------------------------------------------------------------------*/
#include "mbed.h"
#include "EthernetInterface.h"
#include "FXOS8700Q.h"
#include <stdio.h>
#include <iostream>

/*--CONSTANTS---------------------------------------------------------------------------*/
const int PORT = 7;                             //arbitrary port

static const char* SERVER_IP = "192.168.1.101"; //IP of server board
static const char* MASK = "255.255.255.0";      //mask
static const char* GATEWAY = "192.168.1.1";     //gateway


/*--INITS-------------------------------------------------------------------------------*/
Serial pc(USBTX, USBRX);        //create PC interface
EthernetInterface eth;          //create ethernet
UDPSocket server;               //creat server
Endpoint client;                //create endpoint
FXOS8700Q_acc acc( PTE25, PTE24, FXOS8700CQ_SLAVE_ADDR1);


DigitalOut red(LED_RED);        //debug led
DigitalOut green(LED_GREEN);    //debug led


/*--VARIABLES---------------------------------------------------------------------------*/
int n;                  //size of received message
char* recieveBuffer;    //Receive Buffer
char* sendBuffer;       //Send Buffer
std::string inStr;
std::string outStr;
float faX, faY;

/*--FUNCTION DECLARATIONS---------------------------------------------------------------*/
void init_usb(void);    //initializes pc.printf if required
void init_eth(void);    //initializes Ethernet
void receive(void);     //receives packets
void printCharArr(char* arr);
int main(void);         //main


/*--FUNCTION DEFINITIONS----------------------------------------------------------------*/

/*****************************************************************************INIT_USB***/
void init_usb(void)
{
    pc.baud(9600);    //baud
    
}   //end init_usb()

/*****************************************************************************INIT_ETH***/
void init_eth(void)
{
    eth.init(SERVER_IP, MASK, GATEWAY);                                         //set up IP
    eth.connect();                                                              //connect ethernet
    pc.printf("\nSERVER - Server IP Address is %s\r\n", eth.getIPAddress());    //get server IP address;
    
    server.bind(PORT);                                                          //bind server
        
}   //end init_eth()

/******************************************************************************RECEIVE***/
void receive(void)
{

    
    pc.printf("\nSERVER - Waiting for UDP packet...\r\n");                                      //wait for packet
    server.receiveFrom(client, recieveBuffer, 23);                                   //receive message from client
    pc.printf("SERVER - Received '");
    printCharArr(recieveBuffer);
    pc.printf("' from client %s\r\n", client.get_address());   //print message and client
    
    acc.getX(&faX);
    acc.getY(&faY);
    sprintf(sendBuffer, "X:'% 5.3f' Y:'% 5.3f'\0", faX, faY);
    pc.printf("SERVER - Sending '");
    printCharArr(sendBuffer);
    pc.printf("' back to client %s\r\n", client.get_address()); //print sending back
    server.sendTo(client, sendBuffer, sizeof(sendBuffer)+1);                                                          //send message
}   //end receive()

void printCharArr(char* arr){
    for(int i = 0; i < sizeof(arr); i++){
        pc.printf("%c", arr[i]);
    }
}

/*********************************************************************************MAIN***/
int main(void)
{
    red = 1;
    green = 0;      //server
    
    init_usb();     //initialize the PC interface
    init_eth();     //initialize the Ethernet connection
    acc.enable();

    while (true)    //repeat forever
    {
        receive();  //wait for message
    }

}   //end main()
