/* 
 * File:    main.c
 * Author:  A.Smith
 * Created: 14-02-2018, 12:17 PM
 */
// CONFIG1
#pragma config FOSC = INTOSC    // (INTOSC oscillator; I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOREN = OFF    // Low Power Brown-out Reset enable bit (LPBOR is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (Low-voltage programming enabled)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#include "main.h"

/*****************************
            PROTOTYPES
******************************/
void initializers(void);
void ADC_Init(void);
u16 ADC1_Read(void);

/*****************************
            GLOBALS
******************************/
u16 adc = 0;                            // Temperature value
u16 ADCH = 0x0000;                      // ADC High value
u16 ADCL = 0x0000;                      // ADC Low value

/*****************************
            MAIN
******************************/
void main(void) 
{
    u8 once = 0x00;
    initializers();
    ADC_Init();
    
    once = 0x01;
    
    while(1)
    {
        //adc = ADC3_Read();                            // Read Analog Channel 3 [RA4]    - Doesn't work??
        adc = ADC1_Read();                              // Read Analog Channel 2 [RA2]      - WORKS!!
        /***********************************/
        /* To find a temperature threshold */
        /***********************************/
        if(adc <= 250){
            // Do somthing
        }
        else{
            // Do something else
        }
    }
    return;
}

/*****************************
         FUNCTIONS
******************************/
/* Initialize */
void initializers(void)
{
    /* TRIS BITS TO IO's ***/
    TRISA = 0x1B;                   // 
    /* ANALOGUE SELECT */
    ANSELA = 0x12;                  // 
	/* PORTS */
	PORTA = 0X00;                   // 
    /* OSC SET UP */
    OSCCON = 0x6A;                  // 
}

/* Initialize the ADC */
void ADC_Init(void)
{
    /* Vrpos = Vdd + Fosc/2*/
    ADCON1 = 0x80;               // 
}

/* Read the Temperature Sensor value  [RA1 - AN1] */
u16 ADC1_Read(void)
{
    ADCON0 = 0x05;               // 
    __delay_ms(2);               // 
    
    GO_nDONE = 1;                // 
    while(GO_nDONE);             // 
    //return ((ADCH<<8)+ADRESL);
    
    /* Right Justified */
    ADCH = ADRESH;
    ADCL = ADRESL;
    ADCH = ADRESH && 0x03;          // 
    ADCH = (ADCH<<8);               // 
    ADCH = ADCH + ADCL;             // 
    return ADCH;                    // 
}

