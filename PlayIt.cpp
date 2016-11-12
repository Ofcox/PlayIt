//|||||||||||||||||||||||||||||||||||||||||||||||

#include "PlayIt.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

PlayIt::PlayIt() {
    m_pAppStateManager = 0;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

PlayIt::~PlayIt() {
    delete m_pAppStateManager;
    delete OgreFramework::getSingletonPtr();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void PlayIt::start() {
    new OgreFramework();
    if ( !OgreFramework::getSingletonPtr()->initOgre( "Project Uketard pre-aplha 0.000001", 0, 0 ) ) {
        return;
    }

    OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Demo initialized!" );

    m_pAppStateManager = new AppStateManager();

    myMenuState		   = new MenuState( m_pAppStateManager );
    myPauseState	   = new PauseState( m_pAppStateManager );
    mySongListState	   = new SongListState( m_pAppStateManager );
    myPerformanceState = new PerformanceState( m_pAppStateManager );

    m_pAppStateManager->manageAppState( "MenuState", myMenuState );
    m_pAppStateManager->manageAppState( "PauseState", myPauseState );
    m_pAppStateManager->manageAppState( "SongListState", mySongListState );
    m_pAppStateManager->manageAppState( "PerformanceState", myPerformanceState );


    m_pAppStateManager->start( m_pAppStateManager->findByName( "MenuState" ) );
}

//|||||||||||||||||||||||||||||||||||||||||||||||
