#include <LPC214X.H>


void send(unsigned char x)
{
U0THR=x;
while(!(U0LSR&(1<<5)));	
 }

void read(unsigned char *p)
{
unsigned char a;

	while( !(*p == 0x00))
	{
   	a= *p;
		send(a);
		p++;
  }
}

int main(void)

{
	// COMMANDS FOR SEND SMS
	unsigned int i=0;
	unsigned char *commanddial="ATD 8608426258;";
	unsigned char *command1= "AT\r\n"; // TESTING FOR SYNCHRONIZATION
	unsigned char *command2= "AT+CMGF=1\r\n";  // CONFIGURING TEXT MODE FOR SMS
	unsigned char *command3= "AT+CMGS=\"8608426258\"\r\n"; // SMS SENDING COMMAND 
	unsigned char *command4= "THIS IS FIRST TRY FOR SENDING SMS"; // BODY OF THE SMS
	unsigned char command5= 0X1A;  // CNTRL-Z FOR SENDING SMS
	PINSEL0=5;   /// SELECTING TX AND RX P0.0---TX  P0.1 ----RX
	U0TER=(1<<7);
	U0LCR= 0x83; /// enble divisor latch
	U0DLL= 47;
	U0DLM= 0;
	U0FDR=(12<<4)|13;
	U0LCR= 0x03; /// disable divisor latch
	//read(commanddial);
	send(0x0a); // enter key
	read(command1);
	send(0x0a); // enter key
	for( i=0; i<5000000;i++)
	{}
	read(command2);
		for( i=0; i<5000000;i++)
	{}
		send(0x0a); // enter key
	read(command3);
		for( i=0; i<5000000;i++)
	{}
		send(0x0a); // enter key
	read(command4);
	send(command5);
		for( i=0; i<5000000;i++)
	{}
	while(1);

}