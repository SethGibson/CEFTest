#pragma once
#include "CiCefForward.h"
#include "CiGHandler.h"

class CiBrowserClient : public CefClient
{
public:
	CiBrowserClient(CiHandlerRef pHandler);

	CefRefPtr<CefLoadHandler>		GetLoadHandler() override;
	CefRefPtr<CefRenderHandler>		GetRenderHandler()  override;
	CefRefPtr<CefLifeSpanHandler>	GetLifeSpanHandler() override;
	const uint8_t* GetPixelBuffer();

	CefHostRef	BrowserHost;

	IMPLEMENT_REFCOUNTING(CiBrowserClient);

private:
	CiHandlerRef mHandler;
};

