#include "CiCefClient.h"

CiBrowserClient::CiBrowserClient(CiHandlerRef pHandler) :
	mHandler(pHandler)
{
}

CefRefPtr<CefLoadHandler> CiBrowserClient::GetLoadHandler()
{
	return mHandler;
}

CefRefPtr<CefRenderHandler>	CiBrowserClient::GetRenderHandler()
{
	return mHandler;
}

CefRefPtr<CefLifeSpanHandler> CiBrowserClient::GetLifeSpanHandler()
{
	return mHandler;
}

const uint8_t* CiBrowserClient::GetPixelBuffer()
{
	return mHandler->GetPixelBuffer();
}