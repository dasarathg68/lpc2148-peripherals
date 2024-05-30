#include<LPC214x.H>

unsigned int width,i=0;
unsigned int a,echo[2],flag=0;

void EINT1_isr (void) __irq  //TMR1 MATCH INT RATE 100ms*10(PS) = 1000ms (1SEC) = 1HZ  
{
	echo[i] = T0TC;          /* TC0 & PS Enable */
	EXTINT  = 2;    /* Clear Interrupt Flag */
	EXTPOLAR ^= 0x02;     //Falling edge for EINT1
	i++;     //edge count
	VICVectAddr = 0;    //Acknowledge Interrupt 
}

int main()
{
	IO0DIR |= (1<<12);        //P0.3 as I/P for EXINT1 (P0.3), P0.12 AS o/p for trigger
	IODIR1 |= (0xFF<<16);  //P1.16- P1.23 AS O/P (LEDs)	
	IO0CLR = (1<<12);   //Make trigger o/p pin Low (Initial state)
	PINSEL0 = 0X000000C0; //P0.3 AS EINT1
	
	/* Setup Timer Counter 1: Periodic Timer with Interrupt at DATA_FREQ Rate for 10us Trigger pulse*/
  T1MR0 = 150;          /* TC1 Match Value 0 for 10us trigger pulse*/
	T1MCR = 5;                 /* SET Int Flag on TC match with MR0 or MR1, reset on MR1 */
	T1EMR =0X00; /*Do nothing on match*/
	
		/* Setup Timer Counter 0:To measure Echo pulse from Ultrosonic sensor*/
	T0CTCR = 0X00;  //SEL TIMER MODE (PCLK as Timer I/P)
	T0MR0 = 80000;  /* TC0 Match Value based on Max distance of object to be detected*/ 
  T0PR = 0;  //CNT INCREMENT FOR EVERY PR+1  
	T0MCR = 1;                 /* SET Int Flag on TC match with MR0 or MR1, reset on MR1 */
	EXTMODE = 0x02;  //Edge mode for EINT1
	EXTPOLAR = 0x02;     //Rising edge for EINT1
	EXTINT  = 2;    /* Clear Interrupt Flag */
	
	//Setup EINT1 Interrupt 
  VICVectAddr2 = (unsigned long)EINT1_isr;    // EINT1 Interrupt -> Vector 2 
	VICVectCntl2 = 0x20 | 15;             // EINT1 Interrupt -> IRQ Slot 2 
	VICIntEnable = (1 << 15);// | (1<<4);     // Enable EXT1 Interrupt 
//LED OFF if No object present within 1 meter
	IO1PIN = 0; //Turn OFF LEDs in P1.16-P1.23
while(1)
{
	
	i=0;
	T1TC = 0;       //Initailal count as 0
	T1TCR = 1;        /* TC1 Enable */
	T0TC = 0;  //Initial cnt =0
	T0TCR = 1;          /* TC0 & PS Enable */
	IO0SET = (1<<12);   //Make Trigger o/p pin High
	while(!(T1IR&1));   //wait until Timer1 match Int set (end of delay for trigger pulse)
	IO0CLR = (1<<12);   //Make trigger o/p pin Low
	T1IR|=1;   //clear MR0 Int flag
	while((i<2) && (!(T0IR&1))); //wait till echo detected or timeout happens       
	if(i==2)  //if echo pulse detected by ExtINT
{
	//IO1PIN = (1<<16);
	T1TCR = 0;       //T1 disable
	T0TCR = 0;       //T0 disable
//	VICIntEnClr = (1<<15); // Disable EXT1 Interrupt
	width = echo[1] - echo[0];	
	if(width<5000)
	{
	IO1PIN = (1<<16);  //Turn ON LEDs in P1.16-P1.23
	}
	else if(width<10000)
	{
	IO1PIN = (3<<16);  //Turn ON LEDs in P1.16-P1.23
	}
	else if(width<15000)
	{
	IO1PIN = (7<<16);  //Turn ON LEDs in P1.16-P1.23
	}
	else if(width<30000)
	{
	IO1PIN = (0xF<<16);  //Turn ON LEDs in P1.16-P1.23
	}
}
else
{
	T0IR|=1;   //clear MR0 Int flag
	IO1PIN = (1<<23);  //Turn ON LEDs in P1.16-P1.23
}
}
	return 0;
}
