/*******************************************************************************
* File Name: White.h  
* Version 2.0
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_White_H) /* Pins White_H */
#define CY_PINS_White_H

#include "cytypes.h"
#include "cyfitter.h"
#include "White_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    White_Write(uint8 value) ;
void    White_SetDriveMode(uint8 mode) ;
uint8   White_ReadDataReg(void) ;
uint8   White_Read(void) ;
uint8   White_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define White_DRIVE_MODE_BITS        (3)
#define White_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - White_DRIVE_MODE_BITS))
#define White_DRIVE_MODE_SHIFT       (0x00u)
#define White_DRIVE_MODE_MASK        (0x07u << White_DRIVE_MODE_SHIFT)

#define White_DM_ALG_HIZ         (0x00u << White_DRIVE_MODE_SHIFT)
#define White_DM_DIG_HIZ         (0x01u << White_DRIVE_MODE_SHIFT)
#define White_DM_RES_UP          (0x02u << White_DRIVE_MODE_SHIFT)
#define White_DM_RES_DWN         (0x03u << White_DRIVE_MODE_SHIFT)
#define White_DM_OD_LO           (0x04u << White_DRIVE_MODE_SHIFT)
#define White_DM_OD_HI           (0x05u << White_DRIVE_MODE_SHIFT)
#define White_DM_STRONG          (0x06u << White_DRIVE_MODE_SHIFT)
#define White_DM_RES_UPDWN       (0x07u << White_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define White_MASK               White__MASK
#define White_SHIFT              White__SHIFT
#define White_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define White_PS                     (* (reg32 *) White__PS)
/* Port Configuration */
#define White_PC                     (* (reg32 *) White__PC)
/* Data Register */
#define White_DR                     (* (reg32 *) White__DR)
/* Input Buffer Disable Override */
#define White_INP_DIS                (* (reg32 *) White__PC2)


#if defined(White__INTSTAT)  /* Interrupt Registers */

    #define White_INTSTAT                (* (reg32 *) White__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins White_H */


/* [] END OF FILE */
