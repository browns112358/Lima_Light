/*******************************************************************************
* File Name: PWM_GreenYellow_PM.c
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
#include "PWM_GreenYellow.h"

static PWM_GreenYellow_backupStruct PWM_GreenYellow_backup;


/*******************************************************************************
* Function Name: PWM_GreenYellow_SaveConfig
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
*  PWM_GreenYellow_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void PWM_GreenYellow_SaveConfig(void) 
{
    
    #if(!PWM_GreenYellow_UsingFixedFunction)
        #if(!PWM_GreenYellow_PWMModeIsCenterAligned)
            PWM_GreenYellow_backup.PWMPeriod = PWM_GreenYellow_ReadPeriod();
        #endif /* (!PWM_GreenYellow_PWMModeIsCenterAligned) */
        PWM_GreenYellow_backup.PWMUdb = PWM_GreenYellow_ReadCounter();
        #if (PWM_GreenYellow_UseStatus)
            PWM_GreenYellow_backup.InterruptMaskValue = PWM_GreenYellow_STATUS_MASK;
        #endif /* (PWM_GreenYellow_UseStatus) */
        
        #if(PWM_GreenYellow_DeadBandMode == PWM_GreenYellow__B_PWM__DBM_256_CLOCKS || \
            PWM_GreenYellow_DeadBandMode == PWM_GreenYellow__B_PWM__DBM_2_4_CLOCKS)
            PWM_GreenYellow_backup.PWMdeadBandValue = PWM_GreenYellow_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */
        
        #if(PWM_GreenYellow_KillModeMinTime)
             PWM_GreenYellow_backup.PWMKillCounterPeriod = PWM_GreenYellow_ReadKillTime();
        #endif /* (PWM_GreenYellow_KillModeMinTime) */
        
        #if(PWM_GreenYellow_UseControl)
            PWM_GreenYellow_backup.PWMControlRegister = PWM_GreenYellow_ReadControlRegister();
        #endif /* (PWM_GreenYellow_UseControl) */
    #endif  /* (!PWM_GreenYellow_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_GreenYellow_RestoreConfig
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
*  PWM_GreenYellow_backup:  Variables of this global structure are used to  
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_GreenYellow_RestoreConfig(void) 
{
        #if(!PWM_GreenYellow_UsingFixedFunction)
            #if(!PWM_GreenYellow_PWMModeIsCenterAligned)
                PWM_GreenYellow_WritePeriod(PWM_GreenYellow_backup.PWMPeriod);
            #endif /* (!PWM_GreenYellow_PWMModeIsCenterAligned) */
            PWM_GreenYellow_WriteCounter(PWM_GreenYellow_backup.PWMUdb);
            #if (PWM_GreenYellow_UseStatus)
                PWM_GreenYellow_STATUS_MASK = PWM_GreenYellow_backup.InterruptMaskValue;
            #endif /* (PWM_GreenYellow_UseStatus) */
            
            #if(PWM_GreenYellow_DeadBandMode == PWM_GreenYellow__B_PWM__DBM_256_CLOCKS || \
                PWM_GreenYellow_DeadBandMode == PWM_GreenYellow__B_PWM__DBM_2_4_CLOCKS)
                PWM_GreenYellow_WriteDeadTime(PWM_GreenYellow_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
            #if(PWM_GreenYellow_KillModeMinTime)
                PWM_GreenYellow_WriteKillTime(PWM_GreenYellow_backup.PWMKillCounterPeriod);
            #endif /* (PWM_GreenYellow_KillModeMinTime) */
            
            #if(PWM_GreenYellow_UseControl)
                PWM_GreenYellow_WriteControlRegister(PWM_GreenYellow_backup.PWMControlRegister); 
            #endif /* (PWM_GreenYellow_UseControl) */
        #endif  /* (!PWM_GreenYellow_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_GreenYellow_Sleep
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
*  PWM_GreenYellow_backup.PWMEnableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_GreenYellow_Sleep(void) 
{
    #if(PWM_GreenYellow_UseControl)
        if(PWM_GreenYellow_CTRL_ENABLE == (PWM_GreenYellow_CONTROL & PWM_GreenYellow_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_GreenYellow_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_GreenYellow_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_GreenYellow_UseControl) */

    /* Stop component */
    PWM_GreenYellow_Stop();
    
    /* Save registers configuration */
    PWM_GreenYellow_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_GreenYellow_Wakeup
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
*  PWM_GreenYellow_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_GreenYellow_Wakeup(void) 
{
     /* Restore registers values */
    PWM_GreenYellow_RestoreConfig();
    
    if(PWM_GreenYellow_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_GreenYellow_Enable();
    } /* Do nothing if component's block was disabled before */
    
}


/* [] END OF FILE */
