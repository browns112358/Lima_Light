/*******************************************************************************
* File Name: Blue.c  
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
#include "Blue.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Blue_PC =   (Blue_PC & \
                                (uint32)(~(uint32)(Blue_DRIVE_MODE_IND_MASK << (Blue_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Blue_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Blue_Write
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
void Blue_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Blue_DR & (uint8)(~Blue_MASK));
    drVal = (drVal | ((uint8)(value << Blue_SHIFT) & Blue_MASK));
    Blue_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Blue_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Blue_DM_STRONG     Strong Drive 
*  Blue_DM_OD_HI      Open Drain, Drives High 
*  Blue_DM_OD_LO      Open Drain, Drives Low 
*  Blue_DM_RES_UP     Resistive Pull Up 
*  Blue_DM_RES_DWN    Resistive Pull Down 
*  Blue_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Blue_DM_DIG_HIZ    High Impedance Digital 
*  Blue_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Blue_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Blue__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Blue_Read
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
*  Macro Blue_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Blue_Read(void) 
{
    return (uint8)((Blue_PS & Blue_MASK) >> Blue_SHIFT);
}


/*******************************************************************************
* Function Name: Blue_ReadDataReg
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
uint8 Blue_ReadDataReg(void) 
{
    return (uint8)((Blue_DR & Blue_MASK) >> Blue_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Blue_INTSTAT) 

    /*******************************************************************************
    * Function Name: Blue_ClearInterrupt
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
    uint8 Blue_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Blue_INTSTAT & Blue_MASK);
		Blue_INTSTAT = maskedStatus;
        return maskedStatus >> Blue_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
