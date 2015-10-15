/*****************************************************************************

                Microchip Memory Disk Drive File System

 *****************************************************************************
 FileName:        Demonstration.c
 Dependencies:    FSIO.h
 Processor:       PIC24F/PIC32
 Compiler:        C30/C32
 Description:     This project demonstrates the use of SD Card
                    -> It describes how to initialise SD card hardware
                    -> It describes how to open a file
                    -> It describes how to write in a file
                    -> It describes how to read a file
                    -> It desfribes how to make a file folder
                    -> It describes how to search a file
                    -> It describes how to delete a file

******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ports.h>
#include <p24fj256gb206.h>
#include <pic24f_periph_features.h>
#include "ELBv21_HardwareConfig.h"
#include "ELB_OSC.h"
#include "ELB_Timer.h"
#include "ELB_UART.h"
#include "ELB_LCD.h"
#include "ELB_I2C.h"

#include "Define.h"
//#include "CONFIGbits.h"


#define USE_AND_OR		// Macro to use Periheral Lib
#include <p24fxxxx.h>
#include <PIC24F_periph_features.h>
#include <spi.h>
#include <pps.h>

#include "FSIO.h"
#include "Configuration.h"


/****Decleration of global variables***/

char sendBuffer[] = "This is test string 1";
char send2[] = "2";
char receiveBuffer[50];
extern  ts_ELB_Hardware Hardware;
extern V_PBIntFlag_U8;
U8 A_LCDarray_U8[50];
int Readbits;
int code;
char barcode[11];
char finalcode[2];
int trig;
char str[3];

int trig1; int trig2; int trig3;
int trig4; int trig5; int trig6;



int main (void)
{

    	int flag1 = 1;
	int flag2 = 1;

        SET_FreqOsc( FRCDIV_1MHZ );
        Hardware_INIT();
        //Hardware.ConfigPins_Default();
        LCD_INIT();
//--------------
        Hardware.ConfigPins_PB(USE1|USE2|USE3); //Config Push Button 1,2,3 pins
        Hardware.ConfigPins_Motor(USE1|USE2);

     // /*
        TRISEbits.TRISE1 = 0;
      PORTEbits.RE1 = 1;
        TRISEbits.TRISE2 = 0;
      PORTEbits.RE2 = 1;
      TRISEbits.TRISE3 = 0;
      PORTEbits.RE3 = 1;
      Enable_PB123Int();

      //Waits until you start the motor by pressing push button1
       while (1)
    {
        // Push Button Interrupt Flag  variable (V_PBIntFlag_U8) is set in the
        //Interrupt Service Routine, when the the state of Change Notification
        //pins connected to Push Buttons changes
        if (V_PBIntFlag_U8) //Check PB interrupt flag
        {
            sprintf(A_LCDarray_U8,"Starting");
            LCD_WriteString(1,1,A_LCDarray_U8);

            V_PBIntFlag_U8 = 0; //Reset the PB interrupt flag
            if (PB1) //If PB1 is pressed
            {
                M_ToggleIO(LED1); //Toggle LED1
                MotA1 = 1;
                MotA2 = 0;
                break;

            }
            if (PB2) //If PB1 is pressed
            {
                M_ToggleIO(LED2); //Toggle LED1

            }
            if (PB3) //If PB1 is pressed
            {
                M_ToggleIO(LED3); //Toggle LED1

            }
        }
        sprintf(A_LCDarray_U8,"wait");
    LCD_WriteString(1,1,A_LCDarray_U8);

    }

    //configuring ADC bits

    //int count=11;

    TRISBbits.TRISB1 = 0;

    AD1CON1 = 0x0000;
    AD1CHS = 0x0001;
    AD1CSSL = 0;
    AD1CON2 = 0;
    AD1CON3 = 0x0002;
    AD1CON1bits.ADON = 1;



    sprintf(A_LCDarray_U8,"Starting");
    LCD_WriteString(1,1,A_LCDarray_U8);





    int i=0;
    int trigger =0; int trigger2=1; int a=0; int b=0;
    int ftrig=0; int p=1;
    int cc=0;

    //Takes input for the 3 trigger values for the character codes.
    while(i<3)
    {
        //while(1)
        //{
        //     sprintf(A_LCDarray_U8," Output ");
     //LCD_WriteString(1,3,A_LCDarray_U8);
       // }
        AD1CON1bits.SAMP = 1;
        DELAY_mSec(1);
        AD1CON1bits.SAMP = 0;

        while(!AD1CON1bits.DONE)  ;
        Readbits = ADC1BUF0;
        //while(1)
        //{
        //sprintf(A_LCDarray_U8," %d ",Readbits);
        //LCD_WriteString(1,3,A_LCDarray_U8);
    //}

        if(Readbits>100) //130
        {

            if(i==0&&trigger!=0) { trig1=b; i++; }

            else if(i==1&&trigger!=0) { trig2=b; i++; }

            else if(i==2&&trigger!=0) { trig3=b; i++; }

            else {
                
            }

                sprintf(A_LCDarray_U8,"waiting");
                LCD_WriteString(1,1,A_LCDarray_U8);
                trigger2++;
                a=trigger2;
                trigger=b;
                //sprintf(A_LCDarray_U8,"%d %d",trigger,cc);
                //LCD_WriteString(2,1,A_LCDarray_U8);
                trigger=0;



        }

        else
        {

                sprintf(A_LCDarray_U8,"Reading wait");
                LCD_WriteString(1,1,A_LCDarray_U8);

                trigger2=a;
                //sprintf(A_LCDarray_U8,"%d %d",trigger2,cc);
                //LCD_WriteString(2,1,A_LCDarray_U8);
                trigger2=0;
                trigger++;
                b=trigger;
                ftrig=trigger;

        }
    }
    /////

    MotA1=0;
    MotA2=0;
    //for18[0]=ftrig;
    /////
     //Waits until you start the motor again by pressing push button1
     while (1)
    {
        // Push Button Interrupt Flag  variable (V_PBIntFlag_U8) is set in the
        //Interrupt Service Routine, when the the state of Change Notification
        //pins connected to Push Buttons changes
        if (V_PBIntFlag_U8) //Check PB interrupt flag
        {
            sprintf(A_LCDarray_U8,"Starting");
            LCD_WriteString(1,1,A_LCDarray_U8);

            V_PBIntFlag_U8 = 0; //Reset the PB interrupt flag
            if (PB1) //If PB1 is pressed
            {
                M_ToggleIO(LED1); //Toggle LED1
                MotA1 = 1;
                MotA2 = 0;
                break;

            }
            if (PB2) //If PB1 is pressed
            {
                M_ToggleIO(LED2); //Toggle LED1

            }
            if (PB3) //If PB1 is pressed
            {
                M_ToggleIO(LED3); //Toggle LED1

            }
        }
        sprintf(A_LCDarray_U8,"Dying");
    LCD_WriteString(1,1,A_LCDarray_U8);

    }
    
    //Takes input for the 3 trigger values for the character codes.
    trigger=0; trigger2=0;
    i=0;
    while(i<3)
    {
        //while(1)
        //{
        //     sprintf(A_LCDarray_U8," Output ");
     //LCD_WriteString(1,3,A_LCDarray_U8);
       // }
        AD1CON1bits.SAMP = 1;
        DELAY_mSec(1);
        AD1CON1bits.SAMP = 0;

        while(!AD1CON1bits.DONE)  ;
        Readbits = ADC1BUF0;
        //while(1)
        //{
        //sprintf(A_LCDarray_U8," %d ",Readbits);
        //LCD_WriteString(1,3,A_LCDarray_U8);
    //}

        if(Readbits>100) //130
        {
            //reading trigger values for the characters
            if(i==0&&trigger!=0) { trig4=b; i++; }

            else if(i==1&&trigger!=0) { trig5=b; i++; }

            else if(i==2&&trigger!=0) { trig6=b; i++; }

            else {

            }

                sprintf(A_LCDarray_U8,"waiting");
                LCD_WriteString(1,1,A_LCDarray_U8);
                trigger2++;
                a=trigger2;
                trigger=b;
                //sprintf(A_LCDarray_U8,"%d %d",trigger,cc);
                //LCD_WriteString(2,1,A_LCDarray_U8);
                trigger=0;



        }

        else
        {


                sprintf(A_LCDarray_U8,"Reading start");
                LCD_WriteString(1,1,A_LCDarray_U8);

                trigger2=a;
                //sprintf(A_LCDarray_U8,"%d %d",trigger2,cc);
                //LCD_WriteString(2,1,A_LCDarray_U8);
                trigger2=0;
                trigger++;
                b=trigger;




        }
        
    }


        sprintf(A_LCDarray_U8,"Done process");
        LCD_WriteString(1,1,A_LCDarray_U8);

        MotA1=0;
        MotA2=0;
        //compares the trigger values to distinguish between the characters 'P' , 'I', 'C'.
        int x1=0; int x2=0; int charflag=0;

        if(trig1<trig2&&trig1<trig3)
        {
            str[0]='I';  x1=0; charflag++;
        }
        else if(trig2<trig1&&trig2<trig3)
        {
            str[1]='I'; x1=1; charflag++;
        }
        else //if(trig3>trig2&&trig3>trig1)
        {
            str[2]='I'; x1=2; charflag++;
        }

        if(trig4>trig5&&trig4>trig3)
        {
            str[0]='C'; x2=0; charflag++;
        }
        else if(trig5>trig4&&trig5>trig6)
        {
            str[1]='C'; x2=1; charflag++;
        }
        else //if(trig3>trig2&&trig3>trig1)
        {
            str[2]='C'; x2=2; charflag++;
        }

        int x3;
        if(charflag==2)
        {
            x3=3-x1-x2;
        }
        if(x3==0||x3==1||x3==2)
            str[x3]='P';

        /*
        */
        

    /***Local Variables***/
   FSFILE * pointer;
   SearchRec rec;
   unsigned char attributes;

   /************ Define the SPI Pin mpaing for PPS and Map the PPS pins************/
   #if (SPI1_EN ==1)

           // Configure the PPS and Map the pins and Directions
           #if (SPI1_MODE == MASTER)
                        iPPSOutput(SPI1_CLK,OUT_FN_PPS_SCK1OUT);
                        iPPSOutput(SPI1_CS,OUT_FN_PPS_SS1OUT);
                        SPI1_CS_DIR = DIR_OUT;
                        SPI1_CLK_DIR = DIR_OUT;
           #endif
           #if (SPI1_MODE == SLAVE)
                        iPPSInput(IN_FN_PPS_SCK1IN,SPI1_CLK);
                        iPPSInput(IN_FN_PPS_SS1IN,SPI1_CS);
                        SPI1_CS_DIR = DIR_IN;
                        SPI1_CLK_DIR = DIR_IN;
           #endif

           iPPSInput(IN_FN_PPS_SDI1,SPI1_DO );
           iPPSOutput(SPI1_DI,OUT_FN_PPS_SDO1);
           SPI1_DI_DIR = DIR_OUT ;
           SPI1_DO_DIR = DIR_IN;

           TRISDbits.TRISD7 = 0;
           LATDbits.LATD7 = 1;

   #endif

   while (!MDD_MediaDetect());

   /************************ Initialize the SD Card library************************/

   while (!FSInit());                                                   // Wait till Hardware initializes and mount the card to the Library

   /*******Switch on LED1 to confirm card initializition*******/
      TRISEbits.TRISE1 = 0;
      PORTEbits.RE1 = 1;
   /***********************************************************/





   /************************ WRITE OPERATION IN SD CARD **************************/

      sprintf(A_LCDarray_U8,"Done2");
        LCD_WriteString(1,1,A_LCDarray_U8);

   #ifdef ALLOW_WRITES                                                  // Macro to Enable write operation
       pointer = FSfopen ("BARCODE2.TXT", "w");                            // Open a new file in wrtie mode
           if (pointer == NULL)
           while(1);

           sprintf(A_LCDarray_U8,"Donereyy");
        LCD_WriteString(1,1,A_LCDarray_U8);

           sprintf(A_LCDarray_U8,"Done4");
        LCD_WriteString(1,1,A_LCDarray_U8);

        //FSfprintf(, "Binary number=%#16b", 0x1eff);


        //#ifdef ALLOW_FSFPRINTF
       //   int b=  FSputc ('a', pointer);
        //#endif
        char sendb[]="  \n  ";
        if (FSfwrite (sendb,1, 4, pointer) != 4)             
           while(1);

           
           //char sendb[]="  \n heyy \n ";
        //if (FSfwrite (sendb,1, 13, pointer) != 13)             
           //while(1);

           if (FSfwrite (str, 1, 3, pointer) != 3)             //writes the characters in  the barcode.
           while(1);

           if (FSfclose (pointer))                                        // Close the file
         while(1);
  #endif
     sprintf(A_LCDarray_U8,"Done3");
        LCD_WriteString(1,1,A_LCDarray_U8);

/*********************************************************************
   The final contents of our card should look like this:
   \ -> FILE1.TXT  (This is test string 2)
     -> ONE       -> TWO     -> THREE -> FILE3.TXT
                                      -> FOUR      -> FIVE       -> SIX
*********************************************************************/
    while(1)
        { sprintf(A_LCDarray_U8,str);
        LCD_WriteString(2,1,A_LCDarray_U8);
            if (PB1) //If PB1 is pressed
            {
            break;
            }
        }
        //Waits until u restart it by presing push button3
   while (1)
    {
        // Push Button Interrupt Flag  variable (V_PBIntFlag_U8) is set in the
        //Interrupt Service Routine, when the the state of Change Notification
        //pins connected to Push Buttons changes
        if (V_PBIntFlag_U8) //Check PB interrupt flag
        {
            sprintf(A_LCDarray_U8,"Startingagain");
            LCD_WriteString(1,1,A_LCDarray_U8);

            V_PBIntFlag_U8 = 0; //Reset the PB interrupt flag
            if (PB1) //If PB1 is pressed
            {
                M_ToggleIO(LED1); //Toggle LED1
                //break;


            }
            if (PB2) //If PB1 is pressed
            {
                M_ToggleIO(LED2); //Toggle LED1
                //break;

            }
            if (PB3) //If PB1 is pressed
            {
                M_ToggleIO(LED3); //Toggle LED1
                break;

            }
        }
   }
}







