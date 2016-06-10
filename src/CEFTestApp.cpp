#include "cinder/Log.h"
#include "CEFTestApp.h"

const ivec2 kViewSize(1280, 720);

void CEFTestApp::setup()
{
	mTex = gl::Texture2d::create(kViewSize.x, kViewSize.y, gl::Texture2d::Format().internalFormat(GL_RGBA).dataType(GL_UNSIGNED_BYTE));
	
	mCamera.setPerspective(60.0f, getWindowAspectRatio(), 0.1f, 10.0f);
	mCamera.lookAt(vec3(0, 0, 5), vec3(), vec3(0, 1, 0));
	mCtrl.setCamera(&mCamera);
	mCtrl.connect(getWindow());
	mShader = gl::getStockShader(gl::ShaderDef().texture(mTex).lambert());

	CefMainArgs args;
	CefSettings opts;
	opts.multi_threaded_message_loop = false;
	opts.no_sandbox = true;
	opts.single_process = false;
	opts.windowless_rendering_enabled = true;

	const char* bsp = "C:/dev/projects/cinder/CEFTest/vc2013/x64/Debug/cefclient.exe";
	CefString(&opts.browser_subprocess_path).FromASCII(bsp);

	/*
	int presult = CefExecuteProcess(args, nullptr, nullptr);
	if (presult >= 0)
		quit();
	*/
	bool iresult = CefInitialize(args, opts, nullptr, nullptr);
	if (!iresult)
	{
		quit();
	}

	CefWindowInfo wi;
	CefBrowserSettings bs;
	
	auto wh = (HWND)getWindow()->getNative();
	wi.SetAsWindowless(wh, false);
	
	mG_Handler = CiHandlerRef(new CiGHandler(kViewSize.x, kViewSize.y));
	mClient = new CiBrowserClient(mG_Handler);
	CefBrowserHost::CreateBrowser(wi, mClient, "http://youtube.com/", bs, nullptr);

	
	
	App::get()->getSignalShouldQuit().connect(bind(&CEFTestApp::closeBrowser, this));
	App::get()->getSignalCleanup().connect(bind(&CEFTestApp::shutdown, this));
	//getWindow()->getSignalClose().connect(bind(&CEFTestApp::closeBrowser, this));
	
}

void CEFTestApp::mouseDown( MouseEvent event )
{
}

void CEFTestApp::update()
{
	CefDoMessageLoopWork();
	const uint8_t* pb = mClient->GetPixelBuffer();
	if (pb) {
		Surface8uRef srf = Surface8u::create(const_cast<uint8_t*>(pb), kViewSize.x, kViewSize.y, kViewSize.x * 4, SurfaceChannelOrder::BGRA);
		if (srf)
			mTex->update(*srf);
	}
}

void CEFTestApp::draw()
{
	gl::setMatrices(mCamera);
	gl::clear( Color( 0, 0, 0 ) ); 
	gl::color(Color::white());

	gl::ScopedDepthTest dtest(true);
	gl::ScopedTextureBind tex(mTex, 0);
	gl::ScopedGlslProg shdr(mShader);
	gl::drawCube(vec3(), vec3(1));
}

bool CEFTestApp::closeBrowser()
{
	CEF_REQUIRE_UI_THREAD();
	if (mG_Handler.get() &&!mG_Handler->IsClosing()) {
		auto browser = mG_Handler->GetBrowser();
		if (browser.get()) {
			browser->GetHost()->CloseBrowser(false);
			return false;
		}
	}

	return true;
}

void CEFTestApp::shutdown()
{
	CefShutdown();
}

CINDER_APP(CEFTestApp, RendererGl,
	[](App::Settings *pSettings) 
	{
		pSettings->setWindowSize(1280, 720);
		pSettings->disableFrameRate();
	})
