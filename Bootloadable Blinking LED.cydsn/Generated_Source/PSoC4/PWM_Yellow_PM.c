/*******************************************************************************
* File Name: PWM_Yellow_PM.c
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
#include "PWM_Yellow.h"

static PWM_Yellow_backupStruct PWM_Yellow_backup;


/*******************************************************************************
* Function Name: PWM_Yellow_SaveConfig
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
*  PWM_Yellow_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void PWM_Yellow_SaveConfig(void) 
{
    
    #if(!PWM_Yellow_UsingFixedFunction)
        #if(!PWM_Yellow_PWMModeIsCenterAligned)
            PWM_Yellow_backup.PWMPeriod = PWM_Yellow_ReadPeriod();
        #endif /* (!PWM_Yellow_PWMModeIsCenterAligned) */
        PWM_Yellow_backup.PWMUdb = PWM_Yellow_ReadCounter();
        #if (PWM_Yellow_UseStatus)
            PWM_Yellow_backup.InterruptMaskValue = PWM_Yellow_STATUS_MASK;
        #endif /* (PWM_Yellow_UseStatus) */
        
        #if(PWM_Yellow_DeadBandMode == PWM_Yellow__B_PWM__DBM_256_CLOCKS || \
            PWM_Yellow_DeadBandMode == PWM_Yellow__B_PWM__DBM_2_4_CLOCKS)
            PWM_Yellow_backup.PWMdeadBandValue = PWM_Yellow_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */
        
        #if(PWM_Yellow_KillModeMinTime)
             PWM_Yellow_backup.PWMKillCounterPeriod = PWM_Yellow_ReadKillTime();
        #endif /* (PWM_Yellow_KillModeMinTime) */
        
        #if(PWM_Yellow_UseControl)
            PWM_Yellow_backup.PWMControlRegister = PWM_Yellow_ReadControlRegister();
        #endif /* (PWM_Yellow_UseControl) */
    #endif  /* (!PWM_Yellow_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Yellow_RestoreConfig
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
*  PWM_Yellow_backup:  Variables of this global structure are used to  
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Yellow_RestoreConfig(void) 
{
        #if(!PWM_Yellow_UsingFixedFunction)
            #if(!PWM_Yellow_PWMModeIsCenterAligned)
                PWM_Yellow_WritePeriod(PWM_Yellow_backup.PWMPeriod);
            #endif /* (!PWM_Yellow_PWMModeIsCenterAligned) */
            PWM_Yellow_WriteCounter(PWM_Yellow_backup.PWMUdb);
            #if (PWM_Yellow_UseStatus)
                PWM_Yellow_STATUS_MASK = PWM_Yellow_backup.InterruptMaskValue;
            #endif /* (PWM_Yellow_UseStatus) */
            
            #if(PWM_Yellow_DeadBandMode == PWM_Yellow__B_PWM__DBM_256_CLOCKS || \
                PWM_Yellow_DeadBandMode == PWM_Yellow__B_PWM__DBM_2_4_CLOCKS)
                PWM_Yellow_WriteDeadTime(PWM_Yellow_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
            #if(PWM_Yellow_KillModeMinTime)
                PWM_Yellow_WriteKillTime(PWM_Yellow_backup.PWMKillCounterPeriod);
            #endif /* (PWM_Yellow_KillModeMinTime) */
            
            #if(PWM_Yellow_UseControl)
                PWM_Yellow_WriteControlRegister(PWM_Yellow_backup.PWMControlRegister); 
            #endif /* (PWM_Yellow_UseControl) */
        #endif  /* (!PWM_Yellow_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Yellow_Sleep
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
*  PWM_Yellow_backup.PWMEnableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Yellow_Sleep(void) 
{
    #if(PWM_Yellow_UseControl)
        if(PWM_Yellow_CTRL_ENABLE == (PWM_Yellow_CONTROL & PWM_Yellow_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Yellow_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Yellow_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Yellow_UseControl) */

    /* Stop component */
    PWM_Yellow_Stop();
    
    /* Save registers configuration */
    PWM_Yellow_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Yellow_Wakeup
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
*  PWM_Yellow_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Yellow_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Yellow_RestoreConfig();
    
    if(PWM_Yellow_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Yellow_Enable();
    } /* Do nothing if component's block was disabled before */
    
}


/* [] END OF FILE */
