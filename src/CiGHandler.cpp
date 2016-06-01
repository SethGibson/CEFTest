#include <mutex>
#include "CiGHandler.h"

using namespace std;
#pragma region Render Handler
CiGHandler::CiGHandler()
{

}

CiGHandler::CiGHandler(int pWidth, int pHeight) :
	mWidth(pWidth),
	mHeight(pHeight),
	m_BrowserCount(0),
	m_bIsClosing(false)

{
	mPixelBuffer = new uint8_t[mWidth*mHeight * 4];
}

CiGHandler::~CiGHandler()
{
	delete[] mPixelBuffer;
}

bool CiGHandler::GetViewRect(CefBrowserRef browser, CefRect& rect)
{
	rect = CefRect(0, 0, mWidth, mHeight);
	return true;
}

void CiGHandler::OnPaint(CefBrowserRef browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int width, int height)
{
	mutex m;
	lock_guard<mutex> g(m);
	if (buffer != nullptr)
		memcpy(mPixelBuffer, buffer, mWidth*mHeight * 4);

}
const uint8_t * CiGHandler::GetPixelBuffer()
{
	return mPixelBuffer;
}
#pragma endregion

#pragma region Load Handler
void CiGHandler::OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame)
{

}

void CiGHandler::OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode)
{

}

void CiGHandler::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl)
{

}
#pragma endregion

#pragma region LifeSpan Handler
void CiGHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();
	if (!m_Browser.get()) {
		m_Browser = browser;
		m_BrowserId = browser->GetIdentifier();
	}

	m_BrowserCount++;
}

bool CiGHandler::DoClose(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();

	if (m_BrowserId == browser->GetIdentifier())
		m_bIsClosing = true;

	return false;
}

void CiGHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();

	if (m_BrowserId == browser->GetIdentifier())
		m_Browser = NULL;

	if (--m_BrowserCount == 0)
		m_bIsClosing = false;
}

CefBrowserRef CiGHandler::GetBrowser() { return m_Browser; }
bool CiGHandler::IsClosing() { return m_bIsClosing; }
#pragma endregion