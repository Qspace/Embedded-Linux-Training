#include<wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

void process_led_control(int ledNum, int value)
{
    switch(ledNum)
    {   
        case 1:
            if(value == 1)
            {
                digitalWrite(25,HIGH);
            }
            else
            {
                digitalWrite(25,LOW);
            }
            
        break;
    }
}
int main(int argc, char** argv){
    printf("This Application controls the USER LED3\n");
	printf("arg[1] is led num, arg[2] is value on/off \n");
	wiringPiSetup();
    pinMode(25,OUTPUT);
    if ( argc != 3 ) /* argc should be 3 for correct execution */ 
    {
        printf("Invalid arg format \n");
    }
    else
    {
        /* argc is valid , lets check argv */
		int ledNum = atoi(argv[1]);
		/* Converting argv[2] which is a brightness value in to integer */
		int value = atoi(argv[2]);
		process_led_control(ledNum,value);
    }
	return 0;

}
