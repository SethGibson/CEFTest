#pragma once
#include "CiCefForward.h"
#include "CiCefHandlers.h"

class CiBrowserClient : public CefClient
{
public:
	CiBrowserClient(int pWidth, int pHeight);

	CefRefPtr<CefLoadHandler>		GetLoadHandler() override;
	CefRefPtr<CefRenderHandler>		GetRenderHandler()  override;
	CefRefPtr<CefLifeSpanHandler>	GetLifeSpanHandler() override;
	const uint8_t* GetPixelBuffer();
	void Cleanup();

	CefHostRef	BrowserHost;

	IMPLEMENT_REFCOUNTING(CiBrowserClient);

private:
	CiLoadHandlerRef		mLoadHandler;
	CiRenderHandlerRef		mRenderHandler;
	CiLifeSpanHandlerRef	mLifeSpanHandler;
};

