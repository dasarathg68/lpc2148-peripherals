//common cathode <A>   <B>    . . .   <G>    <DP> 
//common cathode P0.23 P0.22  . . .  P0.17  P0.16 


#include<LPC214x.H>
unsigned char disp[4] = {0xfc,0x60,0xda,0xf2};
unsigned char i=0;
unsigned int a;

int main()
{
IO1DIR=(0XFF<<16);   //To configure P1.16:23 as op
PINSEL1 = 0X00003000;  //SET P0.22 AS MATCH0.0(TIMER0)
T0PC = 0X00000000;
T0PR = 0X000002;//3E8;  //CNT INCREMENT FOR EVERY 1000 PCLK
T0TC = 0X00000000;
T0CTCR = 0X00; 	    //(8-BIT REG) TIMER MODE
T0MCR = 0X0003;  //set Mat0 int flag & RESET TC WHEN MR0 MATCHES	
T0MR0 = 0X00003A98;     //1500 CYCLES WITH PS=1:1000	[[15MHZ/(15000*1000)]=1 HZ]
T0EMR = 0X0030; 	 //Toggle on match
T0TCR = 0X01;  //(8-BIT REG)	CNTR & PRESCALAR ENABLED
while(1)
{	
	while(!(T0IR&1));	//wait for Mat0 int flag
	T0IR = T0IR | 1;		   // clr Mat0 int flag
	
	if(i==8)
		i=0;
	//IO1PIN = ((1<<i) <<16);	 //to drive LEDs
	IO1PIN = (disp[i] <<16);	 //to drive 7-seg display
	i++;
	
	
}
	return 0;
   
}


