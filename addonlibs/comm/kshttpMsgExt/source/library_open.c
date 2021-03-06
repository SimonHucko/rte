
/******************************************************************************
*
*   FILE
*   ----
*   library_open.c
*
*   History
*   -------
*   2014-11-12   File created
*
*******************************************************************************
*
*   This file is generated by the 'acplt_builder' command
*
******************************************************************************/

#ifndef OV_COMPILE_LIBRARY_kshttpMsgExt
#define OV_COMPILE_LIBRARY_kshttpMsgExt
#endif

#include "kshttpMsgExt.h"
#include "libov/ov_macros.h"
#ifdef ov_library_open_kshttpMsgExt
#undef ov_library_open_kshttpMsgExt
#endif

OV_RESULT kshttpMsgExt_include_localfiles(OV_INSTPTR_ov_domain pstaticfiles);

/*
* This function will be called, when the library is loaded.
* It could generate components and initializes the startup procedure
*/
OV_RESULT ov_library_setglobalvars_kshttpMsgExt_new(void) {
	OV_RESULT result;
	OV_INSTPTR_kshttpMsgExt_MsgExt	pMsgExt	=	NULL;
	OV_INSTPTR_MessageSys_MsgDelivery	pDelivery	=	NULL;
	OV_INSTPTR_ov_domain pData = NULL;
	OV_INSTPTR_ov_domain httpStaticfiles = NULL;
	/*
	 *    set the global variables of the original version
	 *    and if successful, load other libraries
	 *    and create some objects
	 */
	result = ov_library_setglobalvars_kshttpMsgExt();
	if(Ov_Fail(result)){
		return result;
	}
	pDelivery = Ov_StaticPtrCast(MessageSys_MsgDelivery, Ov_GetFirstChild(ov_instantiation, pclass_MessageSys_MsgDelivery));
	if(pDelivery){
		result =  Ov_CreateObject(kshttpMsgExt_MsgExt, pMsgExt, pDelivery, "kshttpMessageExtension");
		if(Ov_Fail(result) && result != OV_ERR_ALREADYEXISTS){
			return result;
		}
	}
	pData = Ov_StaticPtrCast(ov_domain, Ov_SearchChild(ov_containment, &pdb->root, "data"));
	if(pData){
		httpStaticfiles = Ov_StaticPtrCast(ov_domain, Ov_SearchChild(ov_containment, pData, "kshttp"));
		if(httpStaticfiles) {
			if(Ov_CanCastTo(ov_domain, (OV_INSTPTR_ov_object) httpStaticfiles))
			{
				/*
				 * calling a generated wrapper function to create all the static files from /staticfiles dir
				 * this function is generated in prebuild.tcl
				 */
				kshttpMsgExt_include_localfiles(httpStaticfiles);

			}
		}
	}
	return OV_ERR_OK;
}
/*
*       Replace the 'setglobalvars' function of a library with this
*       previous one, which additionally creates instances.
* 	This is called by the OV system upon library load.
*/
OV_DLLFNCEXPORT OV_LIBRARY_DEF *ov_library_open_kshttpMsgExt(void) {
	/* local variables */
	static OV_LIBRARY_DEF *OV_LIBRARY_DEF_kshttpMsgExt_new;
	/*
	*       replace the 'setglobalvars' function created by the code generator
	*       with a new one.
	*/
	OV_LIBRARY_DEF_kshttpMsgExt_new = ov_library_open_kshttpMsgExt_old();
	OV_LIBRARY_DEF_kshttpMsgExt_new->setglobalvarsfnc = ov_library_setglobalvars_kshttpMsgExt_new;
	return OV_LIBRARY_DEF_kshttpMsgExt_new;
}
