#pragma once
#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_render_handler.h"

typedef CefRefPtr<CefBrowserHost>	CefHostRef;
typedef CefRefPtr<CefBrowser>		CefBrowserRef;

class CiBrowserClient;
class CiRenderHandler;
class CiLoadHandler;
class CiLifeSpanHandler;

typedef CefRefPtr<CiBrowserClient>		CiClientRef;
typedef CefRefPtr<CiRenderHandler>		CiRenderHandlerRef;
typedef CefRefPtr<CiLoadHandler>		CiLoadHandlerRef;
typedef CefRefPtr<CiLifeSpanHandler>	CiLifeSpanHandlerRef;