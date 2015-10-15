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

#define USE_AND_OR		// Macro to use Periheral Lib
#include <p24fxxxx.h>
#include <PIC24F_periph_features.h>
#include <ports.h>
#include <spi.h>
#include <pps.h>

#include "FSIO.h"
#include "Configuration.h"


/****Decleration of global variables***/

char sendBuffer[] = "This is test string 1";
char send2[] = "2";
char receiveBuffer[50];

    
int main (void)
{
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
   
   #ifdef ALLOW_WRITES                                                  // Macro to Enable write operation
       pointer = FSfopen ("FILE1.TXT", "w");                            // Open a new file in wrtie mode
           if (pointer == NULL)
           while(1);

           if (FSfwrite (sendBuffer, 1, 21, pointer) != 21)             // Write 21 1-byte objects from sendBuffer into the file
           while(1);

           if (FSftell (pointer) != 21)                                 // FSftell returns the file's current position(i.e. 21)
           while(1);

           if (FSfseek(pointer, 1, SEEK_END))                           // File Pointer is pointing to the EOF which is one byte away from it
           while(1);

           if (FSfwrite (send2, 1, 1, pointer) != 1)                    // Write 1 1-byte object from send2 into the file
           while(1);

           if (FSfclose (pointer))                                      // Close the File
           while(1);

       pointer = FSfopen ("FILE2.TXT", "w");                            //Open a new file in wrtie mode
           if (pointer == NULL)
           while(1);

           if (FSfwrite (sendBuffer, 1, 21, pointer) != 21)             // Write 21 1-byte objects from sendBuffer into the file
           while(1);

           if (FSfclose (pointer))                                      // Close the File
           while(1);

  #endif

  /*******Switch on LED2 to confirm File Write operation*******/
      TRISEbits.TRISE2 = 0;
      PORTEbits.RE2 = 1;
  /*****************************************************************************/

 /*********************************************************************
       The present contents of our card should look like this:
       \ -> FILE1.TXT  (This is test string 2)
         -> FILE2.TXT  (This is test string 1)
  *********************************************************************/

  /*********************** READ OPERATION IN SD CARD **************************/

      pointer = FSfopen ("FILE1.TXT", "r");                             // Open file 1 in read mode
          if (pointer == NULL)
          while(1);

          if (FSfread (receiveBuffer, 3, 1, pointer) != 1)              // Read one three-byte object
          while(1);

          if (FSfeof (pointer))                                         // Check if this is the end of the file- it shouldn't be
          while(1);

          if (FSfclose (pointer))                                       // Close the file
          while(1);

          if ((receiveBuffer[0] != 'T') ||(receiveBuffer[1] != 'h')  ||(receiveBuffer[2] != 'i'))          // Make sure you read correctly
          {
               while(1);
          }
  /*******Switch on LED3 to confirm File Read Operation*******/
      TRISEbits.TRISE3 = 0;
      PORTEbits.RE3 = 1;
  /*****************************************************************************/

  /*********************************************************************
       The final contents of our card should look like this:
       \ -> FILE1.TXT  (This is test string 2)
         -> FILE2.TXT  (This is test string 1)
   *********************************************************************/

   /********************** CREATE DIRECTORY IN SD CARD **************************
                            DIRECTORY INSTRUCTION
     -> TO Create a small directory tree
        -> Beginning the path string with a '.' will create the tree in the current directory.
        -> Beginning with a '..' would create the tree in the previous directory.
        -> Beginning with just a '\' would create the tree in the root directory.
        -> Beginning with a dir name would also create the tree in the current directory
   *****************************************************************************/
   #ifdef ALLOW_DIRS                                                    // Macro to enable directory operation

         if (FSmkdir (".\\ONE\\TWO\\THREE"))                            // The directory tree will be created in the current directory
         while(1);

         if (FSchdir ("ONE\\TWO\\THREE"))                               // Change to directory THREE in our new tree
         while(1);


         if (FSmkdir ("FOUR\\FIVE\\SIX"))                               // Create another tree in directory THREE
         while(1);

         pointer = FSfopen ("FILE3.TXT", "w");                          // Create a third file in directory THREE
             if (pointer == NULL)
             while(1);

         if (FSfwrite (send2, 1, 1, pointer) != 1)                      // Write 1 1-byte object from send2 into the file
         while(1);

         if (FSfclose (pointer))                                        // Close the file
         while(1);

         if (FSchdir ("\\"))                                            // Change Directory to the root directory
         while(1);

   #endif

   /*********************************************************************
   The present contents of our card should look like this:
   \ -> FILE1.TXT  (This is test string 2)
     -> FILE2.TXT  (This is test string 1) 
     -> ONE       -> TWO   -> THREE -> FILE3.TXT (2)
                                    -> FOUR      -> FIVE -> SIX
   *********************************************************************/

   /*******************************FILE SEARCHING******************************
      Find the first TXT file with any (or none) of those attributes that has a name beginning with the letters "FILE"
      These functions are more useful for finding out which files are in your current working directory
   ***************************************************************************/
   #ifdef ALLOW_FILESEARCH
   
        attributes = ATTR_DIRECTORY | ATTR_ARCHIVE | ATTR_READ_ONLY | ATTR_HIDDEN;         // Set attributes
  
        if (FindFirst ("FILE*.TXT", attributes, &rec))
        while(1);

        while(rec.filename[4] != '2')                                     // Keep finding files until we get FILE2.TXT
        {
            if (FindNext (&rec))
            while(1);
        }

        if (FSremove (rec.filename))                                      // Delete file 2
        while(1);
  #endif

  
/*********************************************************************
   The final contents of our card should look like this:
   \ -> FILE1.TXT  (This is test string 2)
     -> ONE       -> TWO     -> THREE -> FILE3.TXT
                                      -> FOUR      -> FIVE       -> SIX
*********************************************************************/
   while(1);
}








