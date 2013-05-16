
/******************************************************************************
*
*   FILE
*   ----
*   getVar.c
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


void ksapi_getVar_callback(const OV_INSTPTR_ov_domain this, const OV_INSTPTR_ov_domain that);

OV_DLLFNCEXPORT OV_RESULT ksapi_getVar_constructor(
	OV_INSTPTR_ov_object 	pobj
) {
    /*    
    *   local variables
    */
    OV_RESULT    result;

    /* do what the base class does first */
    result = ksapi_variableOperation_constructor(pobj);
    if(Ov_Fail(result))
         return result;

    /* do what */


    return OV_ERR_OK;
}

OV_DLLFNCEXPORT void ksapi_getVar_destructor(
	OV_INSTPTR_ov_object 	pobj
) {

    /* destroy object */
    ksapi_variableOperation_destructor(pobj);

    return;
}

OV_DLLFNCEXPORT void ksapi_getVar_startup(
	OV_INSTPTR_ov_object 	pobj
) {
     /* do what the base class does first */
    ksapi_variableOperation_startup(pobj);

    /* do what */


    return;
}

OV_DLLFNCEXPORT void ksapi_getVar_shutdown(
	OV_INSTPTR_ov_object 	pobj
) {
     /* do what */

    /* set the object's state to "shut down" */
    ksapi_KSApiCommon_shutdown(pobj);

    return;
}

OV_DLLFNCEXPORT void ksapi_getVar_submit(
	OV_INSTPTR_ksapi_KSApiCommon        pobj
) {
	OV_INSTPTR_ksapi_getVar	pthis = Ov_StaticPtrCast(ksapi_getVar, pobj);
	OV_INSTPTR_ksbase_ClientBase pClient = NULL;
	OV_VTBLPTR_ksbase_ClientBase pVtblClient = NULL;
	OV_INSTPTR_ksapi_Variable pCurrVar = NULL;
	OV_RESULT result;
	OV_STRING* varPaths = NULL;
	OV_UINT numberOfItems = 1;

	if(!pobj->v_serverHost)
	{
		KS_logfile_error(("%s: no serverHost set. aborting", pobj->v_identifier));
		pthis->v_status = KSAPI_COMMON_INTERNALERROR;
		pthis->v_result = OV_ERR_BADPARAM;
		return;
	}

	result = ksapi_getClientPointers(pobj, &pClient, &pVtblClient);
	if(Ov_Fail(result))
	{
		KS_logfile_error(("%s: submit: no Client found. Cannot submit", pobj->v_identifier));
		pthis->v_status = KSAPI_COMMON_INTERNALERROR;
		pthis->v_result = result;
		return;
	}

	result = ksbase_ClientBase_serverHost_set(pClient, pobj->v_serverHost);
	if(Ov_Fail(result))
	{
		KS_logfile_error(("%s: submit: could not set serverHost at Client", pobj->v_identifier));
		pthis->v_status = KSAPI_COMMON_INTERNALERROR;
		pthis->v_result = result;
		return;
	}

	if(pobj->v_serverName)
	{
		result = ksbase_ClientBase_serverName_set(pClient, pobj->v_serverName);
		if(Ov_Fail(result))
		{
			KS_logfile_error(("%s: submit: could not set serverName at Client", pobj->v_identifier));
			pthis->v_status = KSAPI_COMMON_INTERNALERROR;
			pthis->v_result = result;
			return;
		}
	}

	pClient->v_holdConnection = pthis->v_holdConnection;

	varPaths = Ov_HeapMalloc(numberOfItems * sizeof(OV_STRING));
	if(!varPaths)
	{
		pthis->v_status = KSAPI_COMMON_INTERNALERROR;
		pthis->v_result = OV_ERR_HEAPOUTOFMEMORY;
		return;
	}
	if(pthis->v_path)
	{
		varPaths[0] = pthis->v_path;	/*	see comment below	*/
	}
	else
	{
		KS_logfile_error(("%s: submit: own Variable has empty path", pobj->v_identifier));
		pthis->v_status = KSAPI_COMMON_INTERNALERROR;
		pthis->v_result = result;
		Ov_HeapFree(varPaths);
		return;
	}
	/*	iterate over variable objects in containment and linked ones and add them to the package	*/
	Ov_ForEachChildEx(ov_containment, pthis, pCurrVar, ksapi_Variable)
	{
		numberOfItems++;
		varPaths = Ov_HeapRealloc(varPaths, numberOfItems * sizeof(OV_STRING));
		if(!varPaths)
		{
			pthis->v_status = KSAPI_COMMON_INTERNALERROR;
			pthis->v_result = OV_ERR_HEAPOUTOFMEMORY;
			return;
		}
		if(pCurrVar->v_path)
		{
			varPaths[numberOfItems-1] = pCurrVar->v_path;	/*	the string will not be changed, so we do not need to copy it	*/
			pCurrVar->v_order = numberOfItems;
		}
		else
		{
			KS_logfile_error(("%s: submit: Variable %s has empty path", pobj->v_identifier, pCurrVar->v_identifier));
			pthis->v_status = KSAPI_COMMON_INTERNALERROR;
			pthis->v_result = result;
			Ov_HeapFree(varPaths);
			return;
		}
	}

	Ov_ForEachChild(ksapi_operationToVariable, pthis, pCurrVar)
	{
		numberOfItems++;
		varPaths = Ov_HeapRealloc(varPaths, numberOfItems * sizeof(OV_STRING));
		if(!varPaths)
		{
			pthis->v_status = KSAPI_COMMON_INTERNALERROR;
			pthis->v_result = OV_ERR_HEAPOUTOFMEMORY;
			return;
		}
		if(pCurrVar->v_path)
		{
			varPaths[numberOfItems-1] = pCurrVar->v_path;	/*	the string will not be changed, so we do not need to copy it	*/
			pCurrVar->v_order = numberOfItems;
		}
		else
		{
			KS_logfile_error(("%s: submit: Variable %s has empty path", pobj->v_identifier, pCurrVar->v_identifier));
			pthis->v_status = KSAPI_COMMON_INTERNALERROR;
			pthis->v_result = result;
			Ov_HeapFree(varPaths);
			return;
		}
	}


	/*	do the actual submit	*/
	pVtblClient->m_requestGetVar(pClient, NULL, numberOfItems, varPaths, (OV_INSTPTR_ov_domain) pthis,
			&ksapi_getVar_callback);

	Ov_HeapFree(varPaths);

	return;
}

OV_DLLFNCEXPORT void ksapi_getVar_setandsubmit(
    OV_INSTPTR_ksapi_getVar          pobj,
	OV_STRING 									serverHost,
	OV_STRING 									serverName,
	OV_STRING 									path
) {
	OV_RESULT result;

	result = ov_string_setvalue(&(pobj->v_serverHost), serverHost);
	if(Ov_Fail(result))
	{
		pobj->v_status = KSAPI_COMMON_INTERNALERROR;
		pobj->v_result = result;
		return;
	}

	result = ov_string_setvalue(&(pobj->v_serverName), serverName);
	if(Ov_Fail(result))
	{
		pobj->v_status = KSAPI_COMMON_INTERNALERROR;
		pobj->v_result = result;
		return;
	}
	result = ov_string_setvalue(&(pobj->v_path), path);
	if(Ov_Fail(result))
	{
		pobj->v_status = KSAPI_COMMON_INTERNALERROR;
		pobj->v_result = result;
		return;
	}

	ksapi_getVar_submit(Ov_StaticPtrCast(ksapi_KSApiCommon, pobj));

	return;
}

void ksapi_getVar_callback(const OV_INSTPTR_ov_domain this, const OV_INSTPTR_ov_domain that)
{
	OV_INSTPTR_ksapi_getVar thisGV = Ov_StaticPtrCast(ksapi_getVar, this);
	OV_INSTPTR_ksbase_ClientBase pClient = Ov_StaticPtrCast(ksbase_ClientBase, that);
	OV_INSTPTR_ksapi_Variable pCurrVar = NULL;
	OV_VTBLPTR_ksbase_ClientBase pVtblClient = NULL;
	OV_UINT itemsLength;
	OV_GETVAR_ITEM* itemsVals = NULL;
	OV_RESULT result;

	if(!this || !that)
	{
		KS_logfile_error(("callback issued with NULL pointers. aborting."));
		return;
	}

	Ov_GetVTablePtr(ksbase_ClientBase, pVtblClient, pClient);

	if(!pVtblClient)
	{
		KS_logfile_error(("%s callback: could not determine Vtable of Client %s. aborting",
				this->v_identifier, that->v_identifier));
		thisGV->v_status = KSAPI_COMMON_INTERNALERROR;
		thisGV->v_result = OV_ERR_BADOBJTYPE;
		return;
	}
	ov_memstack_lock();
	result = pVtblClient->m_processGetVar(pClient, NULL, (OV_RESULT*) &(thisGV->v_result), &itemsLength, &itemsVals);
	if(Ov_Fail(result))
	{
		thisGV->v_status = KSAPI_COMMON_INTERNALERROR;
		thisGV->v_result = result;
		ov_memstack_unlock();
		return;
	}

	if(Ov_Fail(thisGV->v_result))
	{
		thisGV->v_status = KSAPI_COMMON_EXTERNALERROR;
		ov_memstack_unlock();
		return;
	}

	thisGV->v_varRes = itemsVals[0].result;
	if(Ov_OK(thisGV->v_varRes))
	{
		result = Ov_SetAnyValue(&(thisGV->v_varValue), &(itemsVals[0].var_current_props));
		if(Ov_Fail(thisGV->v_result))
		{
			thisGV->v_status = KSAPI_COMMON_EXTERNALERROR;
			ov_memstack_unlock();
			return;
		}
	}

	/*	iterate over variable objects in containment and linked ones and fill in the results	*/
	Ov_ForEachChildEx(ov_containment, thisGV, pCurrVar, ksapi_Variable)
	{
		if(pCurrVar->v_order)
		{
			if(pCurrVar->v_order <= itemsLength)
			{
				pCurrVar->v_varRes = itemsVals[pCurrVar->v_order-1].result;
				if(Ov_OK(pCurrVar->v_varRes))
				{
					result = Ov_SetAnyValue(&(pCurrVar->v_varValue), &(itemsVals[pCurrVar->v_order-1].var_current_props));
					if(Ov_Fail(result))
					{
						thisGV->v_status = KSAPI_COMMON_INTERNALERROR;
						thisGV->v_result = result;
						ov_memstack_unlock();
						return;
					}
				}

			}
			else
			{
				pCurrVar->v_varRes = OV_ERR_BADPLACEMENT;
			}
		}
	}

	Ov_ForEachChild(ksapi_operationToVariable, thisGV, pCurrVar)
	{
		if(pCurrVar->v_order)
		{
			if(pCurrVar->v_order <= itemsLength)
			{
				pCurrVar->v_varRes = itemsVals[pCurrVar->v_order-1].result;
				if(Ov_OK(pCurrVar->v_varRes))
				{
					result = Ov_SetAnyValue(&(pCurrVar->v_varValue), &(itemsVals[pCurrVar->v_order-1].var_current_props));
					if(Ov_Fail(result))
					{
						thisGV->v_status = KSAPI_COMMON_INTERNALERROR;
						thisGV->v_result = result;
						ov_memstack_unlock();
						return;
					}
				}
			}
			else
			{
				pCurrVar->v_varRes = OV_ERR_BADPLACEMENT;
			}
		}
	}

	ov_memstack_unlock();
	return;
}
