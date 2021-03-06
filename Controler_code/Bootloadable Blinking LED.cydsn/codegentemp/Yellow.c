/*******************************************************************************
* File Name: Yellow.c  
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
#include "Yellow.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Yellow_PC =   (Yellow_PC & \
                                (uint32)(~(uint32)(Yellow_DRIVE_MODE_IND_MASK << (Yellow_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Yellow_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Yellow_Write
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
void Yellow_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Yellow_DR & (uint8)(~Yellow_MASK));
    drVal = (drVal | ((uint8)(value << Yellow_SHIFT) & Yellow_MASK));
    Yellow_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Yellow_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Yellow_DM_STRONG     Strong Drive 
*  Yellow_DM_OD_HI      Open Drain, Drives High 
*  Yellow_DM_OD_LO      Open Drain, Drives Low 
*  Yellow_DM_RES_UP     Resistive Pull Up 
*  Yellow_DM_RES_DWN    Resistive Pull Down 
*  Yellow_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Yellow_DM_DIG_HIZ    High Impedance Digital 
*  Yellow_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Yellow_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Yellow__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Yellow_Read
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
*  Macro Yellow_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Yellow_Read(void) 
{
    return (uint8)((Yellow_PS & Yellow_MASK) >> Yellow_SHIFT);
}


/*******************************************************************************
* Function Name: Yellow_ReadDataReg
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
uint8 Yellow_ReadDataReg(void) 
{
    return (uint8)((Yellow_DR & Yellow_MASK) >> Yellow_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Yellow_INTSTAT) 

    /*******************************************************************************
    * Function Name: Yellow_ClearInterrupt
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
    uint8 Yellow_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Yellow_INTSTAT & Yellow_MASK);
		Yellow_INTSTAT = maskedStatus;
        return maskedStatus >> Yellow_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
