
#include <lpc214x.h>

unsigned char cmp,O,K,R,I,N,G,y=0;

unsigned int i;

void putkey(unsigned char TD)	/* Send the character to UART */  
{
  while(!(U1LSR & 0x20));		//wait for Transmitter empty
  U1THR = TD;   //transmit a character
}


unsigned char getkey()	/* Receive the character from UART */  
{
	unsigned char RD;
  while(!(U1LSR & 0x01));		//wait for Receiver data
  return (RD = U1RBR);   //Read the received character
}


void init_serial (void)  {               	/* Initialize Serial Interface       */
  PINSEL0 = 5<<16 ;                  	        /* Enable RxD1 and TxD1              */
  U1LCR = 0x83;                          	/* DLAB = 1 (Enable access to UART registers), 8 bits, no Parity, 1 Stop bit     */
  U1DLL = 97;                            	/* 9600 Baud Rate @ 15MHz VPB Clock  */
	U1DLM = 0;
  U1LCR = 0x03;                          	/* DLAB = 0 (Disable access to UART registers)  */
}

int main()
{
IO1DIR |= (0xFF<<16);  //P1.16- P1.23 AS O/P (LEDs)	
init_serial();
	
	putkey('A');   //Send AT command to GSM to check communication 
	putkey('T');
	putkey('\r');
	
	cmp=0;
	do{
	O = getkey();
	if(O == 'O')            //check for "OK" to CONFIRM CONNECTIVITY
	{	y++; }
	}while(y==0);
	
	y=0;
K = getkey();
	if(K == 'K') 
	{
do
	{
		R = getkey();
	if(R == 'R')            //check for "RING" to identify incoming call
	{	y++; }
}while(y==0);

I = getkey();
N = getkey();
G = getkey();
if((I == 'I')&& (N == 'N') && (G == 'G'))
	{	
while(1)
{
	IO1PIN  = IO1PIN ^ (0xFF<<16);  //Blink LEDs if incoming call is detected
	for(i=0;i<0X000FFFF8;i++);
}
}
}
return 0;
}