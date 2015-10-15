/*
 * File:   newmain.c
 * Author: nitsikkim
 *
 * Created on October 24, 2014, 11:54 AM
 */

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
#include "CONFIGbits.h"


#define USE_AND_OR		// Macro to use Periheral Lib
#include <p24fxxxx.h>
#include <PIC24F_periph_features.h>
#include <ports.h>
#include <spi.h>
#include <pps.h>

#include "FSIO.h"
#include "Configuration.h"

/*
 *
 */

extern  ts_ELB_Hardware Hardware;
U8 A_LCDarray_U8[50];
int Readbits;
int code;
char barcode[95];
char finalcode[12];



int checkvalid() //checks the guards of the barcode obtained
{

    if(barcode[0]=='1'&&barcode[1]=='0'&&barcode[2]=='1'&&
            barcode[45]=='0'&&barcode[46]=='1'&&barcode[47]=='0'&&barcode[48]=='1'&&barcode[49]=='0'&&
            barcode[92]=='1'&&barcode[93]=='0'&&barcode[94]=='1')
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

int checkbarcode(char a, char b, char c, char d, char e, char f, char g) //checks whether the bits of the barcode are read correctly or not
{
         if(a=='0'&&b=='0'&&c=='0'&&d=='1'&&e=='1'&&f=='0'&&g=='1'||
            a=='0'&&b=='0'&&c=='1'&&d=='1'&&e=='0'&&f=='0'&&g=='1'||
            a=='0'&&b=='0'&&c=='1'&&d=='0'&&e=='0'&&f=='1'&&g=='1'||
            a=='0'&&b=='1'&&c=='1'&&d=='1'&&e=='1'&&f=='0'&&g=='1'||
            a=='0'&&b=='1'&&c=='0'&&d=='0'&&e=='0'&&f=='1'&&g=='1'||
            a=='0'&&b=='1'&&c=='1'&&d=='0'&&e=='0'&&f=='0'&&g=='1'||
            a=='0'&&b=='1'&&c=='0'&&d=='1'&&e=='1'&&f=='1'&&g=='1'||
            a=='0'&&b=='1'&&c=='1'&&d=='1'&&e=='0'&&f=='1'&&g=='1'||
            a=='0'&&b=='1'&&c=='1'&&d=='0'&&e=='1'&&f=='1'&&g=='1'||
            a=='0'&&b=='0'&&c=='0'&&d=='1'&&e=='0'&&f=='1'&&g=='1'||
            )
    {
        return 1;
    }
    else if(a=='1'&&b=='1'&&c=='1'&&d=='0'&&e=='0'&&f=='1'&&g=='0'||
            a=='1'&&b=='1'&&c=='0'&&d=='0'&&e=='1'&&f=='1'&&g=='0'||
            a=='1'&&b=='1'&&c=='0'&&d=='1'&&e=='1'&&f=='0'&&g=='0'||
            a=='1'&&b=='0'&&c=='0'&&d=='0'&&e=='0'&&f=='1'&&g=='0'||
            a=='1'&&b=='0'&&c=='1'&&d=='1'&&e=='1'&&f=='0'&&g=='0'||
            a=='1'&&b=='0'&&c=='0'&&d=='1'&&e=='1'&&f=='1'&&g=='0'||
            a=='1'&&b=='0'&&c=='1'&&d=='0'&&e=='0'&&f=='0'&&g=='0'||
            a=='1'&&b=='0'&&c=='0'&&d=='0'&&e=='1'&&f=='0'&&g=='0'||
            a=='1'&&b=='0'&&c=='0'&&d=='1'&&e=='0'&&f=='0'&&g=='0'||
            a=='1'&&b=='1'&&c=='1'&&d=='0'&&e=='1'&&f=='0'&&g=='0'||
            )
    {
        return 0;
    }
    else
    {
        return 2;
    }

}

void reversecode() //reverses the entire barcode
{
    int i=0; char c;

    while(i<47)
    {
        c=barcode[i];
        barcode[i]=barcode[94-i];
        barcode[94-i]=c;
        i++;
    }
}

int checkpower(int a)  //checks whether a is some power of 2
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

    int i=6; int count=0; int a=0; int j=i; int t=1;
    while(i>=0)
    {
        if(barcode[l+i]=='1')
        {
            j=i; t=1;
            while(j<6)
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
        if(checkpower(a-13))
        {
   barcode[l]='0'; barcode[l+1]='0'; barcode[l+2]='0'; barcode[l+3]='1'; barcode[l+4]='1'; barcode[l+5]='0'; barcode[l+6]='1';
        }
        else if(checkpower(a-25))
        {
   barcode[l]='0'; barcode[l+1]='0'; barcode[l+2]='1'; barcode[l+3]='1'; barcode[l+4]='0'; barcode[l+5]='0'; barcode[l+6]='1';
        }
        else if(checkpower(a-19))
        {
   barcode[l]='0'; barcode[l+1]='0'; barcode[l+2]='1'; barcode[l+3]='0'; barcode[l+4]='0'; barcode[l+5]='1'; barcode[l+6]='1';
        }
        else if(checkpower(a-61))
        {
   barcode[l]='0'; barcode[l+1]='1'; barcode[l+2]='1'; barcode[l+3]='1'; barcode[l+4]='1'; barcode[l+5]='0'; barcode[l+6]='1';
        }
        else if(checkpower(a-35))
        {
   barcode[l]='0'; barcode[l+1]='1'; barcode[l+2]='0'; barcode[l+3]='0'; barcode[l+4]='0'; barcode[l+5]='1'; barcode[l+6]='1';
        }
        else if(checkpower(a-49))
        {
   barcode[l]='0'; barcode[l+1]='1'; barcode[l+2]='1'; barcode[l+3]='0'; barcode[l+4]='0'; barcode[l+5]='0'; barcode[l+6]='1';
        }
        else if(checkpower(a-47))
        {
   barcode[l]='0'; barcode[l+1]='1'; barcode[l+2]='0'; barcode[l+3]='1'; barcode[l+4]='1'; barcode[l+5]='1'; barcode[l+6]='1';
        }
        else if(checkpower(a-59))
        {
   barcode[l]='0'; barcode[l+1]='1'; barcode[l+2]='1'; barcode[l+3]='1'; barcode[l+4]='0'; barcode[l+5]='1'; barcode[l+6]='1';
        }
        else if(checkpower(a-55))
        {
   barcode[l]='0'; barcode[l+1]='1'; barcode[l+2]='1'; barcode[l+3]='0'; barcode[l+4]='1'; barcode[l+5]='1'; barcode[l+6]='1';
        }
        else if(checkpower(a-11))
        {
   barcode[l]='0'; barcode[l+1]='0'; barcode[l+2]='0'; barcode[l+3]='1'; barcode[l+4]='0'; barcode[l+5]='1'; barcode[l+6]='1';
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

void correction2(int l) //checks the right band of bits for correction. Corrects bits
{
    int i=6;
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

    i=6;
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
int finalcount=0;

void decode(int l) //decodes all the bits of the barcode into number
{
    if(l>47)
    {
       int j=6;
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
    if(barcode[l]=='0' && barcode[l+1]=='0'&& barcode[l+2]=='0'&& barcode[l+3]=='1'&& barcode[l+4]=='1'&& barcode[l+5]=='0'&& barcode[l+6]=='1')
        finalcode[i]='0';
    else if (barcode[l]=='0' && barcode[l+1]=='0'&& barcode[l+2]=='1'&& barcode[l+3]=='1'&& barcode[l+4]=='0'&& barcode[l+5]=='0'&& barcode[l+6]=='1')
        finalcode[i]='1';
    else if (barcode[l]=='0' && barcode[l+1]=='0'&& barcode[l+2]=='1'&& barcode[l+3]=='0'&& barcode[l+4]=='0'&& barcode[l+5]=='1'&& barcode[l+6]=='1')
        finalcode[i]='2';
    else if (barcode[l]=='0' && barcode[l+1]=='1'&& barcode[l+2]=='1'&& barcode[l+3]=='1'&& barcode[l+4]=='1'&& barcode[l+5]=='0'&& barcode[l+6]=='1')
        finalcode[i]='3';
    else if (barcode[l]=='0' && barcode[l+1]=='1'&& barcode[l+2]=='0'&& barcode[l+3]=='0'&& barcode[l+4]=='0'&& barcode[l+5]=='1'&& barcode[l+6]=='1')
        finalcode[i]='4';
    else if (barcode[l]=='0' && barcode[l+1]=='1'&& barcode[l+2]=='1'&& barcode[l+3]=='0'&& barcode[l+4]=='0'&& barcode[l+5]=='0'&& barcode[l+6]=='1')
        finalcode[i]='5';
    else if (barcode[l]=='0' && barcode[l+1]=='1'&& barcode[l+2]=='0'&& barcode[l+3]=='1'&& barcode[l+4]=='1'&& barcode[l+5]=='1'&& barcode[l+6]=='1')
        finalcode[i]='6';
    else if (barcode[l]=='0' && barcode[l+1]=='1'&& barcode[l+2]=='1'&& barcode[l+3]=='1'&& barcode[l+4]=='0'&& barcode[l+5]=='1'&& barcode[l+6]=='1')
        finalcode[i]='7';
    else if (barcode[l]=='0' && barcode[l+1]=='1'&& barcode[l+2]=='1'&& barcode[l+3]=='0'&& barcode[l+4]=='1'&& barcode[l+5]=='1'&& barcode[l+6]=='1')
        finalcode[i]='8';
    else if (barcode[l]=='0' && barcode[l+1]=='0'&& barcode[l+2]=='0'&& barcode[l+3]=='1'&& barcode[l+4]=='0'&& barcode[l+5]=='1'&& barcode[l+6]=='1')
        finalcode[i]='9';

    if(l>47)
    {
       int j=6;
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


int main(int argc, char** argv) {

	int flag1 = 1;
	int flag2 = 1;

        SET_FreqOsc( FRCDIV_1MHZ );
        Hardware_INIT();
        Hardware.ConfigPins_Default();
        LCD_INIT();
//--------------
        Hardware.ConfigPins_Motor(USE1|USE2);

        Hardware.ConfigPins_Motor(USE1|USE2);

     // /*
        TRISEbits.TRISE1 = 0;
      PORTEbits.RE1 = 1;
        TRISEbits.TRISE2 = 0;
      PORTEbits.RE2 = 1;
      TRISEbits.TRISE3 = 0;
      PORTEbits.RE3 = 1;
      Enable_PB123Int();

//while(1)
//{
        MotA1 = 1;
        MotA2 = 0;

// return (EXIT_SUCCESS);
//--------------

    int count=95;

    TRISBbits.TRISB1 = 0;

    AD1CON1 = 0x0000;
    AD1CHS = 0x0001;
    AD1CSSL = 0;
    AD1CON2 = 0;
    AD1CON3 = 0x0002;
    AD1CON1bits.ADON = 1;

     sprintf(A_LCDarray_U8," Output ");
     LCD_WriteString(1,3,A_LCDarray_U8);

    int i=0;
    int trigger =0;

    while(flag1)
    {
        AD1CON1bits.SAMP = 1;
        DELAY_mSec(1);
        AD1CON1bits.SAMP = 0;

        while(!AD1CON1bits.DONE)  ;
        Readbits = ADC1BUF0;

        sprintf(A_LCDarray_U8," %d ",Readbits);

        if(Readbits>130)
        {
		if(flag2==0)
		{
                    flag1 = 0;
		}

                MotA1=1;
                MotA2=0;
        }

        else
        {
		flag2 = 0;
		trigger++;

                MotA1=1;
                MotA2=0;
        }
    }


	barcode[i]=1; i++;
        count--;

        AD1CON1bits.SAMP = 1;
        DELAY_mSec(trigger/3);
        AD1CON1bits.SAMP = 0;
        while(!AD1CON1bits.DONE);
        Readbits = ADC1BUF0;
        count--;

        if(Readbits>130)
        {   barcode[i]='0'; i++;    //WHITE
        }
        else
        {
            barcode[i]='1'; i++;    //BLACK
        }

	while(count>0)
    {
        AD1CON1bits.SAMP = 1;
        DELAY_mSec(trigger);
        AD1CON1bits.SAMP = 0;
        while(!AD1CON1bits.DONE);
        Readbits = ADC1BUF0;
        count--;

        //sprintf(A_LCDarray_U8," %d ",Readbits);

        if(Readbits>130)
        {   barcode[i]='0'; i++;    //WHITE
            code=0;
        }
        else
        {
            barcode[i]='1'; i++;    //BLACK
            code=1;

        }

        sprintf(A_LCDarray_U8," %d ",code);
        LCD_WriteString(2,4,A_LCDarray_U8);

        sprintf(A_LCDarray_U8," %d %d",code,trigger);
        LCD_WriteString(2,8,A_LCDarray_U8);

    }
        count=5; int checkf=0;

        while(count>0)
        {
            AD1CON1bits.SAMP = 1;
            DELAY_mSec(trigger);
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

        if(checkf==5)
        {
            if(checkvalid())
            {
                if(checkbarcode(barcode[0],barcode[1],barcode[2],barcode[3],barcode[4],barcode[5],barcode[6])==1)
                {

                }
                else if(checkbarcode(barcode[0],barcode[1],barcode[2],barcode[3],barcode[4],barcode[5],barcode[6])==0)
                {
                    reversecode();
                }
                else
                {
                    int cot=5; int p=10; int ff=0;
                    while(cot>0)
                    {
                       if(checkbarcode(barcode[p],barcode[p+1],barcode[p+2],barcode[p+3],barcode[p+4],barcode[p+5],barcode[p+6])==1)
                        {
                           ff=1; break;
                        }
                        else if(checkbarcode(barcode[p],barcode[p+1],barcode[p+2],barcode[p+3],barcode[p+4],barcode[p+5],barcode[p+6])==0)
                        {
                            ff=1; reversecode(); break;
                        }
                        cot--; p+=7;
                    }
                    if(cot==0&&ff==0)
                    {
                        sprintf(A_LCDarray_U8,"Barcode err");
                        LCD_WriteString(1,1,A_LCDarray_U8);
                        exit(0);
                    }
                    //correction();
                }

                //correction();
                int l=3;
                while(l<91)
                {
                    if(l<47)
                    {
                        correction1(l);

                    }
                    else
                    {
                        correction2(l);
                    }
                    l+=7;
                    if(l==45) l=50;
                }

                 l=3;
                while(l<91)
                {
                    if(l<47)
                    {
                        decode(l);

                    }
                    else
                    {
                        decode(l);
                    }
                    l+=7;
                    if(l==45) l=50;
                }
                //final code is ready;
            }
        }

        else
        {
            sprintf(A_LCDarray_U8,"Barcode err");
            LCD_WriteString(1,1,A_LCDarray_U8);
            exit(0);
        }

////////////////////////////////////////////////////////SD_CARD

FSFILE * pointer;
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
       pointer = FSfopen ("BARCODEtrig.TXT", "a");                            // Open a new file in wrtie mode
           if (pointer == NULL)
           while(1);

           sprintf(A_LCDarray_U8,"Done4");
        LCD_WriteString(1,1,A_LCDarray_U8);

        //FSfprintf(, "Binary number=%#16b", 0x1eff);


        //#ifdef ALLOW_FSFPRINTF
       //   int b=  FSputc ('a', pointer);
        //#endif
        char sendb[]="  \n  ";
        if (FSfwrite (sendb,1, 3, pointer) != 3)             // Write 21 1-byte objects from sendBuffer into the file
           while(1);

          
           
           //char sendb[]="  \n heyy \n ";
        //if (FSfwrite (sendb,1, 13, pointer) != 13)             // Write 21 1-byte objects from sendBuffer into the file
           //while(1);

           if (FSfwrite (barcode, 1, 95, pointer) != 95)             // Write 95 1-byte barcodes into the file
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

    return (EXIT_SUCCESS);
}



//57 bits
//////
/*
int checkbarcode()
{
    if(barcode[4]=='0'&&barcode[5]=='0'&&barcode[6]=='1'&&barcode[7]=='0')
    {
        return 0;
    }
    else if(barcode[4]=='0'&&barcode[5]=='0'&&barcode[6]=='1'&&barcode[7]=='1')
    {
        return 0;
    }
    else if(barcode[4]=='0'&&barcode[5]=='1'&&barcode[6]=='0'&&barcode[7]=='0')
    {
        return 0;
    }
    else if(barcode[4]=='0'&&barcode[5]=='1'&&barcode[6]=='0'&&barcode[7]=='1')
    {
        return 0;
    }
    else if(barcode[4]=='0'&&barcode[5]=='1'&&barcode[6]=='1'&&barcode[7]=='0')
    {
        return 0;
    }
    else if(barcode[4]=='1'&&barcode[5]=='0'&&barcode[6]=='0'&&barcode[7]=='0')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void reversecode()
{
    int i=0; char c;

    while(i<28)
    {
        c=barcode[i];
        barcode[i]=barcode[56-i];
        barcode[56-i]=c;
        i++;
    }
}

int checkvalid()
{
    int i=0;
    if(barcode[0]=='1'&&barcode[1]=='0'&&barcode[2]=='1'&&barcode[54]=='1'
            &&barcode[55]=='0'&&barcode[56]=='1'&&barcode[27]=='0'&&barcode[28]=='1'&&barcode[29]=='0')
    {
        if(barcode[3]=='0'&&barcode[8]=='1'&&barcode[9]=='0'&&barcode[14]=='1'&&barcode[15]=='0'&&
                barcode[20]=='1'&&barcode[21]=='0'&&barcode[26]=='1'&&barcode[30]=='1'&&barcode[35]=='0'&&
                barcode[36]=='1'&&barcode[41]=='0'&&barcode[42]=='1'&&barcode[47]=='0'&&barcode[48]=='1'&&
                barcode[53]=='0')
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

int decode(char a, char b, char c, char d)
{
    if(a=='0'&&b=='0'&&c=='1'&&d=='0')
        return 0;
    if(a=='1'&&b=='1'&&c=='0'&&d=='1')
        return 0;
    if(a=='0'&&b=='0'&&c=='1'&&d=='1')
        return 1;
    if(a=='1'&&b=='1'&&c=='0'&&d=='0')
        return 1;
    if(a=='0'&&b=='1'&&c=='0'&&d=='0')
        return 2;
    if(a=='1'&&b=='0'&&c=='1'&&d=='1')
        return 2;
    if(a=='0'&&b=='1'&&c=='0'&&d=='1')
        return 3;
    if(a=='1'&&b=='0'&&c=='1'&&d=='0')
        return 3;
    if(a=='0'&&b=='1'&&c=='1'&&d=='0')
        return 4;
    if(a=='1'&&b=='0'&&c=='0'&&d=='1')
        return 4;
    if(a=='1'&&b=='0'&&c=='0'&&d=='0')
        return 5;
    if(a=='0'&&b=='1'&&c=='1'&&d=='1')
        return 5;

    else
    {
        return 9;
    }


}
*/