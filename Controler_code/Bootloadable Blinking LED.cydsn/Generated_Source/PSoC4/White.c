/*******************************************************************************
* File Name: White.c  
* Version 2.0
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "White.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        White_PC =   (White_PC & \
                                (uint32)(~(uint32)(White_DRIVE_MODE_IND_MASK << (White_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (White_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: White_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void White_Write(uint8 value) 
{
    uint8 drVal = (uint8)(White_DR & (uint8)(~White_MASK));
    drVal = (drVal | ((uint8)(value << White_SHIFT) & White_MASK));
    White_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: White_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  White_DM_STRONG     Strong Drive 
*  White_DM_OD_HI      Open Drain, Drives High 
*  White_DM_OD_LO      Open Drain, Drives Low 
*  White_DM_RES_UP     Resistive Pull Up 
*  White_DM_RES_DWN    Resistive Pull Down 
*  White_DM_RES_UPDWN  Resistive Pull Up/Down 
*  White_DM_DIG_HIZ    High Impedance Digital 
*  White_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void White_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(White__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: White_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro White_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 White_Read(void) 
{
    return (uint8)((White_PS & White_MASK) >> White_SHIFT);
}


/*******************************************************************************
* Function Name: White_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 White_ReadDataReg(void) 
{
    return (uint8)((White_DR & White_MASK) >> White_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(White_INTSTAT) 

    /*******************************************************************************
    * Function Name: White_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 White_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(White_INTSTAT & White_MASK);
		White_INTSTAT = maskedStatus;
        return maskedStatus >> White_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
