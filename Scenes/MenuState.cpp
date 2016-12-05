#include "MenuState.hpp"

using namespace Ogre;

MenuState::MenuState( AppStateListener *AppStateManager ) {
    m_bQuit        = false;
    m_FrameEvent   = Ogre::FrameEvent();
    m_pAppStateMgr = AppStateManager;
}

MenuState::~MenuState() {
}

void MenuState::enter() {
    OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Entering MenuState..." );

    m_sceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager( ST_GENERIC, "MenuSceneMgr" );
    m_sceneMgr->setAmbientLight( Ogre::ColourValue( 0.7f, 0.7f, 0.7f ) );

    m_sceneMgr->addRenderQueueListener( OgreFramework::getSingletonPtr()->m_pOverlaySystem );

    m_pCamera = m_sceneMgr->createCamera( "MenuCam" );
    m_pCamera->setPosition( Vector3( 0, 25, -50 ) );
    m_pCamera->lookAt( Vector3( 0, 0, 0 ) );
    m_pCamera->setNearClipDistance( 1 );

    m_pCamera->setAspectRatio( Real( OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth() ) /
                               Real( OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight() ) );

    OgreFramework::getSingletonPtr()->m_pViewport->setCamera( m_pCamera );

    OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showFrameStats( OgreBites::TL_BOTTOMLEFT );
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showLogo( OgreBites::TL_BOTTOMRIGHT );
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton( OgreBites::TL_BOTTOMLEFT, "PickBtn", "Pick", 250 );
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton( OgreBites::TL_BOTTOMLEFT, "TunerBtn", "/Tuner/", 250 );
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton( OgreBites::TL_BOTTOMLEFT, "OptionsBtn", "/Options/", 250 );
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton( OgreBites::TL_BOTTOMLEFT, "ExitBtn", "Exit", 250 );
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createLabel( OgreBites::TL_TOP, "MenuLbl", "Main menu", 250 );


    Ogre::String infoTitle = ( "Welcome" );
    Ogre::String infoText;
    infoText.append( "Lorem ipsum dolor sit amet, \n" );
    infoText.append( "consectetuer adipiscing elit. \n" );
    OgreBites::TextBox* WelcomeInfo = OgreFramework::getSingletonPtr()->m_pTrayMgr->createTextBox( OgreBites::TL_CENTER, "InfoPanel", infoTitle, 300, 220 );
    WelcomeInfo->setText( infoText );

//    TextAreaOverlayElement* textArea = new TextAreaOverlayElement(infoText);
//    //WelcomeInfo->setTextAlignment(&textArea.Center);
//    textArea->setColour(ColourValue(1.0, 0.2, 0.2));
//    WelcomeInfo->setTextAlignment(textArea->Center);
//    WelcomeInfo->
////    WelcomeInfo->refitContents();

//    OverlayManager _overlayMgr;
//    Ogre::OverlayElement* textBox = _overlayMgr.createOverlayElement("TextArea","instance1");
//    textBox->setMetricsMode(Ogre::GMM_PIXELS);
//    textBox->setPosition(100, 200);
//    textBox->setWidth(100);
//    textBox->setHeight(100);
//    textBox->setCaption(infoText);

    createScene();
}

void MenuState::createScene() {
}

void MenuState::exit() {
    OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Leaving MenuState..." );

    m_sceneMgr->destroyCamera( m_pCamera );
    if ( m_sceneMgr ) {
        OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager( m_sceneMgr );
    }

    OgreFramework::getSingletonPtr()->m_pTrayMgr->clearAllTrays();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->setListener( 0 );
}

bool MenuState::keyPressed( const OIS::KeyEvent &keyEventRef ) {
    if ( OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown( OIS::KC_ESCAPE ) ) {
        m_bQuit = true;
        return true;
    }

    OgreFramework::getSingletonPtr()->keyPressed( keyEventRef );
    return true;
}

bool MenuState::keyReleased( const OIS::KeyEvent &keyEventRef ) {
    OgreFramework::getSingletonPtr()->keyReleased( keyEventRef );
    return true;
}

bool MenuState::mouseMoved( const OIS::MouseEvent &evt ) {
    if ( OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseMove( evt ) ) {
        return true;
    }
    return true;
}

bool MenuState::mousePressed( const OIS::MouseEvent &evt, OIS::MouseButtonID id ) {
    if ( OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown( evt, id ) ) {
        return true;
    }
    return true;
}

bool MenuState::mouseReleased( const OIS::MouseEvent &evt, OIS::MouseButtonID id ) {
    if ( OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp( evt, id ) ) {
        return true;
    }
    return true;
}

void MenuState::update( double timeSinceLastFrame ) {
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    OgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued( m_FrameEvent );

    if ( m_bQuit == true ) {
        shutdown();
        return;
    }
}

void MenuState::buttonHit( OgreBites::Button *button ) {
    if ( button->getName() == "ExitBtn" ) {
        m_bQuit = true;
    } else if ( button->getName() == "PickBtn" ) {
        changeAppState( findByName( "SongListState" ) );
    } else if ( button->getName() == "TunerBtn" ) {
        changeAppState( findByName( "GameState" ) );
    }
}
