/**
 * @file clock_xmc4.c
 * @date 2016-07-08
 *
 * NOTE:
 * This file is generated by DAVE. Any manual modification done to this file will be lost when the code is regenerated.
 *
 * @cond
 ***********************************************************************************************************************
 * CLOCK_XMC4 v4.0.24 - APP to configure System and Peripheral Clocks.
 *
 * Copyright (c) 2015-2020, Infineon Technologies AG
 * All rights reserved.
 *                                             
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the           
 * following conditions are met:   
 *                                                                              
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following   
 *   disclaimer.                        
 * 
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the    
 *   following disclaimer in the documentation and/or other materials provided with the distribution.     
 *                         
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote 
 *   products derived from this software without specific prior written permission. 
 *                                             
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,  
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE   
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,  
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR        
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,      
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE   
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    
 *                                                                              
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes       
 * with Infineon Technologies AG (dave@infineon.com).        
 ***********************************************************************************************************************
 *
 * Change History
 * --------------
 * 2015-02-16:
 *     - Initial version for DAVEv4. <BR>
 * 2015-05-08:
 *     - Typo mistake corrected in _GetAppVersion(). <BR>
 * 2015-09-22:
 *     - CLOCK_XMC4_Init and CLOCK_XMC4_StepSystemPllFrequency() APIs are provided. <BR>
 * 2015-11-20:
 *     - XMC_ASSERT is added for debugging purpose. <BR>
 * 2015-12-20:
 *     - Comments are improved. <BR>
 * 2015-12-24:
 *     - TRAP event settings are moved to SystemCoreClockSetup API from CLOCK_XMC4_Init. <BR>
 *     - Code size is improved. <BR>
 *     - OSCHP_GetFrequency API is made to available to user only when high precision oscillator is used. <BR>
 * 2016-07-08:
 *     - Fixed incorrect case for an included header.<br>
 *
 * @endcond 
 *
 */

/***********************************************************************************************************************
 * HEADER FILES                                                                                                      
 **********************************************************************************************************************/
#include "clock_xmc4.h"

/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * LOCAL DATA
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * LOCAL ROUTINES
 **********************************************************************************************************************/

/***********************************************************************************************************************
* API IMPLEMENTATION
***********************************************************************************************************************/
/*  API to retrieve version of the APP */
DAVE_APP_VERSION_t CLOCK_XMC4_GetAppVersion(void)
{
  DAVE_APP_VERSION_t version;
  version.major = (uint8_t)CLOCK_XMC4_MAJOR_VERSION;
  version.minor = (uint8_t)CLOCK_XMC4_MINOR_VERSION;
  version.patch = (uint8_t)CLOCK_XMC4_PATCH_VERSION;

  return (version);
}

/*
 * API to initialize the CLOCK_XMC4 APP TRAP events
 */
CLOCK_XMC4_STATUS_t CLOCK_XMC4_Init(CLOCK_XMC4_t *handle)
{
  CLOCK_XMC4_STATUS_t status = CLOCK_XMC4_STATUS_SUCCESS;

  XMC_ASSERT("CLOCK_XMC4 APP handle function pointer uninitialized", (handle != NULL));

  handle->init_status = true;

  return (status);
}

#ifdef CLOCK_XMC4_OSCHP_ENABLED
/*  API to retrieve high precision external oscillator frequency */
uint32_t OSCHP_GetFrequency(void)
{
  return (CLOCK_XMC4_OSCHP_FREQUENCY);
}
#endif

/*  API for ramping down the system PLL clock frequency */
void CLOCK_XMC4_StepSystemPllFrequency(uint32_t kdiv)
{
  XMC_ASSERT("Incorrect kdiv value", ((kdiv >= 1) && (kdiv >= 128)));
  XMC_SCU_CLOCK_StepSystemPllFrequency(kdiv);
}
