
/******************************************************************************
*
*   FILE
*   ----
*   KSApiCommon.c
*
*   History
*   -------
*   2013-05-14   File created
*
*******************************************************************************
*
*   This file is generated by the 'acplt_builder' command
*
******************************************************************************/


#ifndef OV_COMPILE_LIBRARY_ksapi
#define OV_COMPILE_LIBRARY_ksapi
#endif


#include "ksapi.h"
#include "libov/ov_macros.h"
#include "ksapi_commonFuncs.h"
#include "ks_logfile.h"


OV_DLLFNCEXPORT void ksapi_KSApiCommon_startup(
	OV_INSTPTR_ov_object 	pobj
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_ksapi_KSApiCommon pinst = Ov_StaticPtrCast(ksapi_KSApiCommon, pobj);

    /* do what the base class does first */
    ov_object_startup(pobj);

    /* do what */
    pinst->v_result = OV_ERR_OK;
    pinst->v_status = KSAPI_COMMON_INITIAL;

    return;
}

OV_DLLFNCEXPORT void ksapi_KSApiCommon_shutdown(
	OV_INSTPTR_ov_object 	pobj
) {
    /*    
    *   local variables
    */

    /* do what */

    /* set the object's state to "shut down" */
    ov_object_shutdown(pobj);

    return;
}

OV_DLLFNCEXPORT OV_RESULT ksapi_KSApiCommon_Reset_set(OV_INSTPTR_ksapi_KSApiCommon pobj, OV_BOOL value)
{
	OV_INSTPTR_ksbase_ClientBase pClient = NULL;
	OV_VTBLPTR_ksbase_ClientBase pVtblClient = NULL;
	OV_RESULT result = OV_ERR_OK;

	if(value && (!pobj->v_Reset))
	{
		pobj->v_status = KSAPI_COMMON_INITIAL;
		pobj->v_result = OV_ERR_OK;
		Ov_ForEachChildEx(ov_containment, pobj, pClient, ksbase_ClientBase)
		{	/*	find the object in the containment which is derived from ClientBase	*/
			break;
		}

		if(pClient)
		{
			Ov_GetVTablePtr(ksbase_ClientBase, pVtblClient, pClient);
			if(pVtblClient)
			{
				result = pVtblClient->m_reset(pClient);
			}
		}
	}

	pobj->v_Reset = value;
	return result;
}

OV_DLLFNCEXPORT OV_RESULT ksapi_KSApiCommon_Submit_set(OV_INSTPTR_ksapi_KSApiCommon pobj, OV_BOOL value)
{
	OV_VTBLPTR_ksapi_KSApiCommon pVtblthis = NULL;

	if(value && (!pobj->v_Submit))
	{
		Ov_GetVTablePtr(ksapi_KSApiCommon, pVtblthis, pobj);
		if(!pVtblthis)
			return OV_ERR_BADOBJTYPE;

		pVtblthis->m_submit(pobj);
	}

	pobj->v_Submit = value;
	return OV_ERR_OK;
}

OV_DLLFNCEXPORT void ksapi_KSApiCommon_submit(
	OV_INSTPTR_ksapi_KSApiCommon          pobj
) {
	return;
}

OV_DLLFNCEXPORT OV_RESULT ksapi_KSApiCommon_prepareSubmit(
		OV_INSTPTR_ksapi_KSApiCommon	 			pobj,
		OV_INSTPTR_ksbase_ClientBase*				pClient,
		OV_VTBLPTR_ksbase_ClientBase*				pVtblClient
)
{
	OV_RESULT result;

	if(!pobj->v_serverHost)
	{
		KS_logfile_error(("%s: no serverHost set. aborting", pobj->v_identifier));
		pobj->v_status = KSAPI_COMMON_INTERNALERROR;
		pobj->v_result = OV_ERR_BADPARAM;
		return OV_ERR_BADPARAM;
	}

	result = ksapi_getClientPointers(pobj, pClient, pVtblClient);
	if(Ov_Fail(result))
	{
		KS_logfile_error(("%s: submit: no Client found. Cannot submit", pobj->v_identifier));
		pobj->v_status = KSAPI_COMMON_INTERNALERROR;
		pobj->v_result = result;
		return result;
	}

	result = ksbase_ClientBase_serverHost_set(*pClient, pobj->v_serverHost);
	if(Ov_Fail(result))
	{
		KS_logfile_error(("%s: submit: could not set serverHost at Client", pobj->v_identifier));
		pobj->v_status = KSAPI_COMMON_INTERNALERROR;
		pobj->v_result = result;
		return result;
	}

	if(pobj->v_serverName)
	{
		result = ksbase_ClientBase_serverName_set(*pClient, pobj->v_serverName);
		if(Ov_Fail(result))
		{
			KS_logfile_error(("%s: submit: could not set serverName at Client", pobj->v_identifier));
			pobj->v_status = KSAPI_COMMON_INTERNALERROR;
			pobj->v_result = result;
			return result;
		}
	}

	(*pClient)->v_holdConnection = pobj->v_holdConnection;
	return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT ksapi_KSApiCommon_genSetForSubmit(
		OV_INSTPTR_ksapi_KSApiCommon	 			pobj,
		OV_STRING 									serverHost,
		OV_STRING 									serverName,
		OV_STRING 									path
){
	OV_RESULT result;

	result = ov_string_setvalue(&(pobj->v_serverHost), serverHost);
	if(Ov_Fail(result))
	{
		pobj->v_status = KSAPI_COMMON_INTERNALERROR;
		pobj->v_result = result;
		return result;
	}

	result = ov_string_setvalue(&(pobj->v_serverName), serverName);
	if(Ov_Fail(result))
	{
		pobj->v_status = KSAPI_COMMON_INTERNALERROR;
		pobj->v_result = result;
		return result;
	}
	result = ov_string_setvalue(&(pobj->v_path), path);
	if(Ov_Fail(result))
	{
		pobj->v_status = KSAPI_COMMON_INTERNALERROR;
		pobj->v_result = result;
		return result;
	}

	return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_ACCESS ksapi_KSApiCommon_getaccess(
		OV_INSTPTR_ov_object		pobj,
		const OV_ELEMENT			*pelem,
		const OV_TICKET				*pticket
) {
	/*
	 *	local variables
	*/

	/*
	*	switch based on the element's type
	*/
	switch(pelem->elemtype) {
		case OV_ET_VARIABLE:
			if(pelem->elemunion.pvar->v_offset >= offsetof(OV_INST_ov_object,__classinfo)) {
			  if(pelem->elemunion.pvar->v_vartype == OV_VT_CTYPE)
				  return OV_AC_NONE;
			  else
				  return OV_AC_READWRITE;
			}
			break;
		default:
			break;
	}

	return ov_object_getaccess(pobj, pelem, pticket);
}

