#include<reg51.h>
#define sw P0
	#define led  P2
	
	void main()
	{
		P0=0xff;  // just to declare input port
		P2=0x00;  // output
		while(1)
		{
			led=sw;  // whatever the switch value is there comes to the led
		}			
	}