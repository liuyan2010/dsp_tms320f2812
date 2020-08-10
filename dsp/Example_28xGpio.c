#include "DSP28_Device.h"
#include "DSP28_Globalprototypes.h"

// Prototype statements for functions found within this file.
// interrupt void ISRTimer2(void);
void delay_loop(void);
void Gpio_select(void);

unsigned int var1 = 0;
unsigned int var2 = 0;
unsigned int var3 = 0;
unsigned int var4 = 0;
unsigned int var5 = 0;

/*
1，init system
2, disabled interrupt
3, init pie register to default status. pie = irq for gpio
4, set gpio status : MUX, dir, QUAL, data

QUAL: 输入限定寄存器，
	意为对于输入信号进行了采样，以便滤除掉不必要的非人为意愿的输入
*/
void main(void)
{
	int kk=0;

	//init
	InitSysCtrl();

	// Disable and clear all CPU interrupts:
	DINT;
	IER = 0x0000;	
	IFR = 0x0000;

	// Initialize Pie Control Registers To Default State:
	InitPieCtrl();

	InitPieVectTable();	
	

	// Run GPIO test
	var1= 0x0000;		// sets GPIO Muxs as I/Os
	var2= 0xFFFF;		// sets GPIO DIR as outputs
	var3= 0x0000;		// sets the Input qualifier values
	
	Gpio_select();	
	// Toggle I/Os  using DATA register for ever
	while(1)
	{    
		GpioDataRegs.GPADAT.all    =0xAAAA;   
		GpioDataRegs.GPBDAT.all    =0xAAAA;     
		GpioDataRegs.GPDDAT.all    =0x0022;    
		GpioDataRegs.GPEDAT.all    =0x0002; 
		GpioDataRegs.GPFDAT.all    =0xAAAA;    
		GpioDataRegs.GPGDAT.all    =0x0020; 
		for(kk=0; kk<100; kk++)	   			  
	    delay_loop();
	    
	    GpioDataRegs.GPADAT.all    =0x5555;     			
		GpioDataRegs.GPBDAT.all    =0x5555;     
		GpioDataRegs.GPDDAT.all    =0x0041;    // Four I/Os only
		GpioDataRegs.GPEDAT.all    =0x0005;    // ThreeI/Os only
		GpioDataRegs.GPFDAT.all    =0x5555;    
		GpioDataRegs.GPGDAT.all    =0x0010;    // Two  I/Os only
		for(kk=0; kk<100; kk++)
	    	delay_loop();	
    }
	
} 	

void delay_loop()
{
    short i;
    for (i = 0; i < 10000; i++) {}
}

void Gpio_select(void)
{
	 EALLOW;
	 
	GpioMuxRegs.GPAMUX.all=var1;
    GpioMuxRegs.GPBMUX.all=var1;   
    GpioMuxRegs.GPDMUX.all=var1;
    GpioMuxRegs.GPFMUX.all=var1;		 
    GpioMuxRegs.GPEMUX.all=var1; 
    GpioMuxRegs.GPGMUX.all=var1;
										
    GpioMuxRegs.GPADIR.all=var2;		// GPIO PORTs  as output
    GpioMuxRegs.GPBDIR.all=var2;   		// GPIO DIR select GPIOs as output 
    GpioMuxRegs.GPDDIR.all=var2;
    GpioMuxRegs.GPEDIR.all=var2;		
    GpioMuxRegs.GPFDIR.all=var2; 
    GpioMuxRegs.GPGDIR.all=var2;

    GpioMuxRegs.GPAQUAL.all=var3;  		// Set GPIO input qualifier values
    GpioMuxRegs.GPBQUAL.all=var3;   
    GpioMuxRegs.GPDQUAL.all=var3;
    GpioMuxRegs.GPEQUAL.all=var3;
 
    EDIS;
     
}     
//===========================================================================
// No more.
//===========================================================================

