//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef OGRE_DEMO_HPP
#define OGRE_DEMO_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||
#include <memory>
#include "AdvancedOgreFramework.hpp"
#include "AppStateManager.hpp"

#include "states/MenuState.hpp"
#include "states/PauseState.hpp"
#include "states/SongListState.hpp"
#include "states/PerformanceState.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

class DemoApp
{
public:
    DemoApp();
    ~DemoApp();

    void startDemo();

private:
    AppStateManager* m_pAppStateManager;

    AppState*   findByName( Ogre::String stateName ) {return m_pParent->findByName( stateName ); }
    void        changeAppState( AppState* state ) {m_pParent->changeAppState( state ); }
    bool        pushAppState( AppState* state ) {return m_pParent->pushAppState( state ); }
    void        popAppState() {m_pParent->popAppState(); }
    void        shutdown() {m_pParent->shutdown(); }
    void        popAllAndPushAppState( AppState* state ) {m_pParent->popAllAndPushAppState( state ); }

    AppStateListener* m_pParent;

    Ogre::Camera*		m_pCamera;
    Ogre::SceneManager* m_pSceneMgr;
    Ogre::FrameEvent	m_FrameEvent;


    MenuState*		  myMenuState;
    PauseState*		  myPauseState;
    SongListState*	  mySongListState;
    PerformanceState* myPerformanceState;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
