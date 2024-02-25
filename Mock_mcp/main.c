#include "Lpspi.h"
#include "Clock.h"
#include "Port.h"
#include "Gpio.h"
#include "Systick.h"
#include "Nvic.h"
#include "Led_declare.h"
#include "Lpuart.h"

typedef struct
{
	unsigned int second;
	unsigned int minute;
	unsigned int hour;
}Clock;

typedef struct
{
	unsigned int day;
	unsigned int month;	
	unsigned int year;	
}Date;

/*** DECLARE FUNCTION ***/
void MAX7219_Init(void);										// initialize SPI communication with MAX7219
void systick_clock_init(void); 							// initialize systick
void SysTick_Handler(void);									// interrupt systick
void button_init(void);											// button 1+2
void PORTC_IRQHandler (void);								// interrupt button 1+2
void Uart1_init(void);											// initialize Uart1
void LPUART1_RxTx_IRQHandler(void);   			// interrupt Uart1
unsigned char LPUART1_receive_char(void);		// receives string by uart		
void set_time_uart(unsigned char * str);   	// set time from string received by uart

//function of program
void Lpspi1_Transmit(unsigned short TXbuffer); 
void display_time(Clock clock);	
void display_date(Date date);

/*** DECLARE VARIABLE ***/
//PCC//
static Pcc_ConfigType PCC_PORTB; 			// LPSPI
static Scg_Firc_ConfigType FIRC_cf; 	// LPSPI
static Pcc_ConfigType PCC_LPSPI1; 		// LPSPI
static Pcc_ConfigType PCC_PORTC; 			// Button 1 + Button 2
static Pcc_ConfigType PCC_LPUART1; 		// LPUART1

//PORT//
static Port_ConfigType PORTB_PCR17 ; 	// LPSPI
static Port_ConfigType PORTB_PCR16 ; 	// LPSPI
static Port_ConfigType PORTB_PCR15 ; 	// LPSPI
static Port_ConfigType PORTB_PCR14 ; 	// LPSPI
static Port_ConfigType PORTC_PCR6 ; 	// TX
static Port_ConfigType PORTC_PCR7 ; 	// RX
static Port_ConfigType PORTC_PCR12 ; 	// button1
static Port_ConfigType PORTC_PCR13 ; 	// button2

//GPIO//
static Gpio_ConfigType GPIOC_PCR12;		//button1
static Gpio_ConfigType GPIOC_PCR13;		//button2

// LSPI//
static Lpspi_ConfigType Lpspi1_config; 
static Lpspi_InitType Lpspi1_init;		

//SYSICK//
static Systick_ConfigType systick_config;

//UART//
static Lpuart_ConfigType Lpuart1_config;
static LPUART_InitType Init_config;

//program variable//
static unsigned char count;											// how many time for systick count to 1s 
static Clock clock_counter; 										// clock
static Date date_counter; 											// date
static char mode_display = 1;										// identify to display time or date (1 for time / 0 for date)
static char on_display = 1;											// identify to display turn on or off (1 for on / 0 for off)
static unsigned char rec_str[30] = "0";								// string received by uart
static char btn1_value = 0; 										// read value of button 1
static char btn2_value = 0; 										// read value of button 2

static unsigned char index_uart =0;
int main(void)
{		
		//set start time;
		clock_counter.second = 0;
		clock_counter.minute = 0;
		clock_counter.hour = 0;
	
		//set start day;
		date_counter.day = 1;
		date_counter.month = 1;
		date_counter.year = 1971;	
		
		// init hardware
		button_init();
		MAX7219_Init();		
    systick_clock_init();
		NVIC_EnableInterrupt(LPUART1_RxTx_IRQn);
		NVIC_EnableInterrupt(PORTC_IRQn);	
		Uart1_init();
		NVIC_SetPriority(LPUART1_RxTx_IRQn,1);
	
		// send start value;
		display_time(clock_counter);
    while(1)
    {		
			// read value of button 1 and 2
			btn1_value = GPIO_ReadFromInputPin(GPIOC,12);
			btn2_value = GPIO_ReadFromInputPin(GPIOC,13);
			
			if(btn1_value == 1)
			{
				if(mode_display ==  1)
				{
					mode_display = 0; // display date
				}
				else
				{
					mode_display = 1; // display time
				}		
			}
			
			if (btn2_value == 1) 
			{
				if(on_display ==  1) 
				{
					Lpspi1_Transmit(OFF_display); // turn off display
					on_display = 0; 
				}
				else
				{
					Lpspi1_Transmit(ON_display); // turn on display
					on_display = 1; 
				}		
			}
    } 		
}

void LPUART1_RxTx_IRQHandler(void)
{			
	rec_str[index_uart] = (unsigned char)LPUART1->DATA;	
	index_uart++;
	// if recieve enough 14 char, update date and time 
	if(index_uart == 14)
	{
		index_uart=0;
		set_time_uart(rec_str);
	}
}
void set_time_uart(unsigned char * str)
{	
	// trans revieced uart data form char into uint 
	unsigned int hour_uart 	= (str[0]-'0') *10 + (str[1]-'0') ;	 	
	unsigned int minute_uart = (str[2]-'0') *10 + (str[3]-'0') ;
	unsigned int second_uart = (str[4]-'0') *10 + (str[5]-'0') ;
	unsigned int day_uart 	  = (str[6]-'0') *10 + (str[7]-'0') ;
	unsigned int month_uart  = (str[8]-'0') *10 + (str[9]-'0') ;
	unsigned int year_uart   = (str[10]-'0') *1000 + (str[11]-'0') *100 + (str[12]-'0') *10 + (str[13]-'0') ;  
	
	// update time
	clock_counter.hour = hour_uart;
	clock_counter.minute = minute_uart;
	clock_counter.second = second_uart;
	
	// update date
	date_counter.day = day_uart;
	date_counter.month = month_uart;
	date_counter.year = year_uart;	
	
	// send time and date updated to display
	display_time(clock_counter);	
}

void SysTick_Handler(void)
{	
	while(SYST_CSR &(1u<<16));
	count++;	
	// update time and date
	if (count >= 10)
	{
		count = 0;
		clock_counter.second++;
		if(clock_counter.second >=60)
		{
			clock_counter.second = 0;
			clock_counter.minute++;
			if(clock_counter.minute >= 60)
			{
				clock_counter.minute = 0;
				clock_counter.hour ++;
				if(clock_counter.hour >=24)
				{
					clock_counter.hour = 0;
					date_counter.day++;
					if(date_counter.day >= 30)
					{
						date_counter.day = 0;
						date_counter.month++;
						if(date_counter.month >= 12)
						{
							date_counter.month = 0;
							date_counter.year++;	
						}		
					}						
				}
			}
		}
		// display the time or date
		if (mode_display ==1)
		{
			display_time(clock_counter);		
		}		
		else
		{
			 display_date(date_counter);
		}
	}	
}
 
void Lpspi1_Transmit(unsigned short TXbuffer)
{
		while(!(LPSPI1->SR &(0x01)));
		LPSPI1->TDR = TXbuffer;
}
void display_time(Clock clock)		
{
		unsigned int hour_ten = clock.hour / 10;
		unsigned int hour_one = clock.hour % 10;
		unsigned int minute_ten = clock.minute / 10;
		unsigned int minute_one = clock.minute % 10;
		unsigned int second_ten = clock.second / 10;
		unsigned int second_one = clock.second % 10;	
		
		Lpspi1_Transmit(LED8[hour_ten]); 			// 2
		Lpspi1_Transmit(LED7[hour_one]); 			// 4
		Lpspi1_Transmit(LED6_under);					// -
		Lpspi1_Transmit(LED5[minute_ten]);		// 6
		Lpspi1_Transmit(LED4[minute_one]);		// 0
		Lpspi1_Transmit(LED3_under);					// -
		Lpspi1_Transmit(LED2[second_ten]);		// 6
		Lpspi1_Transmit(LED1[second_one]);		// 0
	
}
void display_date(Date date)		
{		
		unsigned int day_ten = date.day / 10;
		unsigned int day_one = date.day % 10;
		unsigned int month_ten = date.month / 10;
		unsigned int month_one = date.month % 10;
		unsigned int year_thousand = date.year / 1000;
		unsigned int year_hundred = date.year % 1000 / 100 ;
		unsigned int year_ten = date.year % 100 / 10;
		unsigned int year_one = date.year % 10;

		Lpspi1_Transmit(LED8[day_ten]); 						// 0
		Lpspi1_Transmit(LED7_point[day_one]); 			// 1.
		Lpspi1_Transmit(LED6[month_ten]);						// 0
		Lpspi1_Transmit(LED5_point[month_one]);			// 1.
		Lpspi1_Transmit(LED4[year_thousand]);				// 1
		Lpspi1_Transmit(LED3[year_hundred]);				// 9
		Lpspi1_Transmit(LED2[year_ten]);						// 7
		Lpspi1_Transmit(LED1[year_one]);						// 1
	
}
void Uart1_init(void)
{
	//1. Setting Tx/Rx pin
	PORTC_PCR6.base = PORTC;
	PORTC_PCR7.base = PORTC;	
	
	PORTC_PCR6.pinPortIdx = 6;
	PORTC_PCR7.pinPortIdx = 7;	
	
	// 2. Set pin as GPIO
	PORTC_PCR6.mux = PORT_MUX_ALT2;  													//PORTC_PCR6 |= (2 << 8);
	PORTC_PCR7.mux = PORT_MUX_ALT2; 													//PORTC_PCR7 |= (2 << 8);	
	
	// 3. setting pull down registor
	PORTC_PCR6.pullConfig	=	PORT_NO_PULL_UP_DOWN ;						//PORTC_PCR6 |=  (0<<1);
	PORTC_PCR7.pullConfig = PORT_NO_PULL_UP_DOWN ;						//PORTC_PCR7 |=  (0<<1);
	
	PORTC_PCR6.driveSelect = PORT_LOW_DRV_STRENGTH; 					// PORTC_PCR6 &=~  (1u<<0);
	PORTC_PCR7.driveSelect = PORT_LOW_DRV_STRENGTH; 					// PORTC_PCR7 &=~  (1u<<0);
	
	// 4. Enable interrupt
	PORTC_PCR6.intConfig = PORT_DMA_INT_DISABLED; 
	PORTC_PCR7.intConfig = PORT_DMA_INT_DISABLED;
	
	Port_Init(&PORTC_PCR6) ;																	//PORTC_PCR6 |=  (1<<4);
	Port_Init(&PORTC_PCR7) ;																	//PORTC_PCR7 |=  (1<<4);		
	
	// PCC_LPUART1
	PCC_LPUART1.clockName =  LPUART1_CLK ;
	PCC_LPUART1.clkSrc = CLK_SRC_OP_3 ;
	PCC_LPUART1.clkGate = CLK_GATE_ENABLE;		
	Clock_SetPccConfig(&PCC_LPUART1);
	
	Init_config.F_lpuart = 48000000;
	Init_config.BaudRate = 19200;	
	Init_config.OverSampling = 8;
	Init_config.BitMode = LPUART_BIT_MODE_8;
	Init_config.StopBits = LPUART_STOP_BIT_1 ;
	Init_config.Parity = LPUART_PARITY_NONE ;
	Init_config.Mode = LPUART_MODE_TX_RX;
	
	Lpuart1_config.Instance = LPUART1;	
	Lpuart1_config.Init = Init_config;
	//6. Enable Receiver Interrupt
	LPUART1->CTRL |= (1<<21);
	
	Lpuart_Init(&Lpuart1_config);
}
void MAX7219_Init(void)
{		
	//1. Setting SCK/PCS/SOUT/SIN pin
	// enable port B
	PCC_PORTB.clockName = PORTB_CLK ;
	PCC_PORTB.clkSrc = CLK_SRC_OP_1 ;
	PCC_PORTB.clkGate = CLK_GATE_ENABLE;		
	Clock_SetPccConfig(&PCC_PORTB);
		
	//PORTB_PCR17 |= (3<<8); 
	PORTB_PCR17.base = PORTB;
	PORTB_PCR17.pinPortIdx = 17;
	PORTB_PCR17.pullConfig = PORT_NO_PULL_UP_DOWN;
	PORTB_PCR17.driveSelect = PORT_LOW_DRV_STRENGTH;
	PORTB_PCR17.mux = PORT_MUX_ALT3 ;
	PORTB_PCR17.intConfig = PORT_DMA_INT_DISABLED;

	//PORTB_PCR16 |= (3<<8); 
	PORTB_PCR16.base = PORTB;
	PORTB_PCR16.pinPortIdx = 16;
	PORTB_PCR16.pullConfig = PORT_NO_PULL_UP_DOWN;
	PORTB_PCR16.driveSelect = PORT_LOW_DRV_STRENGTH;
	PORTB_PCR16.mux = PORT_MUX_ALT3 ;
	PORTB_PCR16.intConfig = PORT_DMA_INT_DISABLED;
	 
	//PORTB_PCR15 |= (3<<8); 
	PORTB_PCR15.base = PORTB;
	PORTB_PCR15.pinPortIdx = 15;
	PORTB_PCR15.pullConfig = PORT_NO_PULL_UP_DOWN;
	PORTB_PCR15.driveSelect = PORT_LOW_DRV_STRENGTH;
	PORTB_PCR15.mux = PORT_MUX_ALT3 ;
	PORTB_PCR15.intConfig = PORT_DMA_INT_DISABLED;
	 
	//PORTB_PCR14 |= (3<<8); 
	PORTB_PCR14.base = PORTB;
	PORTB_PCR14.pinPortIdx = 14;
	PORTB_PCR14.pullConfig = PORT_NO_PULL_UP_DOWN;
	PORTB_PCR14.driveSelect = PORT_LOW_DRV_STRENGTH;
	PORTB_PCR14.mux = PORT_MUX_ALT3 ;
	PORTB_PCR14.intConfig = PORT_DMA_INT_DISABLED;
	 
	Port_Init(&PORTB_PCR17);
	Port_Init(&PORTB_PCR16);
	Port_Init(&PORTB_PCR15);
	Port_Init(&PORTB_PCR14);
	
	//2. Select source LPSPI
	//Enable Div2
	FIRC_cf.div2 = SCG_CLOCK_DIV_BY_1; 		// SCG_FIRCDIV |= (1<<8) 
	Clock_SetScgFircConfig(&FIRC_cf);
	
	//enable clock
	PCC_LPSPI1.clockName =  LPSPI1_CLK ;	// SCG_FIRCDIV |= (1<<8); 
	PCC_LPSPI1.clkSrc = CLK_SRC_OP_3 ; 		// PCC_LPSPI1  |= (3<<24);	
	PCC_LPSPI1.clkGate = CLK_GATE_ENABLE;	// PCC_LPSPI1  |= (1<<30);
	
	Clock_SetPccConfig(&PCC_LPSPI1);
		
	Lpspi1_init.F_lpspi = 48000000;
	Lpspi1_init.spi_speed = 1000000;
	Lpspi1_init.spi_prescaler = LPSPI_PRE_DIV_BY_8;
	Lpspi1_init.spi_type_tran = LPSPI_MSB_FIRST ;
	Lpspi1_init.spi_frame = LPSPI_FRAME_16 ;
	Lpspi1_init.spi_cpol = SPI_CPOL_0;
	Lpspi1_init.spi_cpha = SPI_CPHA_0;
	Lpspi1_init.spi_pcs = LPSPI_PCS_3 ;
	
	Lpspi1_config.pSPIx = LPSPI1;		
	Lpspi1_config.Init = Lpspi1_init;
	LPSPI1 -> CCR |= (8<<16); // delay time cs go down to receive data
	LPSPI1 -> CCR |= (8<<8);	// delay time between transmit times
	//9. Enable LPSPI module
	Lpspi_Init(&Lpspi1_config);
	
		Lpspi1_Transmit(0x0c01); 		
		Lpspi1_Transmit(0x09ff);	
		Lpspi1_Transmit(0x0b07);
		Lpspi1_Transmit(0x0A00);
		Lpspi1_Transmit(0x0f00);
		Lpspi1_Transmit(0x0189);
	
}
void systick_clock_init(void)
{
	systick_config.fSystick = 48000000;
	systick_config.period = 100;
	systick_config.isInterruptEnabled = ENABLE_SYST_INT;
	Systick_Init(&systick_config);
	Systick_Start();
}

void button_init(void)
{
	//1 enable port C for button 
	PCC_PORTC.clockName =  PORTC_CLK ;
	PCC_PORTC.clkSrc = CLK_SRC_OP_1 ;
	PCC_PORTC.clkGate = CLK_GATE_ENABLE;		
	Clock_SetPccConfig(&PCC_PORTC);	

	PORTC_PCR12.base = PORTC;
	PORTC_PCR13.base = PORTC;	
	
	PORTC_PCR12.pinPortIdx = 12;
	PORTC_PCR13.pinPortIdx = 13;	
	
	// 2. Set pin as GPIO
	PORTC_PCR12.mux = PORT_MUX_AS_GPIO;  							//PORTC_PCR12 |= (1 << 8);
	PORTC_PCR13.mux = PORT_MUX_AS_GPIO; 							 	//PORTC_PCR13 |= (1 << 8);

	// 3. setting pull down registor
	PORTC_PCR12.pullConfig	=	PORT_PULL_DOWN ;						//PORTC_PCR12 |=  (1<<1);
	PORTC_PCR13.pullConfig = PORT_PULL_DOWN ;						//PORTC_PCR13 |=  (1<<1);
	
	PORTC_PCR12.driveSelect = PORT_LOW_DRV_STRENGTH; 	// PORTC_PCR12 &=~  (1u<<0);
	PORTC_PCR13.driveSelect = PORT_LOW_DRV_STRENGTH; 	// PORTC_PCR13 &=~  (1u<<0);
	
	// 4. Set pin as input
  GPIOC_PCR12.base = GPIOA; 													// GPIOA_PDDR &=~ (1u << 3u);
	GPIOC_PCR12.GPIO_PinNumber = 12;
	GPIOC_PCR12.GPIO_PinMode = INPUT_MODE;
	Gpio_Init(&GPIOC_PCR12);
	
	GPIOC_PCR13.base = GPIOB; 													// GPIOB_PDDR &=~ (1u << 8u);
	GPIOC_PCR13.GPIO_PinNumber = 13;
	GPIOC_PCR13.GPIO_PinMode = INPUT_MODE;																						
	Gpio_Init(&GPIOC_PCR13);	
	
	// 5. Enable interrupt
	PORTC_PCR12.intConfig = PORT_DMA_RISING_EDGE; 
	PORTC_PCR13.intConfig = PORT_DMA_RISING_EDGE ;

	// 6. Enable Passive Filter Enable
	PORTC->PCR[12] |= (1<<4);
	PORTC->PCR[13] |= (1<<4);

	
	// 7. config
	Port_Init(&PORTC_PCR12) ;													
	Port_Init(&PORTC_PCR13) ;													
}

