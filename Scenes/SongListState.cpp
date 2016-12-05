#include "SongListState.hpp"

using namespace Ogre;

SongListState::SongListState( AppStateListener* AppStateManager ) {
    m_pAppStateMgr = AppStateManager;
}

SongListState::~SongListState() {
}

void SongListState::enter() {
    OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Entering SongListState..." );

    m_sceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager( ST_GENERIC, "SongListSceneMgr" );
    m_sceneMgr->setAmbientLight( Ogre::ColourValue( 0.7f, 0.7f, 0.7f ) );

    m_sceneMgr->addRenderQueueListener( OgreFramework::getSingletonPtr()->m_pOverlaySystem );

    m_pCamera = m_sceneMgr->createCamera( "SongListCam" );
    m_pCamera->setPosition( Vector3( 0, 25, -50 ) );
    m_pCamera->lookAt( Vector3( 0, 0, 0 ) );
    m_pCamera->setNearClipDistance( 1 );

    m_pCamera->setAspectRatio( Real( OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth() ) /
                               Real( OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight() ) );

    OgreFramework::getSingletonPtr()->m_pViewport->setCamera( m_pCamera );

    OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
//    OgreFramework::getSingletonPtr()->m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
//    OgreFramework::getSingletonPtr()->m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton( OgreBites::TL_BOTTOMLEFT, "BackBtn", "Back", 100 );
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton( OgreBites::TL_BOTTOMRIGHT, "PlayBtn", "Play!", 100 );

    OgreFramework::getSingletonPtr()->m_pTrayMgr->createLabel( OgreBites::TL_TOP, "MenuLbl", "List", 250 );

    m_pSongInfo = new SongInfo( "notation.xml" );

    //Ogre::String infoText = "Vitejte\n\n";
    Ogre::String infoTitle = ( "Info" );
    Ogre::String infoText  = m_pSongInfo->m_songName;
    infoText.append( "\n" );
    infoText.append( m_pSongInfo->m_artistName );
    infoText.append( "\n" );
    infoText.append( m_pSongInfo->m_albumName );
    OgreBites::TextBox* SongInfo = OgreFramework::getSingletonPtr()->m_pTrayMgr->createTextBox( OgreBites::TL_CENTER, "InfoPanel", infoTitle, 300, 220 );
    SongInfo->setText( infoText );

    createScene();
}

void SongListState::createScene() {
}

void SongListState::exit() {
    OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Leaving SongListState..." );

    m_sceneMgr->destroyCamera( m_pCamera );
    if ( m_sceneMgr ) {
        OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager( m_sceneMgr );
    }

    OgreFramework::getSingletonPtr()->m_pTrayMgr->clearAllTrays();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->setListener( 0 );

    delete m_pSongInfo;
}

bool SongListState::keyPressed( const OIS::KeyEvent &keyEventRef ) {
    if ( OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown( OIS::KC_ESCAPE ) ) {
        pushAppState( findByName( "SongListState" ) );
        return true;
    }
}

bool SongListState::keyReleased( const OIS::KeyEvent &keyEventRef ) {
    OgreFramework::getSingletonPtr()->keyReleased( keyEventRef );
    return true;
}

bool SongListState::mouseMoved( const OIS::MouseEvent &evt ) {
    if ( OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseMove( evt ) ) {
        return true;
    }
    return true;
}

bool SongListState::mousePressed( const OIS::MouseEvent &evt, OIS::MouseButtonID id ) {
    if ( OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown( evt, id ) ) {
        return true;
    }
    return true;
}

bool SongListState::mouseReleased( const OIS::MouseEvent &evt, OIS::MouseButtonID id ) {
    if ( OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp( evt, id ) ) {
        return true;
    }
    return true;
}

void SongListState::buttonHit( OgreBites::Button *button ) {
    if ( button->getName() == "BackBtn" ) {
        changeAppState( findByName( "MenuState" ) );
    } else if ( button->getName() == "PlayBtn" )      {
        changeAppState( findByName( "PerformanceState" ) );
    }
}

void SongListState::update( double timeSinceLastFrame ) {
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    OgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued( m_FrameEvent );
}
