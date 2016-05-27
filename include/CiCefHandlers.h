#pragma once
#include <list>
#include "CiCefForward.h"

using namespace std;

#pragma region Render Handler
class CiRenderHandler : public CefRenderHandler {
public:
	CiRenderHandler();
	CiRenderHandler(int pWidth, int pHeight);
	~CiRenderHandler();

	bool GetViewRect(CefBrowserRef browser, CefRect& rect) override;
	void OnPaint(CefBrowserRef browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int width, int height) override;
	const uint8_t* GetPixelBuffer();

	IMPLEMENT_REFCOUNTING(CiRenderHandler);

private:
	int mWidth, mHeight;
	uint8_t* mPixelBuffer;

};
#pragma endregion

#pragma region Load Handler
class CiLoadHandler : public CefLoadHandler {
public:
	void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame) override;
	void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) override;
	void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) override;

	IMPLEMENT_REFCOUNTING(CiLoadHandler);

private:
	CiClientRef mParent;
};
#pragma endregion

#pragma region LifeSpan Handler
class CiLifeSpanHandler : public CefLifeSpanHandler {
public:
	CiLifeSpanHandler();
	void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
	bool DoClose(CefRefPtr<CefBrowser> browser) override;
	void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

	CefBrowserRef GetBrowser();
	bool IsClosing();

	IMPLEMENT_REFCOUNTING(CiLifeSpanHandler);

private:
	CefBrowserRef m_Browser;
	int m_BrowserId;
	int m_BrowserCount;
	bool m_bIsClosing;

};
#pragma endregion

