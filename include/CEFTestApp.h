#pragma once
#include <mutex>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Camera.h"
#include "cinder/CameraUi.h"
#include "cinder/gl/gl.h"
#include "CiCefClient.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CEFTestApp : public App {
public:
	void setup() override;
	void mouseDown(MouseEvent event) override;
	void update() override;
	void draw() override;

	void closeBrowser();
	void shutdown();

private:
	CameraPersp	mCamera;
	CameraUi	mCtrl;

	CiClientRef mClient;
	CefBrowserRef mBrowser;
	gl::Texture2dRef mTex;
	gl::GlslProgRef mShader;

	CiHandlerRef	mG_Handler;
};