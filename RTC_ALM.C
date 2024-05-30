#include<LPC214x.H>

int i;

int main()
{
IODIR1 |= (0xFF<<16);  //P1.16- P1.23 AS O/P (LEDs)	

	
	CCR = 0X00;  //DISTABLE TIME REGs TO INIALIZE
	
//INITIAL CLOCK TIME	
SEC = 0;
MIN = 27;
HOUR = 14;
DOM = 29;
DOW = 3;
DOY =	273;
MONTH = 9;
YEAR = 2021;
	
//ALARM TIME	
ALSEC = 2;
ALMIN = 27;
ALHOUR = 14;
ALDOM = 8;
ALDOW = 4;
ALDOY =	36;
ALMON = 2;
ALYEAR = 2015;
	
AMR = 0XF8; //(MASK) DOM, DOY, MONTH

//USING PRESCALAR (CLK DIVIDER) TO OBTAIN REFENCE CLK = 32.768KHZ FROM 60MHZ-PCLK 
PREINT = 0X1C8;   // (PCLK/32768) - 1
PREFRAC = 0X61C0;       //  [PCLK - ((PREINT+1)*32768)]

CIIR = 0x00; //Disable all counter increment interrupts

CCR = 0X01;  //ENABLE TIME REGs, CLK FROM PRESCALAR (0X11 FOR EXTERNAL 32KHZ OSC IS USED) 
while(!(ILR & 2));                   //Clear ALARM Interrupt Flag 
	
		IOPIN1 |= (0xFF<<16);  //TOGGLE LEDs EVERY 1SEC 
		ILR |= 2;                   //lear ALARM Interrupt Flag 
	
while(1)
{
	i++;
}

	return 0;
   
}


