#include <reg51.h> //Define 8051 Registers
void UART_Init();
void UART_TxChar(char);
void UART_SendString(char *);


void UART_Init()
{
	TMOD = 0x20;    //Timer1, Mode2
	TH1 = 0xFD;     //Baud Rate 9600bps
	SCON = 0x50;	//Serial Mode1, Receive Enable
	TR1 = 1;   	//Timer1 ON
			
}

void UART_TxChar(char Data)
{
	SBUF = Data;  // DATA MOVED  TO SERIAL BUFFER
	while (TI==0);
    TI = 0;
}


	
void UART_SendString(char *str)
{
     int i;
     for(i=0;str[i]!=0;i++)
		{
         UART_TxChar(str[i]);
    }
}


void main()
{
	UART_Init();					/* initialize UART Tx=P3^0 and Rx=P3^1 */
	
	while(1)
	{
		UART_SendString("Hello World!! \n\r");
 }
}
