#include<LPC214x.H>

void EINT1_isr (void) __irq  
{
	EXTINT  = 2;    /* Clear Interrupt Flag */
	VICVectAddr = 0;    //Acknowledge Interrupt 
	IO1PIN  = IO1PIN |(0xFF<<16);  //Turn ON LEDs
}


int main()
{
	IO0DIR = 0;        //P0 as I/P for EXINT1 (P0.14)
IO1DIR |= (0xFF<<16);  //P1.16- P1.23 AS O/P (LEDs)	
 PINSEL0 |= (2<<28); //PO.14 AS EINT1
	EXTMODE = 0x00;  //Level sensitive mode for EINT1
	EXTPOLAR = 0x02;     //High Level trigger for EINT1
	//Setup EINT0 Interrupt 
  VICVectAddr2 = (unsigned long)EINT1_isr;    // EINT1 Interrupt -> Vector 2 
  VICVectCntl2 = 0x20 | 15;             // EINT1 Interrupt -> IRQ Slot 2 
  VICIntEnable = (1 << 15);                    // Enable EXT1 Interrupt 
	
	while(1)
	{
		IO1PIN  = IO1PIN &(~(0xFF<<16));  //Turn OFF LEDs
	}

	return 0;
   
}


