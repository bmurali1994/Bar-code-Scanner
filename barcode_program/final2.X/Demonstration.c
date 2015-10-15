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

//int for18[11]={0,0,0,0,0,0,0,0,0,0,0};

int checkvalid()    //checks the guards of the barcode obtained
{

    if(barcode[0]=='1'&&barcode[1]=='0'&&barcode[2]=='1'&&
            barcode[5]=='0'&&barcode[9]=='0'&&barcode[10]=='1')
    {
        /**if(barcode[3]=='0'&&barcode[8]=='1'&&barcode[9]=='0'&&barcode[14]=='1'&&barcode[15]=='0'&&
                barcode[20]=='1'&&barcode[21]=='0'&&barcode[26]=='1'&&barcode[30]=='1'&&barcode[35]=='0'&&
                barcode[36]=='1'&&barcode[41]=='0'&&barcode[42]=='1'&&barcode[47]=='0'&&barcode[48]=='1'&&
                barcode[53]=='0')
            return 1;   **/

        return 1;
    }
    else
        return 0;
}

int checkbarcode(char a, char b, char c)    //checks whether the bits of the barcode are read correctly or not
{

           if(a=='0'&&b=='1'&&c=='1')
             return 0;
            if(a=='1'&&b=='0'&&c=='1')
             return 0;
            if(a=='1'&&b=='1'&&c=='0')
             return 0;


            if(a=='0'&&b=='0'&&c=='1')
                return 1;
            if(a=='0'&&b=='1'&&c=='0')
                return 1;
            if(a=='1'&&b=='0'&&c=='0')
                return 1;


         return 2;

}

void reversecode() //reverses the entire barcode
{
    int i=0; char c;

    while(i<5)
    {
        c=barcode[i];
        barcode[i]=barcode[10-i];
        barcode[10-i]=c;
        i++;
    }
}

int checkpower(int a) //checks whether a is some power of 2
{
    if(a<0) a=0-a;

    int t=1;
    while(t<a)
    {
        t=2*t;
    }
    if(t==a) return 1;
    else return 0;
}

void correction1(int l) //checks the left band of bits for correction. Corrects bits
{
    //(barcode[l], barcode[l+1],barcode[l+2],barcode[l+3],barcode[l+4],barcode[l+5],barcode[l+6])

    int i=2; int count=0; int a=0; int j=i; int t=1;
    while(i>=0)
    {
        if(barcode[l+i]=='1')
        {
            j=i; t=1;
            while(j<2)
            {
                t=2*t;
                j++;
            }
            a+=t;
            count++;
        }
        i--;
    }

    if(count%2==0)
    {
        if(checkpower(a-1))
        {
   barcode[l]='0'; barcode[l+1]='0'; barcode[l+2]='0'; barcode[l+3]='1'; barcode[l+4]='1'; barcode[l+5]='0'; barcode[l+6]='1';
        }
        else if(checkpower(a-2))
        {
   barcode[l]='0'; barcode[l+1]='0'; barcode[l+2]='1'; barcode[l+3]='1'; barcode[l+4]='0'; barcode[l+5]='0'; barcode[l+6]='1';
        }
        else if(checkpower(a-4))
        {
   barcode[l]='0'; barcode[l+1]='0'; barcode[l+2]='1'; barcode[l+3]='0'; barcode[l+4]='0'; barcode[l+5]='1'; barcode[l+6]='1';
        }
        else
        {
            sprintf(A_LCDarray_U8,"Barcode err");
            LCD_WriteString(1,1,A_LCDarray_U8);
            exit(0);
        }
    }
    else
    {
        //nothing
    }
}

void correction2(int l)     //checks the right band of bits for correction. Corrects bits
{
    int i=2;
    while(i>=0)
    {
        if(barcode[l+i]=='1')
        {
            barcode[l+i]=='0';
        }
        else if(barcode[l+i]=='0')
        {
            barcode[l+i]=='1';
        }
        i--;
    }

    correction1(l);

    i=2;
    while(i>=0)
    {
        if(barcode[l+i]=='1')
        {
            barcode[l+i]=='0';
        }
        else if(barcode[l+i]=='0')
        {
            barcode[l+i]=='1';
        }
        i--;
    }

}

void decode(int l)  //decodes all the bits of the barcode into number
{
    if(l>5)
    {
       int j=2;
        while(j>=0)
        {
         if(barcode[l+j]=='1')
         {
             barcode[l+j]=='0';
          }
         else if(barcode[l+j]=='0')
         {
             barcode[l+j]=='1';
         }
            j--;
        }
    }

    int i=0;
    if(barcode[l]=='0' && barcode[l+1]=='0'&& barcode[l+2]=='1')
        finalcode[i]='1';
    else if (barcode[l]=='0' && barcode[l+1]=='1'&& barcode[l+2]=='0')
        finalcode[i]='2';
    else if (barcode[l]=='1' && barcode[l+1]=='0'&& barcode[l+2]=='0')
        finalcode[i]='3';

    if(l>5)
    {
       int j=2;
        while(j>=0)
        {
         if(barcode[l+j]=='1')
         {
             barcode[l+j]=='0';
          }
         else if(barcode[l+j]=='0')
         {
             barcode[l+j]=='1';
         }
            j--;
        }
    }

    i++;
}


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


    //configuring for ADC operation
    int count=11;

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

    while(1)
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
        //detecting white
            if(trigger2==0)
            {
                break;
                barcode[i]='1'; trigger2=0; i++;
            }

                sprintf(A_LCDarray_U8,"TRIGGER END");
                LCD_WriteString(1,1,A_LCDarray_U8);
                trigger2++;
                a=trigger2;
                trigger=b;
                sprintf(A_LCDarray_U8,"%d %d",trigger,i);
                LCD_WriteString(2,1,A_LCDarray_U8);
                trigger=0;



        }

        else
        {
            //detecting black
            if(trigger==0)
            {
                barcode[i]='1'; i++;

            }

                sprintf(A_LCDarray_U8,"TRIGGER START");
                LCD_WriteString(1,1,A_LCDarray_U8);


                trigger2=a;
                sprintf(A_LCDarray_U8,"%d %d",trigger2,i);
                LCD_WriteString(2,1,A_LCDarray_U8);
                trigger2=0;
                trigger++;
                b=trigger;
                ftrig=trigger;

        }
    }
    /////


    //for18[0]=ftrig;
    /////
    trigger=0; trigger2=0;
    i=1;
    while(i<11)
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
         //detecting black
            if(trigger2==0)
            {
                if(trigger<ftrig+60&&trigger>ftrig-60)
                { barcode[i]='1'; i++;
                   /////
                //for18[i]=trigger;
                }

                 if(trigger<2*ftrig+60&&trigger>2*ftrig-60)
                { barcode[i]='1'; i++;
                    barcode[i]='1'; i++;
                    //for18[i]=trigger;
                }

            }

                sprintf(A_LCDarray_U8,"TRIGGER END");
                LCD_WriteString(1,1,A_LCDarray_U8);
                trigger2++;
                a=trigger2;
                trigger=b;
                sprintf(A_LCDarray_U8,"%d %d",trigger,i);
                LCD_WriteString(2,1,A_LCDarray_U8);
                trigger=0;



        }

        else
        {
             //detecting black
            if(trigger==0)
            {
                if(trigger2<2*ftrig+60&&trigger2>2*ftrig-60)
                { barcode[i]='0'; i++;//for18[i]=trigger;
                }

                if(trigger2<3*ftrig+60&&trigger2>3*ftrig-60)
                { barcode[i]='0'; i++;
                    barcode[i]='0'; i++;//for18[i]=trigger;
                }
            }


                sprintf(A_LCDarray_U8,"TRIGGER START");
                LCD_WriteString(1,1,A_LCDarray_U8);


                trigger2=a;
                sprintf(A_LCDarray_U8,"%d %d",trigger2,i);
                LCD_WriteString(2,1,A_LCDarray_U8);
                trigger2=0;
                trigger++;
                b=trigger;

                


        }
    }
    
        count=4; int checkf=0;
        //checks whether the barcode has ended or not
        while(count>0)
        {
            AD1CON1bits.SAMP = 1;
            DELAY_mSec(2*trigger);
            AD1CON1bits.SAMP = 0;
            while(!AD1CON1bits.DONE);
            Readbits = ADC1BUF0;
            count--;

            if(Readbits>130)
            {
                code=0;         //WHITE
                checkf++;
            }
            else
            {
                code=1;         //BLACK
            }
        }
        MotA1=0;
        MotA2=0;
        sprintf(A_LCDarray_U8,"Readingdone");
        LCD_WriteString(1,1,A_LCDarray_U8);

        //processes the barcode, checks whether it correct or not, does correction and decodes it
        if(checkf==4)
        {
            if(checkvalid())
            {
                if(checkbarcode(barcode[2],barcode[3],barcode[4])==1)
                {

                }
                else if(checkbarcode(barcode[2],barcode[3],barcode[4])==0)
                {
                    reversecode();
                }
                else
                {
                    //correction();
                int l=2;
                while(l<9)
                {
                    if(l<5)
                    {
                        correction1(l);

                    }
                    else
                    {
                        correction2(l);
                    }
                    l+=4;

                }
                    //correction();
                }
                int lp=2;
                while(lp<9)
                {
                    if(lp<5)
                    {
                        correction1(lp);

                    }
                    else
                    {
                        correction2(lp);
                    }
                    lp+=4;

                }


                 int l=2;
                while(l<9)
                {
                    if(l<5)
                    {
                        decode(l);

                    }
                    else
                    {
                        decode(l);
                    }
                    l+=4;

                }
                //final code is ready;
            }
             else
            {
            sprintf(A_LCDarray_U8,"Barcode err");
            LCD_WriteString(1,1,A_LCDarray_U8);
            exit(0);
            }
        }

        else
        {
            sprintf(A_LCDarray_U8,"Barcode err");
            LCD_WriteString(1,1,A_LCDarray_U8);
            exit(0);
        }

        sprintf(A_LCDarray_U8,"Done process");
        LCD_WriteString(1,1,A_LCDarray_U8);

        MotA1=0;
        MotA2=0;

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
       pointer = FSfopen ("BARCODE.TXT", "a");                            // Open a new file in wrtie mode
           if (pointer == NULL)
           while(1);

           sprintf(A_LCDarray_U8,"Done4");
        LCD_WriteString(1,1,A_LCDarray_U8);

        //FSfprintf(, "Binary number=%#16b", 0x1eff);


        //#ifdef ALLOW_FSFPRINTF
       //   int b=  FSputc ('a', pointer);
        //#endif
        char sendb[]="  \n  ";
        if (FSfwrite (sendb,1, 3, pointer) != 3)            
           while(1);
           
           //if (FSfwrite (for18,1, 11, pointer) != 11)             
           //while(1);
           //char sendb[]="  \n heyy \n ";
        //if (FSfwrite (sendb,1, 13, pointer) != 13)             
           //while(1);

           if (FSfwrite (barcode, 1, 11, pointer) != 11)             //writes the barcode into the file
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

//Waits until you start again by pressing push button 3
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







