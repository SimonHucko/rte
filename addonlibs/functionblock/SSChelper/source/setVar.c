
/******************************************************************************
*
*   FILE
*   ----
*   setVar.c
*
*   History
*   -------
*   2015-06-01   File created
*
*******************************************************************************
*
*   This file is generated by the 'acplt_builder' command
*
******************************************************************************/


#ifndef OV_COMPILE_LIBRARY_SSChelper
#define OV_COMPILE_LIBRARY_SSChelper
#endif


#include "SSChelper.h"
#include "libov/ov_macros.h"

#include "libov/ov_path.h"
#include "libov/ov_memstack.h"
#include "libov/ov_result.h"
#include "libov/ov_logfile.h"

#include "fb_namedef.h"

#include "ov_call_macros_10.h"


static void extractBehindSeperator(const OV_STRING inputstring, OV_STRING *pathname, OV_STRING *varname, char seperator){
	OV_UINT len = 0;
	OV_UINT i = 0;

	if(!inputstring){
		return;
	}
	ov_string_setvalue(pathname, inputstring);
	len = ov_string_getlength(inputstring);	//todo iterate backwards, for speed :-)
	for(i = 0 ; i<len-1 ; i++){
		if(inputstring[len-i] == seperator){
			ov_string_setvalue(varname, &inputstring[len-i+1]);
			(*pathname)[len-i] = '\0';
			break;
		}
	}
	return;
}

OV_INSTPTR_ov_object getrelativeobjectpointer(
		const OV_STRING			startPoint,
		const OV_STRING			pathname
) {
	/*
	 *	local variables
	 */
	OV_PATH		path;
	OV_ELEMENT	element;
	OV_PATH     startPointPath;
	ov_memstack_lock();
	ov_path_resolve(&startPointPath, NULL, startPoint, 2);

	/*
	 *	instructions
	 */
	if(Ov_Fail(ov_path_resolve(&path, &startPointPath, pathname, 2))) {
		//	bad path
		ov_memstack_unlock();
		return NULL;
	}
	element = path.elements[path.size-1];

	ov_memstack_unlock();
	if(element.elemtype == OV_ET_OBJECT) {
		return element.pobj;
	}
	//	not an object path
	return NULL;
}

static OV_RESULT SSChelper_getObjectAndVarnameFromSetVariable(
		const OV_INSTPTR_SSChelper_setVar pinst,
		const OV_STRING nameToCheck,
		OV_INSTPTR_ov_object *pTargetObj,
		OV_STRING *ptargetVarname
) {
	OV_STRING targetPathname = NULL;
	OV_STRING pathRelativeobject = NULL;
	OV_INSTPTR_ov_object pStep = Ov_DynamicPtrCast(ov_object, Ov_GetParent(ov_containment, pinst));
	OV_INSTPTR_ov_object activeHeader = Ov_DynamicPtrCast(ov_object, Ov_GetParent(ov_containment, pStep));
	OV_INSTPTR_ov_domain containerDomain = NULL;

	*pTargetObj = NULL;
	//split the input at dot
	extractBehindSeperator(nameToCheck, &targetPathname, ptargetVarname, '.');

	if(targetPathname == NULL){
		return OV_ERR_BADPARAM;
	}else if(targetPathname[0] == '/'){
		//we have a full path
		*pTargetObj = ov_path_getobjectpointer(targetPathname, 2);
	}else{
		//we have a relative path
		ov_memstack_lock();
		//all path are relative to the activeHeader
		containerDomain =Ov_DynamicPtrCast(ov_domain, activeHeader);
		ov_string_setvalue(&pathRelativeobject, ov_path_getcanonicalpath(Ov_PtrUpCast(ov_object, containerDomain), 2));
		*pTargetObj = getrelativeobjectpointer(pathRelativeobject, targetPathname);
//		if(*pTargetObj == NULL){
//			//perhaps the target is in the actions PART of the header
//			containerDomain = Ov_GetPartPtr(actions, activeHeader);
//			ov_string_setvalue(&pathRelativeobject, ov_path_getcanonicalpath(Ov_PtrUpCast(ov_object, containerDomain), 2));
//			*pTargetObj = getrelativeobjectpointer(pathRelativeobject, targetPathname);
//		}
		ov_memstack_unlock();
	}
	if(Ov_CanCastTo(fb_port, *pTargetObj)){
		//we have a fc port, so adjust everything
		ov_string_setvalue(ptargetVarname, nameToCheck);
		*pTargetObj = Ov_PtrUpCast(ov_object, Ov_GetParent(ov_containment, *pTargetObj));
	}
	ov_string_setvalue(&targetPathname, NULL);
	ov_string_setvalue(&pathRelativeobject,NULL);

	return OV_ERR_OK;
}

OV_RESULT SSChelper_setNamedVariable(const OV_INSTPTR_ov_object pTargetObj, const OV_STRING targetVarname, OV_ANY *value){
	OV_RESULT result = OV_ERR_OK;
	OV_ELEMENT element;
	OV_ELEMENT varElement;
	OV_VTBLPTR_ov_object pVtblObj = NULL;

	if(pTargetObj == NULL){
			return OV_ERR_BADPARAM;
	}else if (Ov_CanCastTo(fb_functionchart, pTargetObj)&& !Ov_CanCastTo(ssc_SequentialControlChart, pTargetObj)&&ov_string_compare(targetVarname,"CMD")!=OV_STRCMP_EQUAL){
		//set variable in a functionchart
		result = fb_functionchart_setport(Ov_StaticPtrCast(fb_functionchart, pTargetObj), targetVarname, value);
	}else{
		//set variable in a object
		varElement.elemtype = OV_ET_NONE;
		element.elemtype = OV_ET_OBJECT;
		element.pobj = pTargetObj;

		//search the variable for the set operation
		ov_element_searchpart(&element, &varElement, OV_ET_VARIABLE, targetVarname);
		if(varElement.elemtype == OV_ET_VARIABLE) {
			//port found, use the setter to write the value
			Ov_GetVTablePtr(ov_object, pVtblObj, pTargetObj);
			result = pVtblObj->m_setvar(varElement.pobj, &varElement, value);
		}
	}

	return result;
}



OV_DLLFNCEXPORT void SSChelper_setVar_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_SSChelper_setVar pinst = Ov_StaticPtrCast(SSChelper_setVar, pfb);
    OV_INSTPTR_ov_object target=NULL;

    SSChelper_getObjectAndVarnameFromSetVariable(pinst,pinst->v_path,&target,&pinst->v_port);

    SSChelper_setNamedVariable(target,pinst->v_port,&pinst->v_var);
    return;
}

