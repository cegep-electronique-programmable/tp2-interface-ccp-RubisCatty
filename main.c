/*
 Sonia Michaud
 Programme qui lit une onde carré
 */
/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F25K80
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "ecran.h"

/*
                         Main application
 */
void Capture_CallBack(uint16_t capturesValue);
uint16_t Haut;
uint16_t Bas;
bool rising=1;
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    CCP2_SetCallBack(Capture_CallBack);
    videEcran();
    curseurPosition(0x00);
    printf("Temps Haut:");
    curseurPosition(0x40);
    printf("Periode   :");
    curseurPosition(0x14);
    printf("Magnetique:");
    while (1)
    {
        curseurPosition(0x0C);
        printf("%d",Haut/5);
        curseurPosition(0x4C);
        printf("%d",((Haut+Bas)/5));
        static signed uint16_t magnetique;
        static unsigned float force;
        magnetique=(Haut/(Haut+Bas))-50;
        if(magnetique<0){
            force=magnetique*-1;
        }else{
            force=magnetique;
        }
        curseurPosition(0x20);
        printf("%0.2f",force);
    }
}
void Capture_CallBack(uint16_t capturesValue){
    static uint16_t oldValue;
    if (rising==1){
        Bas=(capturesValue-oldValue);
        oldValue=capturesValue;
        rising=0;
        CCP2CON = 0x04;
    }else{
        Haut=capturesValue-oldValue;
        oldValue=capturesValue;
        rising=1;
        CCP2CON = 0x05;
    }
    
}
/**
 End of File
*/