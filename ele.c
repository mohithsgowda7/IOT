#include <lpc214x.h>
#define LED_OFF (IO0SET = 1U << 31)
#define LED_ON (IO0CLR = 1U << 31)
void delay_ms(unsigned int j);
void elevator_run(void);
int main()
{
 IO0DIR |= 1U << 31 | 0XFF << 16; // to set P0.31 & P1.20 to P1.23 as outputs
 IO1DIR |= 1 << 24; // to set P1.24 as output
 LED_ON; // make D7 Led on .. just to indicate the program is running
 elevator_run( );
 while(1);
}
void elevator_run(void)
{
  	int i,val;
	unsigned int counter;
	IO1CLR = 1 << 24; // enable elevator section in the application board : 0 to enable
	IO0CLR = 0X000F0000; //to set the  elevator led for grnd floor
	do{
// clear all the latches *CLR
IO0CLR = 0X00F00000;IO0SET = 0X00F00000; 
	    	//waiting for floor key
		do{
		   counter = (IO1PIN >> 16) & 0X0000000F ; // wait for any lift/elevator key press
		}while(counter == 0x0F);
		if(counter == 0x0e)      val=3;      //1110 - floor 1 key pressed
		else if(counter == 0x0d) val=6;    //1101 - floor 2 key pressed
		else if(counter == 0x0b) val=8;    //1011 - floor 3 key pressed
		else if(counter == 0x07) val=10;  //0111- floor 4 key pressed
		//elevator movement-UP
		for(i=0 ; i<val ; i++)  
		{
			IO0CLR = 0X000F0000;IO0SET = i << 16;
			delay_ms(250);
		}
	    	//elevator movement-DN
		for(i=val-1;i>=0;i--)
		{
			IO0CLR = 0X000F0000;IO0SET = i << 16;
			delay_ms(250);
		}
	} while(1);
}
void delay_ms(unsigned int j){
	unsigned int x,i;
	for(i=0;i<j;i++){
		for(x=0;x<10000;x++);
	}
}