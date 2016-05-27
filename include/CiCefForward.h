#pragma once
#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_render_handler.h"
#include "include/wrapper/cef_helpers.h"

typedef CefRefPtr<CefBrowserHost>	CefHostRef;
typedef CefRefPtr<CefBrowser>		CefBrowserRef;

class CiBrowserClient;
class CiGHandler;

typedef CefRefPtr<CiBrowserClient>	CiClientRef;
typedef CefRefPtr<CiGHandler>		CiHandlerRef;