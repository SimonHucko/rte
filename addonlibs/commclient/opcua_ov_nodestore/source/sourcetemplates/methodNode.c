
/******************************************************************************
*
*   FILE
*   ----
*   methodNode.c
*
*   History
*   -------
*   2016-11-09   File created
*
*******************************************************************************
*
*   This file is generated by the 'acplt_builder' command
*
******************************************************************************/


#ifndef OV_COMPILE_LIBRARY_opcua
#define OV_COMPILE_LIBRARY_opcua
#endif


#include "opcua.h"
#include "libov/ov_macros.h"


OV_DLLFNCEXPORT OV_RESULT opcua_methodNode_preCallMethod(
	OV_INSTPTR_opcua_methodNode pobj
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT void opcua_methodNode_postCallMethod(
	OV_INSTPTR_opcua_methodNode pobj,
	OV_BOOL methodFailed
) {

    return;
}

OV_DLLFNCEXPORT OV_ACCESS opcua_methodNode_getaccess(
	OV_INSTPTR_ov_object	pobj,
	const OV_ELEMENT		*pelem,
	const OV_TICKET			*pticket
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_opcua_methodNode pinst = Ov_StaticPtrCast(opcua_methodNode, pobj);

    return (OV_ACCESS)0;
}

