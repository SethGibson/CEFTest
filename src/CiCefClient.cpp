#include "CiCefClient.h"

CiBrowserClient::CiBrowserClient(int pWidth, int pHeight)
{
	mLoadHandler = CiLoadHandlerRef(new CiLoadHandler());
	mRenderHandler = CiRenderHandlerRef(new CiRenderHandler(pWidth, pHeight));
}

CefRefPtr<CefLoadHandler> CiBrowserClient::GetLoadHandler()
{
	return mLoadHandler;
}

CefRefPtr<CefRenderHandler>	CiBrowserClient::GetRenderHandler()
{
	return mRenderHandler;
}

CefRefPtr<CefLifeSpanHandler> CiBrowserClient::GetLifeSpanHandler()
{
	return mLifeSpanHandler;
}

const uint8_t* CiBrowserClient::GetPixelBuffer()
{
	return mRenderHandler->GetPixelBuffer();
}

void CiBrowserClient::Cleanup()
{
	mLoadHandler->Release();
	mRenderHandler->Release();
}
