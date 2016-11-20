#include "PerformanceState.hpp"


//|||||||||||||||||||||||||||||||||||||||||||||||

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

PerformanceState::PerformanceState( AppStateListener *AppStateManager ) :
    m_direction( Vector3::ZERO ) { // samo se to nevynuluje
    m_MoveSpeed	  = 0.1f;
    m_RotateSpeed = 0.3f;

    m_bLMouseDown	= false;
    m_bRMouseDown	= false;
    m_bQuit			= false;
    m_bSettingsMode = false;

    m_pDetailsPanel = 0;


    m_direction.z = SceneSettings::direction.z;

    m_pAppStateMgr = AppStateManager;

}

PerformanceState::~PerformanceState() {

}

void PerformanceState::enter() {
    OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Entering GameState..." );

    m_sceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager( ST_GENERIC, "PerformanceSceneMgr" );
    m_sceneMgr->setAmbientLight( Ogre::ColourValue( 0.9f, 0.9f, 0.9f ) );

    m_sceneMgr->addRenderQueueListener( OgreFramework::getSingletonPtr()->m_pOverlaySystem );

    //Camera
    m_pCamera = m_sceneMgr->createCamera( "GameCamera" );
    m_pCamera->setPosition( Vector3( 0, 30, 100 ) );
    m_pCamera->lookAt( Vector3( 0, 20, 50 ) );
    m_pCamera->setNearClipDistance( 5 );
    m_pCamera->setFarClipDistance( 2000 );

    m_pCamera->setAspectRatio( Real( OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth() ) /
                               Real( OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight() ) );

    OgreFramework::getSingletonPtr()->m_pViewport->setCamera( m_pCamera );


    buildGUI();

    createScene();
}

void PerformanceState::createScene() {

    ///Create the objects of scene
    m_fretGuides = new FretGuide( m_sceneMgr );

    //Uzel sceny
    Ogre::SceneNode* m_perfSceneNode;
    m_perfSceneNode = m_sceneMgr->getRootSceneNode()->createChildSceneNode( "PerfSceneNode" );

    //Uzel prazcu
    m_fretLinesNode = m_perfSceneNode->createChildSceneNode( "FretLinesNode" );
    m_fretGuides->load( m_fretLinesNode );
    m_fretLinesNode->setPosition( 0, 0, 0 );

    //Uzel osnovy, ta se bude pohybovat
    m_staffNode = m_perfSceneNode->createChildSceneNode( "StaffNode" );
    m_staffNode->setPosition( 0, 0, 0 );
    m_staff = new Staff( m_sceneMgr, m_staffNode );

    m_staff->loadElements();


    // Uzel Krku
    m_neckNode = m_perfSceneNode->createChildSceneNode( "NeckNode" );
    m_neck	   = new Neck( m_sceneMgr, m_neckNode, m_staff );
    m_neckNode->setPosition( 0, 0, 0 );

    /////////////////////////////////////////////////////

}

void PerformanceState::exit() {
    OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Leaving PerformanceState..." );
    m_sceneMgr->destroyCamera( m_pCamera );
    //m_pSceneMgr->destroyQuery(m_pRSQ);
    m_fretGuides->unload();
    if ( m_sceneMgr ) {
        OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager( m_sceneMgr );
    }
}

bool PerformanceState::pause() {
    OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Pausing PerformanceState..." );

    return true;
}

void PerformanceState::resume() {
    OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Resuming GameState..." );

    buildGUI();

    OgreFramework::getSingletonPtr()->m_pViewport->setCamera( m_pCamera );
    m_bQuit = false;
}

void PerformanceState::moveCamera() {
    if ( OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown( OIS::KC_LSHIFT ) ) {
        m_pCamera->moveRelative( m_TranslateVector );
    }
    m_pCamera->moveRelative( m_TranslateVector / 10 );
}

void PerformanceState::getInput() {
    if ( m_bSettingsMode == false ) {
        if ( OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown( OIS::KC_A ) ) {
            m_TranslateVector.x = -m_MoveScale;
        }

        if ( OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown( OIS::KC_D ) ) {
            m_TranslateVector.x = m_MoveScale;
        }

        if ( OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown( OIS::KC_W ) ) {
            m_TranslateVector.z = -m_MoveScale;
        }

        if ( OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown( OIS::KC_S ) ) {
            m_TranslateVector.z = m_MoveScale;
        }
    }
}

void PerformanceState::buildGUI() {
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showFrameStats( OgreBites::TL_BOTTOMLEFT );
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showLogo( OgreBites::TL_BOTTOMRIGHT );
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createLabel( OgreBites::TL_TOP, "GameLbl", "Performance", 250 );
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();

    Ogre::StringVector items;
    items.push_back( "cam.pX" );
    items.push_back( "cam.pY" );
    items.push_back( "cam.pZ" );
    items.push_back( "cam.oW" );
    items.push_back( "cam.oX" );
    items.push_back( "cam.oY" );
    items.push_back( "cam.oZ" );
    items.push_back( "Mode" );

    m_pDetailsPanel = OgreFramework::getSingletonPtr()->m_pTrayMgr->createParamsPanel( OgreBites::TL_TOPLEFT, "DetailsPanel", 200, items );
    m_pDetailsPanel->show();

    Ogre::StringVector displayModes;
    displayModes.push_back( "Solid mode" );
    displayModes.push_back( "Wireframe mode" );
    displayModes.push_back( "Point mode" );
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createLongSelectMenu( OgreBites::TL_TOPRIGHT, "DisplayModeSelMenu", "Display Mode", 200, 3, displayModes );
}

bool PerformanceState::keyPressed( const OIS::KeyEvent &keyEventRef ) {
    if ( m_bSettingsMode == true ) {
        if ( OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown( OIS::KC_S ) ) {
            OgreBites::SelectMenu* pMenu = (OgreBites::SelectMenu*)OgreFramework::getSingletonPtr()->m_pTrayMgr->getWidget( "DisplayModeSelMenu" );
            if ( pMenu->getSelectionIndex() + 1 < (int)pMenu->getNumItems() ) {
                pMenu->selectItem( pMenu->getSelectionIndex() + 1 );
            }
        }

        if ( OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown( OIS::KC_W ) ) {
            OgreBites::SelectMenu* pMenu = (OgreBites::SelectMenu*)OgreFramework::getSingletonPtr()->m_pTrayMgr->getWidget( "DisplayModeSelMenu" );
            if ( pMenu->getSelectionIndex() - 1 >= 0 ) {
                pMenu->selectItem( pMenu->getSelectionIndex() - 1 );
            }
        }
    }

    if ( OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown( OIS::KC_ESCAPE ) ) {
        pushAppState( findByName( "PauseState" ) );
        return true;
    }

    if ( OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown( OIS::KC_I ) ) {
        if ( m_pDetailsPanel->getTrayLocation() == OgreBites::TL_NONE ) {
            OgreFramework::getSingletonPtr()->m_pTrayMgr->moveWidgetToTray( m_pDetailsPanel, OgreBites::TL_TOPLEFT, 0 );
            m_pDetailsPanel->show();
        } else
        {
            OgreFramework::getSingletonPtr()->m_pTrayMgr->removeWidgetFromTray( m_pDetailsPanel );
            m_pDetailsPanel->hide();
        }
    }

    if ( OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown( OIS::KC_TAB ) ) {
        m_bSettingsMode = !m_bSettingsMode;
        return true;
    }

    if ( m_bSettingsMode && OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown( OIS::KC_RETURN ) ||
         OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown( OIS::KC_NUMPADENTER ) ) {
    }

    if ( !m_bSettingsMode || ( m_bSettingsMode && !OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown( OIS::KC_O ) ) ) {
        OgreFramework::getSingletonPtr()->keyPressed( keyEventRef );
    }

    return true;
}

bool PerformanceState::keyReleased( const OIS::KeyEvent &keyEventRef ) {
    OgreFramework::getSingletonPtr()->keyPressed( keyEventRef );
    return true;
}

bool PerformanceState::mouseMoved( const OIS::MouseEvent &evt ) {
    if ( OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseMove( evt ) ) {
        return true;
    }

    if ( m_bRMouseDown ) {
        m_pCamera->yaw( Degree( evt.state.X.rel * -0.1f ) );
        m_pCamera->pitch( Degree( evt.state.Y.rel * -0.1f ) );
    }

    return true;
}

bool PerformanceState::mousePressed( const OIS::MouseEvent &evt, OIS::MouseButtonID id ) {
    if ( OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown( evt, id ) ) {
        return true;
    }

    if ( id == OIS::MB_Left ) {
        onLeftPressed( evt );
        m_bLMouseDown = true;
    } else if ( id == OIS::MB_Right ) {
        m_bRMouseDown = true;
    }

    return true;
}

bool PerformanceState::mouseReleased( const OIS::MouseEvent &evt, OIS::MouseButtonID id ) {
    if ( OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp( evt, id ) ) {
        return true;
    }

    if ( id == OIS::MB_Left ) {
        m_bLMouseDown = false;
    } else if ( id == OIS::MB_Right ) {
        m_bRMouseDown = false;
    }

    return true;
}

void PerformanceState::onLeftPressed( const OIS::MouseEvent &evt ) {

}

void PerformanceState::itemSelected( OgreBites::SelectMenu *menu ) {
    switch ( menu->getSelectionIndex() )
    {
    case 0:
        m_pCamera->setPolygonMode( Ogre::PM_SOLID ); break;
    case 1:
        m_pCamera->setPolygonMode( Ogre::PM_WIREFRAME ); break;
    case 2:
        m_pCamera->setPolygonMode( Ogre::PM_POINTS ); break;
    }
}

void PerformanceState::update( double timeSinceLastFrame ) {
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    OgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued( m_FrameEvent );

    if ( m_bQuit == true ) {
        popAppState();
        return;
    }

    if ( !OgreFramework::getSingletonPtr()->m_pTrayMgr->isDialogVisible() ) {
        if ( m_pDetailsPanel->isVisible() ) {
            m_pDetailsPanel->setParamValue( 0, Ogre::StringConverter::toString( m_pCamera->getDerivedPosition().x ) );
            m_pDetailsPanel->setParamValue( 1, Ogre::StringConverter::toString( m_pCamera->getDerivedPosition().y ) );
            m_pDetailsPanel->setParamValue( 2, Ogre::StringConverter::toString( m_pCamera->getDerivedPosition().z ) );
            m_pDetailsPanel->setParamValue( 3, Ogre::StringConverter::toString( m_pCamera->getDerivedOrientation().w ) );
            m_pDetailsPanel->setParamValue( 4, Ogre::StringConverter::toString( m_pCamera->getDerivedOrientation().x ) );
            m_pDetailsPanel->setParamValue( 5, Ogre::StringConverter::toString( m_pCamera->getDerivedOrientation().y ) );
            m_pDetailsPanel->setParamValue( 6, Ogre::StringConverter::toString( m_pCamera->getDerivedOrientation().z ) );
            if ( m_bSettingsMode ) {
                m_pDetailsPanel->setParamValue( 7, "Buffered Input" );
            } else {
                m_pDetailsPanel->setParamValue( 7, "Un-Buffered Input" );
            }
        }
    }
    //1s = 1000
    m_staffNode->translate( ( SceneSettings::direction / SongInfo::getTempoMultiplier() ) * timeSinceLastFrame, Ogre::Node::TS_LOCAL );

    m_staff->update();

    m_MoveScale = m_MoveSpeed   * timeSinceLastFrame;
    m_RotScale	= m_RotateSpeed * timeSinceLastFrame;

    m_TranslateVector = Vector3::ZERO;

    getInput();
    moveCamera();
}
