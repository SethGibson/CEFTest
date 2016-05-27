#include <mutex>
#include "CiCefHandlers.h"

#pragma region Render Handler
CiRenderHandler::CiRenderHandler()
{

}

CiRenderHandler::CiRenderHandler(int pWidth, int pHeight) : mWidth(pWidth), mHeight(pHeight)
{
	mPixelBuffer = new uint8_t[mWidth*mHeight * 4];
}

CiRenderHandler::~CiRenderHandler()
{
	delete[] mPixelBuffer;
}

bool CiRenderHandler::GetViewRect(CefBrowserRef browser, CefRect& rect)
{
	rect = CefRect(0, 0, mWidth, mHeight);
	return true;
}

void CiRenderHandler::OnPaint(CefBrowserRef browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int width, int height)
{
	mutex m;
	lock_guard<mutex> g(m);
	if (buffer != nullptr)
		memcpy(mPixelBuffer, buffer, mWidth*mHeight * 4);

}
const uint8_t * CiRenderHandler::GetPixelBuffer()
{
	return mPixelBuffer;
}
#pragma endregion

#pragma region Load Handler
void CiLoadHandler::OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame)
{

}

void CiLoadHandler::OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode)
{

}

void CiLoadHandler::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl)
{

}
#pragma endregion

void CiLifeSpanHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();
	mBrowserList.push_back(browser);
}

bool CiLifeSpanHandler::DoClose(CefRefPtr<CefBrowser> browser)
{
	return false;
}

void CiLifeSpanHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
}
