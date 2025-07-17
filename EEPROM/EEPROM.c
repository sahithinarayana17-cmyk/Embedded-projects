
#include<reg51.h>
#include<stdio.h>
#include<intrins.h>

#define ACK		1
#define NO_ACK	0


unsigned char EData[5];
unsigned char Data;
void InitSerial(void);
void DelayMs(unsigned int);

void WriteI2C(unsigned char);
unsigned char ReadI2C(bit);

void Start(void);
void Stop(void);
void ReadBYTE(unsigned int);
void WriteBYTE(unsigned int);

sbit SCL  =  P2^0;	// connect to SCL pin (Clock)
sbit SDA  =  P2^1;	// connect to SDA pin (Data)


//---------------------------------------
// Main program
//---------------------------------------
void main(void)
{
	 unsigned int i;
	InitSerial();  		// Initialize serial port  
	putchar(0x0C);		// clear hyper terminal
	DelayMs(5);
	WriteBYTE(0x0000);
	WriteI2C('8');		//Write Data's Here
	WriteI2C('0');
	WriteI2C('5');
	WriteI2C('1');
	Stop();	
	DelayMs(10);

	ReadBYTE(0x0000); 
	EData[0] = ReadI2C(NO_ACK);	
	EData[1] = ReadI2C(NO_ACK);	
	EData[2] = ReadI2C(NO_ACK);	
	EData[3] = ReadI2C(NO_ACK);	
			
	
	for(i=0;i<4;i++)
	{
	printf("%c",EData[i]);	// display data    	  */
	DelayMs(100);
	}
while(1);
}

//---------------------------------------
// Initialize serial port
//---------------------------------------
void InitSerial(void)
{
  	SCON = 0x52;    // setup serial port control 
  	TMOD = 0x20;    // hardware (9600 BAUD @11.0592MHZ) 
  	TH1  = 0xFD;    // TH1
	TR1	 = 1;  		// Timer 1 on
}


//-------------------------------
// start I2C
//-------------------------------
void Start(void)
{
    SDA = 1;
	SCL = 1;
	_nop_();_nop_();
	SDA = 0;
	_nop_();_nop_();
	SCL = 0;
	_nop_();_nop_();
}

//-------------------------------
// stop I2C
//-------------------------------
void Stop(void)
{
	SDA = 0;	    	
	_nop_();_nop_();
	SCL = 1;
	_nop_();_nop_();
	SDA = 1;	
}

//-------------------------------
// Write I2C
//-------------------------------
void WriteI2C(unsigned char Data)
{    
 unsigned int i;
	for (i=0;i<8;i++)
	{
        SDA = (Data & 0x80);
		SCL=1;SCL=0;
		Data<<=1;
	}

  	SCL = 1; 
	_nop_();_nop_();
	SCL = 0;

}

//-------------------------------
// Read I2C
//-------------------------------
unsigned char ReadI2C(bit ACK_Bit)
{
	 unsigned int i;
	
    Start();
	WriteI2C(0xA1);
    

    SDA = 1;	
	for (i=0;i<8;i++)
	{
		SCL   = 1;		
		Data<<= 1;
		Data  = (Data | SDA);		
		SCL   = 0;
		_nop_();
	}
    
 	if (ACK_Bit == 1)
	SDA = 0; // Send ACK		
	else		
	SDA = 1; // Send NO ACK				

	_nop_();_nop_();
	SCL = 1;		
	_nop_();_nop_();
	SCL = 0;
	Stop();
	return Data;
}

//-------------------------------
// Read 1 byte form I2C
//-------------------------------
void ReadBYTE(unsigned int Addr)
{
	Start();
	WriteI2C(0xA0);
	WriteI2C((unsigned char)(Addr>>8)&0xFF);
	WriteI2C((unsigned char)Addr&0xFF);
}

//-------------------------------
// Write 1 byte to I2C
//-------------------------------
void WriteBYTE(unsigned int Addr)
{
	Start();
	WriteI2C(0xA0);
	WriteI2C((unsigned char)(Addr>>8)&0xFF);	// send address high
	WriteI2C((unsigned char)Addr&0xFF);			// send address low	
}


//---------------------------------------
// Delay mS function
//---------------------------------------
void DelayMs(unsigned int count) 
{  // mSec Delay 11.0592 Mhz 
    unsigned int i;		       		// Keil v7.5a 
    while(count) 
	{
        i = 110; 
		while(i>0) i--;
        count--;
    }
}

