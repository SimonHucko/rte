#ifndef OV_COMPILE_LIBRARY_kshttp
#define OV_COMPILE_LIBRARY_kshttp
#endif

#include "config.h"


OV_DLLFNCEXPORT OV_RESULT kshttp_httpIdentificator_constructor(
	OV_INSTPTR_ov_object 	pobj
) {
	/*
	 *   local variables
	 */
	OV_INSTPTR_kshttp_httpIdentificator pinst = Ov_StaticPtrCast(kshttp_httpIdentificator, pobj);
	OV_RESULT    result;

	/* do what the base class does first */
	result = ov_object_constructor(pobj);
	if(Ov_Fail(result))
		return result;

	return ov_string_setvalue(&pinst->v_protocolID, KSHTTP_IDENTIFIER);
}



/**
 * in order to detect a http request, we check if a white list of HTTP methods are provided
 */
OV_DLLFNCEXPORT OV_BOOL kshttp_httpIdentificator_identify (
	OV_INSTPTR_ksbase_ProtocolIdentificator this,
	OV_INSTPTR_ksbase_Channel pchannel
) {
	OV_INSTPTR_kshttp_httpIdentificator
		pObj = Ov_StaticPtrCast(kshttp_httpIdentificator, this);
	OV_UINT i = 0;
	OV_UINT length = 0;

	//minimal length of request is 14
	//GET / HTTP/1.1
	//we need to detect all HTTP methods
	if(pchannel->v_inData.length < 15){
		return FALSE;
	}
	//{"GET", "POST", "HEAD", "PUT", "PROPPATCH", "PROPFIND", "DELETE", "MOVE", "LINK", "UNLINK", "OPTIONS"};
	for(i = 0;i < pObj->v_AllowedMethods.veclen;i++){
		length = ov_string_getlength(pObj->v_AllowedMethods.value[i]);
		//ov_string_getlength returns 0 if pointer is NULL
		if(length == 0){
			continue;
		}
		if(strncmp(pObj->v_AllowedMethods.value[i], (char*)pchannel->v_inData.data, (int)length) == OV_STRCMP_EQUAL){
			return TRUE;
		}
	}
	return FALSE;
}

/**
*	functions to create the ClientHandler corresponding to the protocol. This is calles after a successfull identification. The function has to create the ClientHandler
*	and Link it to the Channel calling it with AssocChannelClientHandler.
*/
OV_DLLFNCEXPORT OV_RESULT kshttp_httpIdentificator_createClientHandler (
	OV_INSTPTR_ksbase_ProtocolIdentificator this,
	OV_INSTPTR_ksbase_Channel pchannel
) {
    /*
    *   local variables
    */
	OV_INSTPTR_kshttp_httpclienthandler pClientHandler = NULL;

	OV_RESULT result;

	result = Ov_CreateIDedObject(kshttp_httpclienthandler, pClientHandler, this, "httpClientHandler");
	if(Ov_OK(result))
	{
		KS_logfile_debug(("%s: ClientHandler created: %s", this->v_identifier, pClientHandler->v_identifier));
		result = Ov_Link(ksbase_AssocChannelClientHandler, pchannel, pClientHandler);
		if(Ov_Fail(result))
		{
			KS_logfile_error(("%s: could not link ClientHandler %s to Channel %s", this->v_identifier, pClientHandler->v_identifier, pchannel->v_identifier));
			return result;
		}
		else
		{
			result = ov_string_setvalue(&(pClientHandler->v_sourceAdr), pchannel->v_address);
			if(Ov_Fail(result))
			{
				KS_logfile_error(("%s: could not set ClientHandler %s's sourceAdr. reason: %s", this->v_identifier, pClientHandler->v_identifier, ov_result_getresulttext(result)));
			}
			return OV_ERR_OK;
		}
	}
	else
	{
		KS_logfile_error(("%s: could not create ClientHandler: %s", this->v_identifier, ov_result_getresulttext(result)));
		return result;
	}


}

