#include<LPC214x.h> 

int main()
{
	int present,previous=0;
	PINSEL1 = PINSEL1 | (1<<10); //CH5 (P0.21)
	IO0DIR = IO0DIR | (1<<21); //P0.21 (PWM5) O/P, P0.6 switch I/P
	PWMPCR = PWMPCR | (1<<13); //PWM5 SGL EDG,PWM 5 ENABLED
	PWMLER = 0X00;
	PWMMCR = 0X00000002; //RESET COUNTER WHEN MATCH0
	PWMPR =  99; //PWM CLK = PCLK/(99+1) = 150 KHz
	PWMPC = 0X00000000;
	PWMTC = 0X00000000;
	PWMMR0 = 1000;       //PWM O/P = PWM CLK / 1000 = 150 KHz / 1000 = 150 Hz (6.67 ms)
	PWMMR5 = 100;
	PWMTCR =0X09; //ENABLE COUNTER & PWM MODE
	previous=IO0PIN & (1<<6);
	while(1)
		{
			present=IO0PIN & (1<<6);
				
		if(previous!=present)
		{
			PWMTCR ^=0X09; //DISABLE PWM 
			if(present!=0)
			{
			PWMMR5 = 900;    //High DUTY CYCLE (High Speed)
		  }
			else
			{
			PWMMR5 = 300;     //Low DUTY CYCLE (Low Speed)
		  }
			PWMTCR ^=0X09; //ENABLE PWM 
			previous=present;
		}
	}
		
	return 0;
}
