#include "PlayIt.hpp"

PlayIt::PlayIt() {
    m_pAppStateManager = nullptr;
}

PlayIt::~PlayIt() {
    delete m_pAppStateManager;
    delete OgreFramework::getSingletonPtr();
}

void PlayIt::start() {
    new OgreFramework();
    if ( !OgreFramework::getSingletonPtr()->initOgre( "Project Uketard pre-aplha 0.00001", 0, 0 ) ) {
        return;
    }

    OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Project Uketard initialized!" );

    m_pAppStateManager = new AppStateManager();

    myMenuState        = new MenuState( m_pAppStateManager );
    myPauseState       = new PauseState( m_pAppStateManager );
    mySongListState    = new SongListState( m_pAppStateManager );
    myPerformanceState = new PerformanceState( m_pAppStateManager );

    // Must be sorted same as the GameStates enum
    m_pAppStateManager->manageAppState( myMenuState );
    m_pAppStateManager->manageAppState( myPauseState );
    m_pAppStateManager->manageAppState( mySongListState );
    m_pAppStateManager->manageAppState( myPerformanceState );

    m_pAppStateManager->start( m_pAppStateManager->getAppState( GS_MenuState ) );
}
