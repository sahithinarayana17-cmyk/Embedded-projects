#include<reg51.h>

void uart_init();
void uart_txchar(char);
void uart_sendstring(char *);
char uart_rxchar()

void uart_init()
{
	TMOD = 0x20; // timer 1, mode 2
	TH1 = 0xFD;  // 9600
	SCON= 0x50;
	TR1=1;

}

void uart_txchar(char Data)
{
	    SBUF = Data;
      while(TI == 0);
	    TI=0;

}

char uart_rxchar()
{
	char data1;
	while(RI=0);
	RI =0;
	data1 = SBUF;
	return(data1);
}

//void uart_sendstring(char *str)
//{
//	int i;
//	for (i=0;str[i]!=0;i++)
//	{
//		uart_txchar(str[i]);
//	}
//}

void main()
{
	char datain;
	uart_init();
	while(1)
	{
		datain=uart_rxchar();
		uart_txchar(datain);
	}
}