#include <lpc214x.h>
#define LED_OFF (IO0SET = 1U << 31)
#define LED_ON (IO0CLR = 1U << 31)
#define PLOCK 0x00000400
void delay_ms(unsigned int j);

int main()
{
 unsigned int  no_of_steps_clk = 200, no_of_steps_aclk = 200;
 IO0DIR |= 1U << 31 | 0x00FF0000 | 1U << 30; // to set P0.16 to P0.23 as o/ps 
 LED_ON; delay_ms(500);LED_OFF; // make D7 Led on .. just indicate the program is running
do{
IO0CLR = 0X000F0000;IO0SET = 0X00010000;delay_ms(5);if(--no_of_steps_clk == 0) break;
IO0CLR = 0X000F0000;IO0SET = 0X00020000;delay_ms(5);if(--no_of_steps_clk == 0) break;
IO0CLR = 0X000F0000;IO0SET = 0X00040000;delay_ms(5);if(--no_of_steps_clk == 0) break;
IO0CLR = 0X000F0000;IO0SET = 0X00080000;delay_ms(5);if(--no_of_steps_clk == 0) break;
}while(1);
do{
IO0CLR = 0X000F0000;IO0SET = 0X00080000;delay_ms(5);if(--no_of_steps_aclk == 0) break;
IO0CLR = 0X000F0000;IO0SET = 0X00040000;delay_ms(5);if(--no_of_steps_aclk == 0) break;
IO0CLR = 0X000F0000;IO0SET = 0X00020000;delay_ms(5);if(--no_of_steps_aclk == 0) break;
IO0CLR = 0X000F0000;IO0SET = 0X00010000;delay_ms(5);if(--no_of_steps_aclk == 0) break;
}while(1);
IO0CLR = 0X00FF0000;
while(1);
}

void delay_ms(unsigned int j)
{
  unsigned int x,i;
  for(i=0;i<j;i++)
   {
      for(x=0; x<10000; x++);    
   }
}
