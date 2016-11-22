//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef APP_STATE_HPP
#define APP_STATE_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "../AdvancedOgreFramework.hpp"
#include <iostream>

class AppState;

//|||||||||||||||||||||||||||||||||||||||||||||||

class AppStateListener
{
public:
    AppStateListener() {};
    virtual ~AppStateListener() {};

    virtual void manageAppState( Ogre::String stateName, AppState* state ) = 0;

    virtual AppState*   findByName( Ogre::String stateName )	 = 0;
    virtual void        changeAppState( AppState *state )		 = 0;
    virtual bool        pushAppState( AppState* state )			 = 0;
    virtual void        popAppState()							 = 0;
    virtual void        pauseAppState()							 = 0;
    virtual void        shutdown()								 = 0;
    virtual void        popAllAndPushAppState( AppState* state ) = 0;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

class AppState : public OIS::KeyListener, public OIS::MouseListener, public OgreBites::SdkTrayListener
{
public:
    //static void create(AppStateListener* parent, const Ogre::String name){};

    void destroy() {delete this; }

    virtual void enter() = 0;
    virtual void exit()	 = 0;
    virtual bool pause() {return true; }
    virtual void resume() {};
    virtual void update( double timeSinceLastFrame ) = 0;
    virtual ~AppState() {};

protected:
    AppState() {};

    AppState*   findByName( Ogre::String stateName ) {return m_pAppStateMgr->findByName( stateName ); }
    virtual void        changeAppState( AppState* state ) {m_pAppStateMgr->changeAppState( state ); }
    virtual bool        pushAppState( AppState* state ) {return m_pAppStateMgr->pushAppState( state ); }
    virtual void        popAppState() {m_pAppStateMgr->popAppState(); }
    void        shutdown() {m_pAppStateMgr->shutdown(); }
    void        popAllAndPushAppState( AppState* state ) {m_pAppStateMgr->popAllAndPushAppState( state ); }

    AppStateListener* m_pAppStateMgr;

    Ogre::Camera*		m_pCamera;
    Ogre::SceneManager* m_sceneMgr;
    Ogre::FrameEvent	m_FrameEvent;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
