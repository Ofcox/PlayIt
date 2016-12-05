#ifndef PLAYIT_HPP
#define PLAYIT_HPP

#include <memory>
#include "AdvancedOgreFramework.hpp"
#include "AppStateManager.hpp"

#include "scenes/MenuState.hpp"
#include "scenes/PauseState.hpp"
#include "scenes/SongListState.hpp"
#include "scenes/PerformanceState.hpp"

class PlayIt{
public:
    PlayIt();
    ~PlayIt();

    void start();

private:
    AppStateManager* m_pAppStateManager;

    AppState* findByName( GameState gameState ) {
        return m_pParent->getAppState( gameState );
    }
    void changeAppState( AppState* state ) {
        m_pParent->changeAppState( state );
    }
    bool pushAppState( AppState* state ) {
        return m_pParent->pushAppState( state );
    }
    void popAppState() {
        m_pParent->popAppState();
    }
    void shutdown() {
        m_pParent->shutdown();
    }
    void popAllAndPushAppState( AppState* state ) {
        m_pParent->popAllAndPushAppState( state );
    }

    AppStateListener* m_pParent;

    Ogre::Camera*       m_pCamera;
    Ogre::SceneManager* m_pSceneMgr;
    Ogre::FrameEvent    m_FrameEvent;


    MenuState*        myMenuState;
    PauseState*       myPauseState;
    SongListState*    mySongListState;
    PerformanceState* myPerformanceState;
};

#endif // PLAYIT_HPP
