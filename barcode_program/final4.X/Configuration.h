/* 
 * File:   Configuration.h
 * Author: ankita
 *
 * Created on August 19, 2014, 3:06 AM
 */

#ifndef CONFIGURATION_H
#define	CONFIGURATION_H

// Digital IO Direction Constant
#define DIR_IN 1
#define DIR_OUT 0

// SPI Port Details

#define SPI1_EN 1
#define SPI2_EN 1

#define SLAVE 0
#define MASTER 1

#define SPI1_MODE MASTER
#define SPI2_MODE SLAVE

// SPI1 Port Configuration

#if (SPI1_MODE == MASTER)
	#define SPI1_CS OUT_PIN_PPS_RP20	// Check for the input or output if SLAVE or MASTER mode
	#define SPI1_CLK OUT_PIN_PPS_RP23
#endif
#if (SPI1_MODE == SLAVE)
	#define SPI1_CS IN_PIN_PPS_RP20	// Check for the input or output if SLAVE or MASTER mode
	#define SPI1_CLK IN_PIN_PPS_RP23
#endif

#define SPI1_DI OUT_PIN_PPS_RP25
#define SPI1_DO IN_PIN_PPS_RP22

#define SPI1_CS_DIR	_TRISD5
#define SPI1_DI_DIR	_TRISD4
#define SPI1_DO_DIR	_TRISD3
#define SPI1_CLK_DIR _TRISD2

//configuration settings for 24FJ256GB206 device
_CONFIG1(FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
_CONFIG2(POSCMOD_HS & IOL1WAY_ON & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_OFF)


#endif	/* CONFIGURATION_H */

