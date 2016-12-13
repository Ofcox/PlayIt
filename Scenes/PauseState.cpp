#include "PauseState.hpp"

using namespace Ogre;

PauseState::PauseState(AppStateListener* AppStateManager){
    m_bQuit           = false;
    m_bQuestionActive = false;
    m_FrameEvent      = Ogre::FrameEvent();
    m_pAppStateMgr    = AppStateManager;
}

PauseState::~PauseState(){
}

void PauseState::enter(){
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering PauseState...");

    m_sceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "PauseSceneMgr");
    m_sceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f) );

    m_sceneMgr->addRenderQueueListener(OgreFramework::getSingletonPtr()->m_pOverlaySystem);

    // Bude lepší mít pro hlavní scénu a pro pauzu stejnou kameru, aby měl hráč dojem že pořád může hrát.
    m_pCamera = m_sceneMgr->createCamera("PauseCam");
    m_pCamera->setPosition(Vector3(0, 25, -50) );
    m_pCamera->lookAt(Vector3(0, 0, 0) );
    m_pCamera->setNearClipDistance(1);

    m_pCamera->setAspectRatio(Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth() ) /
                              Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight() ) );

    OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

    OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "BackToGameBtn", "Return", 250);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "BackToMenuBtn", "Exit to Menu", 250);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "ExitBtn", "Quit", 250);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createLabel(OgreBites::TL_TOP, "PauseLbl", "Pause mode", 250);

    m_bQuit = false;

    createScene();
}

void PauseState::createScene(){
}

void PauseState::exit(){
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving PauseState...");

    m_sceneMgr->destroyCamera(m_pCamera);
    if(m_sceneMgr)
        OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_sceneMgr);

    OgreFramework::getSingletonPtr()->m_pTrayMgr->clearAllTrays();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->setListener(0);
}

bool PauseState::keyPressed(const OIS::KeyEvent &keyEventRef){
    if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE) && !m_bQuestionActive)
    {
        m_bQuit = true;
        return true;
    }

    OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);

    return true;
}

bool PauseState::keyReleased(const OIS::KeyEvent &keyEventRef){
    OgreFramework::getSingletonPtr()->keyReleased(keyEventRef);

    return true;
}

bool PauseState::mouseMoved(const OIS::MouseEvent &evt){
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseMove(evt) ) return true;
    return true;
}

bool PauseState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id){
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id) ) return true;
    return true;
}

bool PauseState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id){
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id) ) return true;
    return true;
}

void PauseState::update(double timeSinceLastFrame){
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    OgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);

    if(m_bQuit == true)
    {
        popAppState();
        return;
    }
}

void PauseState::buttonHit(OgreBites::Button *button){
    if(button->getName() == "ExitBtn")
    {
        OgreFramework::getSingletonPtr()->m_pTrayMgr->showYesNoDialog("Sure?", "Really leave?");
        m_bQuestionActive = true;
    }
    else if(button->getName() == "BackToGameBtn")
        m_bQuit = true;
    else if(button->getName() == "BackToMenuBtn")
        popAllAndPushAppState(getAppState(GS_MenuState) );
}

void PauseState::yesNoDialogClosed(const Ogre::DisplayString& question, bool yesHit){
    if(yesHit == true)
        shutdown();
    else
        OgreFramework::getSingletonPtr()->m_pTrayMgr->closeDialog();

    m_bQuestionActive = false;
}
