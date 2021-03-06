/*
*	Copyright (C) 2010
*	Chair of Process Control Engineering,
*	Aachen University of Technology.
*	All rights reserved.
*
*	Redistribution and use in source and binary forms, with or without
*	modification, are permitted provided that the following conditions
*	are met:
*	1. Redistributions of source code must retain the above copyright
*	   notice, this list of conditions and the following disclaimer.
*	2. Redistributions in binary form must print or display the above
*	   copyright notice either during startup or must have a means for
*	   the user to view the copyright notice.
*	3. Redistributions in binary form must reproduce the above copyright
*	   notice, this list of conditions and the following disclaimer in
*		the documentation and/or other materials provided with the
*		distribution.
*	4. Neither the name of the Chair of Process Control Engineering nor
*		the name of the Aachen University of Technology may be used to
*		endorse or promote products derived from this software without
*		specific prior written permission.
*
*	THIS SOFTWARE IS PROVIDED BY THE CHAIR OF PROCESS CONTROL ENGINEERING
*	``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE CHAIR OF
*	PROCESS CONTROL ENGINEERING BE LIABLE FOR ANY DIRECT, INDIRECT,
*	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*	BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
*	OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
*	AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*	LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*	WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*	POSSIBILITY OF SUCH DAMAGE.
*/
/******************************************************************************
*
*   FILE
*   ----
*   MOD.c
*
*   History
*   -------
*   2010-11-03   File created
*
*******************************************************************************
*
*   This file is generated by the 'fb_builder' command
*
******************************************************************************/


#ifndef OV_COMPILE_LIBRARY_iec61131stdfb
#define OV_COMPILE_LIBRARY_iec61131stdfb
#endif

#define OV_DEBUG

#include "iec61131stdfb.h"
#include "stdfb_macros.h"
#include "libov/ov_macros.h"
#include "libov/ov_logfile.h"
#include "helper.h"
#include <limits.h>

OV_RESULT
iec61131stdfb_MOD_setType
(OV_INSTPTR_iec61131stdfb_MOD pobj, OV_VAR_TYPE type)
{
  if (iec61131stdfb_isConnected (Ov_PtrUpCast (fb_functionblock, pobj)))
    return OV_ERR_NOACCESS;
  else
  {
    
    switch(type & OV_VT_KSMASK)
	{
		case OV_VT_INT:
		case OV_VT_UINT:
		case OV_VT_BYTE:
		case OV_VT_INT_VEC:
		case OV_VT_UINT_VEC:
		case OV_VT_BYTE_VEC:
			pobj->v_IN1.value.vartype = type;
			pobj->v_IN2.value.vartype = type;
			pobj->v_OUT.value.vartype = type;
			return OV_ERR_OK;
		default:
			return OV_ERR_BADPARAM;
	}
		return OV_ERR_GENERIC;
  }
}



OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_MOD_IN1_set(
    OV_INSTPTR_iec61131stdfb_MOD          pobj,
    const OV_ANY*  value
) {
    OV_RESULT res;
  
  if ((value->value.vartype & OV_VT_KSMASK) == (pobj->v_IN1.value.vartype & OV_VT_KSMASK))
    return ov_variable_setanyvalue (&pobj->v_IN1, value);
  else
  {
    iec61131stdfb_freeVec(&pobj->v_IN1);
	iec61131stdfb_freeVec(&pobj->v_IN2);
	iec61131stdfb_freeVec(&pobj->v_OUT);		//free memory of preexisting out-vector
	res = iec61131stdfb_MOD_setType (pobj, value->value.vartype); 
    if (Ov_OK (res))
      return ov_variable_setanyvalue (&pobj->v_IN1, value);
    else return res;
  }
}

OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_MOD_IN2_set(
    OV_INSTPTR_iec61131stdfb_MOD          pobj,
    const OV_ANY*  value
) {
    OV_RESULT res;

	 if ((value->value.vartype & OV_VT_KSMASK) == (pobj->v_IN2.value.vartype & OV_VT_KSMASK))
		return ov_variable_setanyvalue (&pobj->v_IN2, value);
	  else
	  {
		iec61131stdfb_freeVec(&pobj->v_IN1);
		iec61131stdfb_freeVec(&pobj->v_IN2);
		iec61131stdfb_freeVec(&pobj->v_OUT);		//free memory of preexisting out-vector
		res = iec61131stdfb_MOD_setType (pobj, value->value.vartype); 
		if (Ov_OK (res))
		  return ov_variable_setanyvalue (&pobj->v_IN2, value);
		else return res;
	  }

}

OV_DLLFNCEXPORT OV_ANY* iec61131stdfb_MOD_OUT_get(
    OV_INSTPTR_iec61131stdfb_MOD          pobj
) {
    return &pobj->v_OUT;
}


OV_DLLFNCEXPORT void iec61131stdfb_MOD_destructor(OV_INSTPTR_ov_object pobj) {

	OV_INSTPTR_iec61131stdfb_MOD pinst = Ov_StaticPtrCast(iec61131stdfb_MOD, pobj);
	
	iec61131stdfb_freeVec(&pinst->v_IN1);
	iec61131stdfb_freeVec(&pinst->v_IN2);
	iec61131stdfb_freeVec(&pinst->v_OUT);
	fb_functionblock_destructor(pobj);
}

OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_MOD_constructor(OV_INSTPTR_ov_object pobj) {

	OV_RESULT res;
	OV_INSTPTR_iec61131stdfb_MOD pinst = Ov_StaticPtrCast(iec61131stdfb_MOD, pobj);
	
	res = fb_functionblock_constructor(pobj);
	
	if(Ov_OK(res))
	{
		pinst->v_IN1.value.valueunion.val_double = 0;
		pinst->v_IN2.value.valueunion.val_double = 0;
		pinst->v_OUT.value.valueunion.val_double = 0;
		pinst->v_IN1.value.vartype = OV_VT_INT;
		pinst->v_IN2.value.vartype = OV_VT_INT;
		pinst->v_OUT.value.vartype = OV_VT_INT;
		return OV_ERR_OK;
	}
	else
		return res;
}


OV_DLLFNCEXPORT void iec61131stdfb_MOD_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
    /*    
    *   local variables
    */
	unsigned int i;

#define STDFB_STATE_CHECK
	OV_BOOL STDFB_bad_operation = FALSE;
	
    OV_INSTPTR_iec61131stdfb_MOD pinst = Ov_StaticPtrCast(iec61131stdfb_MOD, pfb);
	
		
	iec61131stdfb_freeVec(&pinst->v_OUT);		//free memory of preexisting out-vector
	if(!(pinst->v_IN1.value.vartype & OV_VT_ISVECTOR))
	{
		switch(pinst->v_IN1.value.vartype & OV_VT_KSMASK)
		{
			
			case OV_VT_INT:
				pinst->v_OUT.value.vartype = OV_VT_INT;
				if((pinst->v_IN2.value.valueunion.val_int))
					pinst->v_OUT.value.valueunion.val_int = pinst->v_IN1.value.valueunion.val_int % pinst->v_IN2.value.valueunion.val_int;
				else
				{
					pinst->v_OUT.value.valueunion.val_int = OV_VL_MAXINT;
					STDFB_bad_operation = TRUE;
				}
			break;
			
			case OV_VT_UINT:
				pinst->v_OUT.value.vartype = OV_VT_UINT;
				if((pinst->v_IN2.value.valueunion.val_uint))
					pinst->v_OUT.value.valueunion.val_uint = pinst->v_IN1.value.valueunion.val_uint % pinst->v_IN2.value.valueunion.val_uint;
				else
				{
					pinst->v_OUT.value.valueunion.val_uint = OV_VL_MAXUINT;
					STDFB_bad_operation = TRUE;
				}
			break;
			
			case OV_VT_BYTE:
				pinst->v_OUT.value.vartype = OV_VT_BYTE;
				if((pinst->v_IN2.value.valueunion.val_byte))
				{
					pinst->v_OUT.value.valueunion.val_byte = pinst->v_IN1.value.valueunion.val_byte % pinst->v_IN2.value.valueunion.val_byte;
					ov_logfile_warning("%s: division of bitstring", pinst->v_identifier);
				}				
				else
				{
					pinst->v_OUT.value.valueunion.val_int = 0xff;
					STDFB_bad_operation = TRUE;
				}
			break;
			
			
			default:
				pinst->v_OUT.value.vartype = OV_VT_BOOL;
				pinst->v_OUT.value.valueunion.val_bool = FALSE;
				ov_logfile_alert("%s: modulo can be used on integer types only", pinst->v_identifier);
				STDFB_bad_operation = TRUE;
			break;
		}
	}
	else
	{
		switch(pinst->v_IN1.value.vartype & OV_VT_KSMASK)
		{
			
			case OV_VT_INT_VEC:
				STDFB_VEC_MODS(INT, int);
			break;
			
			case OV_VT_UINT_VEC:
				STDFB_VEC_MOD(UINT, uint);
			break;
			
			case OV_VT_BYTE_VEC:
				ov_logfile_warning("%s: modulo of bitstrings requested", pinst->v_identifier);
				STDFB_VEC_MOD(BYTE, byte);
			break;
			
								
			default:
				pinst->v_OUT.value.vartype = OV_VT_BOOL;
				pinst->v_OUT.value.valueunion.val_bool = FALSE;
				ov_logfile_alert("%s: modulo permitted on integer datatypes only", pinst->v_identifier);
				STDFB_bad_operation = TRUE;
			break;
		}
	}

	/************** handling states and timestamps ********************************/
		
#include "state_2in.c"	

	
	
    return;
}

