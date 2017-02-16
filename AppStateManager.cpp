#include "AppStateManager.hpp"

#include <OgreWindowEventUtilities.h>

AppStateManager::AppStateManager() {
    m_bShutdown = false;
}

AppStateManager::~AppStateManager() {

    while( !m_activeStateStack.empty() ) {
        m_activeStateStack.back()->exit();
        m_activeStateStack.pop_back();
    }

    while( !m_states.empty() ) {
        m_states.back()->destroy();
        m_states.pop_back();
    }
}

void AppStateManager::manageAppState( AppState* state) {
        m_states.push_back(state);
}

AppState* AppStateManager::getAppState(GameState gameState) {
    switch (gameState) {
    case GS_MenuState:
        return m_states[0];
        break;
    case GS_PauseState:
        return m_states[1];
        break;
    case GS_SongListState:
        return m_states[2];
        break;
    case GS_PerformanceState:
        return m_states[3];
        break;
    default:
        return NULL;
        break;
    }
}

void AppStateManager::start(AppState* state) {
    changeAppState(state);

    int timeSinceLastFrame = 1;
    int startTime          = 0;

    while( !m_bShutdown ) {
        if( OgreFramework::getSingletonPtr()->m_pRenderWnd->isClosed() ) m_bShutdown = true;

        Ogre::WindowEventUtilities::messagePump();

        if( OgreFramework::getSingletonPtr()->m_pRenderWnd->isActive() ) {
            startTime = OgreFramework::getSingletonPtr()->m_pTimer->getMillisecondsCPU();

            OgreFramework::getSingletonPtr()->m_pKeyboard->capture();
            OgreFramework::getSingletonPtr()->m_pMouse->capture();

            m_activeStateStack.back()->update(timeSinceLastFrame);

            OgreFramework::getSingletonPtr()->updateOgre(timeSinceLastFrame);
            OgreFramework::getSingletonPtr()->m_pRoot->renderOneFrame();

            timeSinceLastFrame = OgreFramework::getSingletonPtr()->m_pTimer->getMillisecondsCPU() - startTime;
        } else {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            Sleep(1000);
#else
            sleep(1);
#endif
        }
    }

    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Main loop quit");
}

void AppStateManager::changeAppState(AppState* state) {
    if( !m_activeStateStack.empty() ) {
        m_activeStateStack.back()->exit();
        m_activeStateStack.pop_back();
    }

    m_activeStateStack.push_back(state);
    init(state);
    m_activeStateStack.back()->enter();
}

bool AppStateManager::pushAppState(AppState* state) {

    if( !m_activeStateStack.empty() ) {
        if( !m_activeStateStack.back()->pause() )
            return false;
    }

    m_activeStateStack.push_back(state);
    init(state);
    m_activeStateStack.back()->enter();

    return true;
}

void AppStateManager::popAppState() {

    if( !m_activeStateStack.empty() ) {
        m_activeStateStack.back()->exit();
        m_activeStateStack.pop_back();
    }

    if( !m_activeStateStack.empty() ) {
        init(m_activeStateStack.back() );
        m_activeStateStack.back()->resume();
    } else
        shutdown();
}

void AppStateManager::popAllAndPushAppState(AppState* state) {
    while( !m_activeStateStack.empty() ) {
        m_activeStateStack.back()->exit();
        m_activeStateStack.pop_back();
    }

    pushAppState(state);
}

void AppStateManager::pauseAppState() {
    if( !m_activeStateStack.empty() ) {
        //Calls a Pause method of the last object in ActiveStateStack
        m_activeStateStack.back()->pause();
    }

    if( m_activeStateStack.size() > 2 ) {
        init(m_activeStateStack.at(m_activeStateStack.size() - 2) );
        m_activeStateStack.at(m_activeStateStack.size() - 2)->resume();
    }
}

void AppStateManager::shutdown() {
    m_bShutdown = true;
}

void AppStateManager::init(AppState* state) {
    OgreFramework::getSingletonPtr()->m_pKeyboard->setEventCallback(state);
    OgreFramework::getSingletonPtr()->m_pMouse->setEventCallback(state);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->setListener(state);

    OgreFramework::getSingletonPtr()->m_pRenderWnd->resetStatistics();
}
