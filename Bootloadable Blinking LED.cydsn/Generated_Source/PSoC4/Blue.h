/*******************************************************************************
* File Name: Blue.h  
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

#if !defined(CY_PINS_Blue_H) /* Pins Blue_H */
#define CY_PINS_Blue_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Blue_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Blue_Write(uint8 value) ;
void    Blue_SetDriveMode(uint8 mode) ;
uint8   Blue_ReadDataReg(void) ;
uint8   Blue_Read(void) ;
uint8   Blue_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Blue_DRIVE_MODE_BITS        (3)
#define Blue_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Blue_DRIVE_MODE_BITS))
#define Blue_DRIVE_MODE_SHIFT       (0x00u)
#define Blue_DRIVE_MODE_MASK        (0x07u << Blue_DRIVE_MODE_SHIFT)

#define Blue_DM_ALG_HIZ         (0x00u << Blue_DRIVE_MODE_SHIFT)
#define Blue_DM_DIG_HIZ         (0x01u << Blue_DRIVE_MODE_SHIFT)
#define Blue_DM_RES_UP          (0x02u << Blue_DRIVE_MODE_SHIFT)
#define Blue_DM_RES_DWN         (0x03u << Blue_DRIVE_MODE_SHIFT)
#define Blue_DM_OD_LO           (0x04u << Blue_DRIVE_MODE_SHIFT)
#define Blue_DM_OD_HI           (0x05u << Blue_DRIVE_MODE_SHIFT)
#define Blue_DM_STRONG          (0x06u << Blue_DRIVE_MODE_SHIFT)
#define Blue_DM_RES_UPDWN       (0x07u << Blue_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Blue_MASK               Blue__MASK
#define Blue_SHIFT              Blue__SHIFT
#define Blue_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Blue_PS                     (* (reg32 *) Blue__PS)
/* Port Configuration */
#define Blue_PC                     (* (reg32 *) Blue__PC)
/* Data Register */
#define Blue_DR                     (* (reg32 *) Blue__DR)
/* Input Buffer Disable Override */
#define Blue_INP_DIS                (* (reg32 *) Blue__PC2)


#if defined(Blue__INTSTAT)  /* Interrupt Registers */

    #define Blue_INTSTAT                (* (reg32 *) Blue__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Blue_H */


/* [] END OF FILE */
