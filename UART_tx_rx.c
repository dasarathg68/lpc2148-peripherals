
#include <lpc214x.h>
void putkey(int TD)	/* Send the character to UART */  
{
  while(!(U0LSR & 0x20));		//wait for Transmitter empty
  U0THR = TD;   //transmit
}


int getkey()	/* Receive the character from UART */  
{
	int RD;
  while(!(U0LSR & 0x01));		//wait for Receiver data
  return (RD = U0RBR);   //receive
}


void init_serial (void)  {               	/* Initialize Serial Interface       */
  PINSEL0 = 5 ;                  	        /* Enable RxD0 and TxD0              */
  U0LCR = 0x83;                          	/* 8 bits, no Parity, 1 Stop bit     */
  U0DLL = 97;                            	/* 9600 Baud Rate @ 15MHz VPB Clock  */
	U0DLM = 0;
  U0LCR = 0x03;                          	/* DLAB = 0                          */
}

int main()
{
	int i, RD0;
init_serial();
while(1)
{
for(i=0;i<10;i++)
	{
	RD0 = getkey();  //RECEIVES A CHARACTER
	putkey(RD0);     //TRANSMIT A CHARACTER
	}
putkey('\n');  //new line
putkey(0x0d);   // Carriage Return(CR),home
}
return 0;
}