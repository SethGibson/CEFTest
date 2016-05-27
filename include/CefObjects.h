#pragma once
#include "cinder/gl/Texture.h"
#include "cinder/Log.h"
#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_render_handler.h"

using namespace std;
using namespace ci;

typedef CefRefPtr<CefBrowserHost>	CefHostRef;
typedef CefRefPtr<CefBrowser>		CefBrowserRef;

class CiBrowserClient;
class CiRenderHandler;
class CiLoadHandler;
typedef CefRefPtr<CiBrowserClient>	CiClientRef;
typedef CefRefPtr<CiRenderHandler>	CiRenderHandlerRef;
typedef CefRefPtr<CiLoadHandler>	CiLoadHandlerRef;

class CiBrowserClient : public CefClient
{
public:
	CiBrowserClient(CiRenderHandler *pRenderHandler, CiLoadHandler *pLoadHandler) : mRenderHandler(pRenderHandler), mLoadHandler(pLoadHandler)
	{
		mLoadHandler->SetParent(this);
	}
	CefRefPtr<CefLoadHandler> GetLoadHandler() override
	{
		return mLoadHandler;
	}

	CefRefPtr<CefRenderHandler> GetRenderHandler()  override
	{
		return mRenderHandler;
	}

	const uint8_t* GetPixelBuffer();

	void Cleanup();

	CefHostRef	BrowserHost;

private:
	CiLoadHandlerRef mLoadHandler;
	CiRenderHandlerRef mRenderHandler;


public:
	IMPLEMENT_REFCOUNTING(CiBrowserClient);
};

