#pragma once
#include "CiCefForward.h"

class CiGHandler : public CefRenderHandler,
	public CefLoadHandler,
	public CefLifeSpanHandler {
public:
	CiGHandler();
	CiGHandler(int pWidth, int pHeight);
	~CiGHandler();

#pragma region Render Handler
public:
	bool GetViewRect(CefBrowserRef browser, CefRect& rect) override;
	void OnPaint(CefBrowserRef browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int width, int height) override;
private:
	int mWidth, mHeight;
	uint8_t* mPixelBuffer;
#pragma endregion

#pragma region Load Handler
public:
	void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame) override;
	void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) override;
	void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) override;
#pragma endregion

#pragma region LifeSpan Handler
public:
	void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
	bool DoClose(CefRefPtr<CefBrowser> browser) override;
	void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

	CefBrowserRef GetBrowser();
	bool IsClosing();
private:
	CefBrowserRef m_Browser;
	int m_BrowserId;
	int m_BrowserCount;
	bool m_bIsClosing;

#pragma endregion

public:
	const uint8_t* GetPixelBuffer();

	IMPLEMENT_REFCOUNTING(CiGHandler);
};