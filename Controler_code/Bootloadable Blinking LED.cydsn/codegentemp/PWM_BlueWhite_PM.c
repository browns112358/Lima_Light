/*******************************************************************************
* File Name: PWM_BlueWhite_PM.c
* Version 3.0
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "cytypes.h"
#include "PWM_BlueWhite.h"

static PWM_BlueWhite_backupStruct PWM_BlueWhite_backup;


/*******************************************************************************
* Function Name: PWM_BlueWhite_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  PWM_BlueWhite_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void PWM_BlueWhite_SaveConfig(void) 
{
    
    #if(!PWM_BlueWhite_UsingFixedFunction)
        #if(!PWM_BlueWhite_PWMModeIsCenterAligned)
            PWM_BlueWhite_backup.PWMPeriod = PWM_BlueWhite_ReadPeriod();
        #endif /* (!PWM_BlueWhite_PWMModeIsCenterAligned) */
        PWM_BlueWhite_backup.PWMUdb = PWM_BlueWhite_ReadCounter();
        #if (PWM_BlueWhite_UseStatus)
            PWM_BlueWhite_backup.InterruptMaskValue = PWM_BlueWhite_STATUS_MASK;
        #endif /* (PWM_BlueWhite_UseStatus) */
        
        #if(PWM_BlueWhite_DeadBandMode == PWM_BlueWhite__B_PWM__DBM_256_CLOCKS || \
            PWM_BlueWhite_DeadBandMode == PWM_BlueWhite__B_PWM__DBM_2_4_CLOCKS)
            PWM_BlueWhite_backup.PWMdeadBandValue = PWM_BlueWhite_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */
        
        #if(PWM_BlueWhite_KillModeMinTime)
             PWM_BlueWhite_backup.PWMKillCounterPeriod = PWM_BlueWhite_ReadKillTime();
        #endif /* (PWM_BlueWhite_KillModeMinTime) */
        
        #if(PWM_BlueWhite_UseControl)
            PWM_BlueWhite_backup.PWMControlRegister = PWM_BlueWhite_ReadControlRegister();
        #endif /* (PWM_BlueWhite_UseControl) */
    #endif  /* (!PWM_BlueWhite_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_BlueWhite_RestoreConfig
********************************************************************************
* 
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  PWM_BlueWhite_backup:  Variables of this global structure are used to  
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_BlueWhite_RestoreConfig(void) 
{
        #if(!PWM_BlueWhite_UsingFixedFunction)
            #if(!PWM_BlueWhite_PWMModeIsCenterAligned)
                PWM_BlueWhite_WritePeriod(PWM_BlueWhite_backup.PWMPeriod);
            #endif /* (!PWM_BlueWhite_PWMModeIsCenterAligned) */
            PWM_BlueWhite_WriteCounter(PWM_BlueWhite_backup.PWMUdb);
            #if (PWM_BlueWhite_UseStatus)
                PWM_BlueWhite_STATUS_MASK = PWM_BlueWhite_backup.InterruptMaskValue;
            #endif /* (PWM_BlueWhite_UseStatus) */
            
            #if(PWM_BlueWhite_DeadBandMode == PWM_BlueWhite__B_PWM__DBM_256_CLOCKS || \
                PWM_BlueWhite_DeadBandMode == PWM_BlueWhite__B_PWM__DBM_2_4_CLOCKS)
                PWM_BlueWhite_WriteDeadTime(PWM_BlueWhite_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
            #if(PWM_BlueWhite_KillModeMinTime)
                PWM_BlueWhite_WriteKillTime(PWM_BlueWhite_backup.PWMKillCounterPeriod);
            #endif /* (PWM_BlueWhite_KillModeMinTime) */
            
            #if(PWM_BlueWhite_UseControl)
                PWM_BlueWhite_WriteControlRegister(PWM_BlueWhite_backup.PWMControlRegister); 
            #endif /* (PWM_BlueWhite_UseControl) */
        #endif  /* (!PWM_BlueWhite_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_BlueWhite_Sleep
********************************************************************************
* 
* Summary:
*  Disables block's operation and saves the user configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  PWM_BlueWhite_backup.PWMEnableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_BlueWhite_Sleep(void) 
{
    #if(PWM_BlueWhite_UseControl)
        if(PWM_BlueWhite_CTRL_ENABLE == (PWM_BlueWhite_CONTROL & PWM_BlueWhite_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_BlueWhite_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_BlueWhite_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_BlueWhite_UseControl) */

    /* Stop component */
    PWM_BlueWhite_Stop();
    
    /* Save registers configuration */
    PWM_BlueWhite_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_BlueWhite_Wakeup
********************************************************************************
* 
* Summary:
*  Restores and enables the user configuration. Should be called just after 
*  awaking from sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  PWM_BlueWhite_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_BlueWhite_Wakeup(void) 
{
     /* Restore registers values */
    PWM_BlueWhite_RestoreConfig();
    
    if(PWM_BlueWhite_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_BlueWhite_Enable();
    } /* Do nothing if component's block was disabled before */
    
}


/* [] END OF FILE */
