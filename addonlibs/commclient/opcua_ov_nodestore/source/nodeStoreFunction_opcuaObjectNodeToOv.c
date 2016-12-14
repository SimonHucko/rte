/******************************************************************************
 *
 *   FILE
 *   ----
 *   nodeStoreFunctions.c
 *
 *   History
 *   -------
 *   2014-10-21   File created
 *
 *******************************************************************************
 *
 *   This file is generated by the 'acplt_builder' command
 *
 ******************************************************************************/

#ifndef OV_COMPILE_LIBRARY_opcua
#define OV_COMPILE_LIBRARY_opcua
#endif

#include "libov/ov_macros.h"
#include "ksbase.h"
#include "opcua.h"
#include "opcua_helpers.h"
#include "NoneTicketAuthenticator.h"
#include "libov/ov_path.h"
#include "libov/ov_memstack.h"
#include "ks_logfile.h"

extern OV_INSTPTR_opcua_uaServer opcua_pUaServer;


OV_DLLFNCEXPORT UA_StatusCode opcua_nodeStoreFunctions_opcuaObjectNodeToOv(
		void *handle, UA_ObjectNode *opcuaNode, OV_INSTPTR_opcua_objectNode ovNode) {
	OV_RESULT result = 0;
	OV_INSTPTR_ov_domain ptr = Ov_StaticPtrCast(ov_domain, Ov_SearchChild(ov_containment, &(pdb->root), "TechUnits"));
	OV_STRING tmpString;

	ov_string_print(&tmpString, "opcuaToOvNode:%u", opcuaNode->nodeId.identifier.numeric);
	result = Ov_CreateObject(opcua_objectNode, ovNode, ptr, "opcuaToOVNode");

	copyOPCUAQualifiedNameToOV	(&opcuaNode->browseName	, &ovNode->p_browseName);
	copyOPCUALocalizedTextToOV	(&opcuaNode->description, &ovNode->p_description);
	copyOPCUALocalizedTextToOV	(&opcuaNode->displayName, &ovNode->p_displayName);
	copyOPCUANodeIdToOV			(&opcuaNode->nodeId		, &ovNode->p_nodeId);


	ovNode->v_nodeClass 		= opcuaNode->nodeClass;
	ovNode->v_userWriteMask 	= opcuaNode->userWriteMask;
	ovNode->v_writeMask 		= opcuaNode->writeMask;

	//copy references to ov node structure
	OV_INSTPTR_opcua_reference tmpRefNode;

	for (size_t i = 0; i < opcuaNode->referencesSize; i++){
		ov_string_print(&tmpString, "Reference%u", i);
		result = createOVReferenceNodeFromOPCUA(&ovNode->p_references, &tmpRefNode, tmpString);
		if (result != 0)
			return result;
		copyOPCUAReferenceNodeToOV(&opcuaNode->references[i], tmpRefNode);
	}

	//object related fields:
	ovNode->v_eventNotifier = opcuaNode->eventNotifier;
	return result;
}

