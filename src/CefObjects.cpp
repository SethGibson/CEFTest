#include <string>
#include <mutex>
#include "CefObjects.h"

CiRenderHandler::CiRenderHandler()
{
}

CiRenderHandler::~CiRenderHandler()
{
	delete [] mPixelBuffer;
}

CiRenderHandler::CiRenderHandler(int pWidth, int pHeight) :	mWidth(pWidth),
															mHeight(pHeight)
{
	mPixelBuffer = new uint8_t[pWidth*pHeight * 4];
}
bool CiRenderHandler::GetViewRect(CefBrowserRef browser, CefRect& rect)
{
	rect = CefRect(0, 0, mWidth, mHeight);
	return true;
}

void CiRenderHandler::OnPaint(CefBrowserRef browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int width, int height)
{
	mutex m;
	{
		lock_guard<mutex> guard(m);
		memcpy(mPixelBuffer, buffer, mWidth*mHeight * 4);
	}
}

const uint8_t * CiRenderHandler::GetPixelBuffer()
{
	return mPixelBuffer;
}

const uint8_t * CiBrowserClient::GetPixelBuffer()
{
	return mRenderHandler->GetPixelBuffer();
}

void CiBrowserClient::Cleanup()
{
	if(BrowserHost!=nullptr)
		BrowserHost->CloseBrowser(true);
	mLoadHandler->Release();
	mRenderHandler->Release();
}

