#include<LPC214x.H>

int main()
{
	unsigned int i;
	IODIR0=0x000000ff;  //Port0 0-7 as O/P, 8-31 as I/P
	IOSET0=0x000000ff;   //make 0-7 High
	IOCLR0=0x000000ff; //make 0-7 Low
	IOPIN0=0x000000aa;
	SCS=0x02;            //Sel Fast GPIO for Port1
	FIO1MASK=0xff00ffff;   //mask 0-15, 24-31
	FIO1DIR=0x00ff0000;  // 16-23 as O/P
		while(1)
	{
	FIO1CLR=0x00ff0000;  //make 16-23 High
		for(i=0;i<50000;i++){}
	FIO1SET=0x00ff0000;  //make 16-23 Low
			for(i=0;i<50000;i++){}
	}
	return 0;
}
