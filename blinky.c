
#include <MKL25Z4.H>


const uint32_t led_mask[] = {1UL << 18, 1UL << 19, 1UL << 1};
// LED #0, #1 are port B, LED #2 is port D
void LED_Config(void);
void LED_Set(void);
void LED_Clear(void);
__INLINE static void LED_On (uint32_t led);
__INLINE static void LED_Off (uint32_t led);
void Delay(uint32_t nCount);
void output_config();
void analog_in_config();


int main(void)
{
	SystemCoreClockUpdate(); // Optional- Setup SystemCoreClock variable
	// Configure LED outputs
	LED_Config();
	output_config();
	analog_in_config();
	
	#define LOOP_COUNT 0x80000
	
	while(1){
		Delay(LOOP_COUNT);
		//turn external led on.
		FPTD->PSOR |=(1UL<<7);
		Delay(LOOP_COUNT);
		FPTD->PCOR |=(1UL<<7);
		//turn red on
		//FPTB->PCOR |= led_mask[0];
		//Delay(LOOP_COUNT);
		//LED_Clear();	
	};


}
void Delay(uint32_t nCount)
{
while(nCount--)
{
}
}


/*----------------------------------------------------------------------------
analog in config
*----------------------------------------------------------------------------*/
void analog_in_config(void){
	SIM->SCGC5 |= 1UL<<12; //clock
  //define as gpio
	PORTD->PCR[7]|= (1UL<<8);
	
	
	
	//logic off
	FPTD->PCOR |= (1UL<<7);
	//THEN you change the direction into output
	FPTD->PDDR |= (1UL<<7);
}

/*----------------------------------------------------------------------------
output pin config
*----------------------------------------------------------------------------*/
void output_config(void){
	SIM->SCGC5 |= 1UL<<12; //clock
  //define as gpio
	PORTD->PCR[7]|= (1UL<<8);
	//logic off
	FPTD->PCOR |= (1UL<<7);
	//THEN you change the direction into output
	FPTD->PDDR |= (1UL<<7);
}


/*----------------------------------------------------------------------------
LED pin config
*----------------------------------------------------------------------------*/
void LED_Config(void)
{
SIM->SCGC5 |= (1UL << 10) | (1UL << 12); /* Enable Clock to Port B & D */
PORTB->PCR[18] = (1UL << 8); /* Pin PTB18 is GPIO */
PORTB->PCR[19] = (1UL << 8); /* Pin PTB19 is GPIO */
PORTD->PCR[1] = (1UL << 8); /* Pin PTD1 is GPIO */ 
FPTB->PDOR = (led_mask[0] |led_mask[1] ); /* switch Red/Green LED off */
FPTB->PDDR = (led_mask[0] |led_mask[1] ); /* enable PTB18/19 as Output */ 

FPTD->PDOR = led_mask[2]; /* switch Blue LED off */
FPTD->PDDR = led_mask[2]; /* enable PTD1 as Output */
return;
}
/*---------------------------------------------------------------------------
Switch on LEDs
when PCOR is set to 1 on its bit, it will turn the LED on.
*---------------------------------------------------------------------------*/
void LED_Set(void)
{
LED_On(0); //R 
LED_On(1); //G
LED_On(2); //B 
return;
}
/*---------------------------------------------------------------------------
Switch off LEDs
*---------------------------------------------------------------------------*/
void LED_Clear(void)
{
LED_Off(0);
LED_Off(1);
LED_Off(2);
return;
}
/*---------------------------------------------------------------------------
Switch on LED (just one)
*---------------------------------------------------------------------------*/
__INLINE static void LED_On (uint32_t led) {
if (led == 2) FPTD->PCOR = led_mask[led];
else FPTB->PCOR = led_mask[led];
}
/*---------------------------------------------------------------------------
Switch off LED (just one)
*---------------------------------------------------------------------------*/
__INLINE static void LED_Off (uint32_t led) {
if (led == 2) FPTD->PSOR = led_mask[led];
else FPTB->PSOR = led_mask[led];
}