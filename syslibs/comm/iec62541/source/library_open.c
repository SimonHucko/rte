
/******************************************************************************
*
*   FILE
*   ----
*   library_open.c
*
*   History
*   -------
*   2014-10-13   File created
*
*******************************************************************************
*
*   This file is generated by the 'acplt_builder' command
*
******************************************************************************/

#ifndef OV_COMPILE_LIBRARY_iec62541
#define OV_COMPILE_LIBRARY_iec62541
#endif

#include "iec62541.h"
#include "libov/ov_macros.h"
#include "libov/ov_result.h"
#include "libov/ov_logfile.h"
#include "libov/ov_memstack.h"
#include "libov/ov_result.h"
#ifdef ov_library_open_iec62541
#undef ov_library_open_iec62541
#endif

/*
* This function will be called, when the library is loaded.
* It could generate components and initializes the startup procedure
*/
OV_RESULT ov_library_setglobalvars_iec62541_new(void) {
	OV_RESULT result;
	/*
	 *    set the global variables of the original version
	 *    and if successful, load other libraries
	 *    and create some objects
	 */

	OV_INSTPTR_ov_domain pcommunication = NULL;
	OV_INSTPTR_ov_domain pDomOpcUa = NULL;
	OV_INSTPTR_ov_domain pDomTicketAuths = NULL;
	OV_INSTPTR_iec62541_uaIdentificator pIdentificator = NULL;
	OV_INSTPTR_iec62541_uaServer pServer = NULL;

	result = ov_library_setglobalvars_iec62541();
	if(Ov_Fail(result)){
		return result;
	}

	/*	initialize the ServiceImplementations Structure of the open62541 Stack with our service functions	*/
	//get the communication domain for putting in the ksxdr-objects
	pcommunication = Ov_StaticPtrCast(ov_domain, Ov_SearchChild(ov_containment, &(pdb->root), "communication"));
	if(!pcommunication) {
		result = Ov_CreateObject(ov_domain, pcommunication, &(pdb->root), "communication");
		if(Ov_Fail(result)) {
			ov_logfile_error("Fatal: Could not create Object 'communication'");
			return result;
		}
	}
	else if(!Ov_CanCastTo(ov_domain, (OV_INSTPTR_ov_object) pcommunication))
	{
		ov_logfile_error("Fatal: communication object found but not domain (or derived)");
		return OV_ERR_GENERIC;
	}

	pDomOpcUa = Ov_StaticPtrCast(ov_domain, Ov_SearchChild(ov_containment, pcommunication, "OPC_UA"));
	if(!pDomOpcUa) {
		result = Ov_CreateObject(ov_domain, pDomOpcUa, pcommunication, "OPC_UA");
		if(Ov_Fail(result))
		{
			ov_logfile_error("Fatal: could not create OPC_UA domain");
			return result;
		}
	}
	else if(!Ov_CanCastTo(ov_domain, (OV_INSTPTR_ov_object) pDomOpcUa))
	{
		ov_logfile_error("Fatal: OPC_UA object found but not domain (or derived)");
		return OV_ERR_GENERIC;
	}

	/*	create protocol identificator for OPCUA	*/
	pIdentificator = Ov_StaticPtrCast(iec62541_uaIdentificator, Ov_SearchChild(ov_containment, pDomOpcUa, "Identificator"));
	if(pIdentificator)
		Ov_DeleteObject(pIdentificator);
	pIdentificator = NULL;

	result = Ov_CreateObject(iec62541_uaIdentificator, pIdentificator, pDomOpcUa, "Identificator");
	if(Ov_Fail(result))
	{
		ov_logfile_error("Fatal: could not create Identificator object");
		return result;
	}

	/*	create uaServer	*/
	pServer = Ov_StaticPtrCast(iec62541_uaServer, Ov_GetFirstChild(ov_instantiation, pclass_iec62541_uaServer));
	if(!pServer){
		result = Ov_CreateObject(iec62541_uaServer, pServer, pDomOpcUa, "uaServer");
		if(Ov_Fail(result))
		{
			ov_logfile_error("Fatal: could not create Identificator object - reason: %s", ov_result_getresulttext(result));
			return result;
		}
	}

	/*	create ticket authenticators for OPCUA	*/
	pDomTicketAuths = Ov_StaticPtrCast(ov_domain, Ov_SearchChild(ov_containment, pDomOpcUa, "TicketAuthenticators"));
	if(!pDomTicketAuths) {
		result = Ov_CreateObject(ov_domain, pDomTicketAuths, pDomOpcUa, "TicketAuthenticators");
		if(Ov_Fail(result))
		{
			ov_logfile_error("Fatal: could not create TicketAuthenticators domain");
			return result;
		}
	}
	else if(!Ov_CanCastTo(ov_domain, (OV_INSTPTR_ov_object) pDomTicketAuths))
	{
		ov_logfile_error("Fatal: TicketAuthenticators object found but not domain (or derived)");
		return OV_ERR_GENERIC;
	}

	return result;
}
/*
*       Replace the 'setglobalvars' function of a library with this
*       previous one, which additionally creates instances.
* 	This is called by the OV system upon library load.
*/
OV_DLLFNCEXPORT OV_LIBRARY_DEF *ov_library_open_iec62541(void) {
	/* local variables */
	static OV_LIBRARY_DEF *OV_LIBRARY_DEF_iec62541_new;
	/*
	*       replace the 'setglobalvars' function created by the code generator
	*       with a new one.
	*/
	OV_LIBRARY_DEF_iec62541_new = ov_library_open_iec62541_old();
	OV_LIBRARY_DEF_iec62541_new->setglobalvarsfnc = ov_library_setglobalvars_iec62541_new;
	return OV_LIBRARY_DEF_iec62541_new;
}
