#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "MyGame.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();

    auto glview = director->getOpenGLView();
    if(!glview) 
    {
        glview = GLView::create("My Game");       //
        director->setOpenGLView(glview);
    }   
    
    
   


    //---------------------------------------------------------------------------------------

    Size size;
    size = director->getWinSize();
    log("***IDONG: Director getWinSize:w=%f,h=%f", size.width, size.height);

    size = director->getWinSizeInPixels();
    log("***IDONG: Director getWinSizeInPixels:w=%f,h=%f", size.width, size.height);

    size = director->getVisibleSize();
    log("***IDONG: Director getVisibleSize:w=%f,h=%f", size.width, size.height);

    Point point = director->getVisibleOrigin();
    log("***IDONG: Director getVisibleOrigin:x=%f,y=%f", point.x, point.y);


    log("***IDONG: Director BS: getContentScaleFactor: scaleFactor=%f", director->getContentScaleFactor());


//     // set design resolution size  
//     glview->setDesignResolutionSize(SCREEN_WIDTH, SCREEN_HEIGHT, ResolutionPolicy::NO_BORDER);

    log("***IDONG:\n");
    log("***IDONG: Director AS: getContentScaleFactor: scaleFactor=%f", director->getContentScaleFactor());

    size = director->getWinSize();
    log("***IDONG: Director getWinSize:w=%f,h=%f", size.width, size.height);

    size = director->getWinSizeInPixels();
    log("***IDONG: Director getWinSizeInPixels:w=%f,h=%f", size.width, size.height);

    size = director->getVisibleSize();
    log("***IDONG: Director getVisibleSize:w=%f,h=%f", size.width, size.height);

    point = director->getVisibleOrigin();
    log("***IDONG: Director getVisibleOrigin:x=%f,y=%f", point.x, point.y);

    //--------------------------------------------------------------------------

    // create a scene. it's an autorelease object
    //auto scene = HelloWorld::createScene();

    // run
   // director->runWithScene(scene);
    

    Size designSize(960,640);
    Size screenSize = glview->getFrameSize();

    log("FrameSize: %f,%f", screenSize.width, screenSize.height);

    if (screenSize.height > designSize.height)
    {
        
    }
    else{


    }
    

    //glview->setFrameSize(director->getWinSize().width, director->getWinSize().height);
    //director->setContentScaleFactor(SCREEN_WIDTH / 320);

    //glview->setFrameZoomFactor(0.8);
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::NO_BORDER);
    //director->setContentScaleFactor( screenSize.height/designSize.height );
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);




    CMyGame::getShareGame()->setState(CMyGame::STATE_INIT);
    
    Vec2 origin = director->getVisibleOrigin();
    log("org %f, %f",origin.x, origin.y );
   
  
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

    CMyGame::getShareGame()->setState(CMyGame::STATE_STOP);
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

    CMyGame::getShareGame()->setState(CMyGame::STATE_RUN);
}
