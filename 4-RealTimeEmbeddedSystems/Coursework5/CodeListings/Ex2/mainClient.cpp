#include "mbed.h"
#include "EthernetInterface.h"
#include "FXOS8700Q.h"
#include <stdio.h>
#include <iostream>


const int PORT = 7;

static const char* SERVER_IP = "192.168.1.101"; //IP of server board
static const char* CLIENT_IP = "192.168.1.102"; //IP of client board
static const char* MASK = "255.255.255.0";      //mask          
static const char* GATEWAY = "192.168.1.1";     //gateway


/*--INITS-------------------------------------------------------------------------------*/
Serial pc(USBTX, USBRX);        //create PC interface
EthernetInterface eth;          //create ethernet
UDPSocket sock;                 //creat Ethernet socket
Endpoint server;                //create endpoint

DigitalOut red(LED_RED);        //debug led
DigitalOut green(LED_GREEN);    //debug led
FXOS8700Q_acc acc( PTE25, PTE24, FXOS8700CQ_SLAVE_ADDR1);


/*--VARIABLES---------------------------------------------------------------------------*/
int n;                  //size of received message
char* recieveBuffer = new char[23];      //create receive buffer
char* sendBuffer = new char[23];  //sample send buffer
std::string inStr;
std::string outStr;


/*--FUNCTION DECLARATIONS---------------------------------------------------------------*/
void init_usb(void);    //initializes pc.printf if required
void init_eth(void);    //initializes Ethernet
void end_eth(void);     //closes Ethernet socket
void printCharArr(char* arr);
int main(void);         //main


/*--FUNCTION DEFINITIONS---------------------------------------------------*****************************************************************************INIT_USB***/
void init_usb(void)
{
    pc.baud(9600);    //baud
    
}   //end init_usb()

/*****************************************************************************INIT_ETH***/
void init_eth(void)
{
    eth.init(CLIENT_IP, MASK, GATEWAY);                                         //set up IP
    eth.connect();                                                              //connect ethernet
    pc.printf("\nCLIENT - Client IP Address is %s\r\n", eth.getIPAddress());    //get client IP address
    
    sock.init();                                                                //initialize socket
    
    server.set_address(SERVER_IP, PORT);                                        //set address of server
    
}   //end init_eth()

/******************************************************************************END_ETH***/
void end_eth(void)
{
    sock.close();       //close socket
    eth.disconnect();   //close Ethernet
    
}   //end end_eth()

void printCharArr(char* arr){
    for(int i = 0; i < sizeof(arr); i++){
        pc.printf("%c", arr[i]);
    }
}

/*********************************************************************************MAIN***/
int main(void)
{
    red = 0;                                                                                //client
    green = 1;
    
    acc.enable();
    float faX, faY;
        
    init_usb();                                                                             //initialize the PC interface
    init_eth();                                                                             //initialize the Ethernet connection

    while(true)                                                                             //repeat forever
    {
        acc.getX(&faX);
        acc.getY(&faY);
        sprintf(sendBuffer, "X:'% 5.3f' Y:'% 5.3f'\0", faX, faY);
        pc.printf("\nCLIENT - Sending");
        printCharArr(sendBuffer); 
        pc.printf(" to server %s\r\n",  SERVER_IP);       //print message to send
        sock.sendTo(server, sendBuffer, sizeof(sendBuffer)+1);                                      //send message
        pc.printf("CLIENT - Waiting for UDP packet...\r\n");                                //wait for message
        n = sock.receiveFrom(server, recieveBuffer, 23);                         //receive message from server
        pc.printf("CLIENT - Received ");
        printCharArr(recieveBuffer);
        pc.printf(" from server %s\r\n", SERVER_IP);    //print message received
        
        
        wait(1);                                                                            //wait 1 second
    }
    
}   //end main()
