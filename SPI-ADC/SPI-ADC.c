
#include<reg52.h>
#include<stdio.h>

sbit ADC_CS 	=  P2^4;
sbit ADC_CLK 	=  P2^5;
sbit ADC_DO 	=  P2^6;
sbit ADC_DI 	=  P2^7;


void InitSerial(void);
void write_adc_byte(char data_byte);
unsigned int ReadADC(unsigned char channel);
void DelayMs(unsigned int count);

//---------------------------------------
// Initialize serial port
//---------------------------------------
void InitSerial(void)
{
  	SCON = 0x52;    // setup serial port control 
  	TMOD = 0x20;    // hardware (9600 BAUD @11.05592MHZ) 
  	TH1  = 0xFD;    // TH1
	  TR1	 = 1;  		// Timer 1 on
}


//---------------------------------------
// read analog from ADC
// Single end mode(2 channel)
//---------------------------------------
unsigned int ReadADC(unsigned char channel)
{
	   unsigned char i,k;
	   unsigned int AdcResult;  // 12 bit
	
	   ADC_CS=0;  						// Active chip select
     k++;								    // Delay about 1 uS
		 ADC_CLK=0; 						// make clock low first   
	   k++;k++;	
	   channel = channel? 0xA0 : 0xD0;	//Refer Datasheet of MCP3202 - in Single Mode for Independent Channel Processing
	   k++;k++;  						// delay about 2 uS

	   /*--- write command 4 bit ----------*/
	   for(i=0; i< 4;i++) 
	   {
	      ADC_DI = (channel & 0x80) != 0;
			 //ADC_DI = (channel & 0x80);
	      channel<<=1;
	      ADC_CLK=1;
	      k++;k++;					// delay about 2 uS
	      ADC_CLK=0;
	   }
	
	   k++;k++;  					// delay about 2 uS
	   ADC_CLK=1;
	   k++;k++;  					// delay about 2 uS
	   ADC_CLK=0;
	   k++;k++;  					// delay about 2 uS 
	
	   /* --- read ADC result 12 bit -------- */
	   AdcResult=0;
	   for(i=0;i<12;i++) 
	   {
		      ADC_CLK=1;
		      k++;k++;  			/// delay about 2 uS 
		      AdcResult<<=1;
			  AdcResult=AdcResult | (ADC_DO & 0x01);	       
		   ADC_CLK=0;
		      k++;k++;  			/// delay about 2 uS
	   }
	   ADC_CS=1;
	   return(AdcResult);	
}


//---------------------------------------
// Main program
//---------------------------------------
void main(void)
{
	unsigned int CH0, CH1;
	InitSerial();  		// Initialize serial port
	putchar(0x0C);  // clear Hyper terminal
	while(1)
	{									   	    
		CH0	=	ReadADC (0);
		printf("Ch 0 : %4d  \n\r", CH0);
	}
}



