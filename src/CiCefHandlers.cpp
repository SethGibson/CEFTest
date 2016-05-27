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

#pragma region LifeSpan Handler
CiLifeSpanHandler::CiLifeSpanHandler() :
	m_BrowserCount(0),
	m_bIsClosing(false)
{
}
void CiLifeSpanHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();
	if (!m_Browser.get()) {
		m_Browser = browser;
		m_BrowserId = browser->GetIdentifier();
	}

	m_BrowserCount++;
}

bool CiLifeSpanHandler::DoClose(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();

	if (m_BrowserId == browser->GetIdentifier())
		m_bIsClosing = true;

	return false;
}

void CiLifeSpanHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();

	if (m_BrowserId == browser->GetIdentifier())
		m_Browser = NULL;

	if (--m_BrowserCount == 0)
		CefQuitMessageLoop();
}

CefBrowserRef CiLifeSpanHandler::GetBrowser(){ return m_Browser; }
bool CiLifeSpanHandler::IsClosing(){ return m_bIsClosing; }
#pragma endregion