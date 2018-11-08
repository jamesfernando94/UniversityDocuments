/* Program: A simple Timer Activate Tera Term terminal to test.*/
#include "mbed.h"
#include <string>

Timer t; // define Timer with name "t"
Serial pc(USBTX, USBRX);
int main()
{
    for(int i = 0; i <= 10; i++) { // Test 1 to 10 characters
        string str = "";
        for(int j = 0; j < i; j++) { // Add i characters to string str
            str += "a";
        }
        t.reset();
        t.start(); //start the timer
        pc.printf("%s\n", str.c_str());
        t.stop(); //stop the timer
        pc.printf("The time taken for %i characters was %f seconds\n", i, t.read()); //print to pc
    }
}