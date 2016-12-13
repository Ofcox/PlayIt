#ifndef APP_STATE_MANAGER_HPP
#define APP_STATE_MANAGER_HPP

#include "scenes/AppState.hpp"

class AppStateManager : public AppStateListener{
public:
    AppStateManager();
    ~AppStateManager();

    //Registers a new application states
    void manageAppState(AppState* state );

    //Returns the desired AppState
    AppState* getAppState( GameState gameState );

    //Starts an application with desired AppState
    void start( AppState* state );
    //Changes to desired AppState
    void changeAppState( AppState* state );
    //Override an AppState with desired one. The overriden AppState is still active
    bool pushAppState( AppState* state );
    //Close the AppState
    void popAppState();

    //Pauses the last element in ActiveStateStack
    void pauseAppState();
    //Closes program
    void shutdown();
    //Closes all AppStates in ActiveStateStack and make a desired one
    void popAllAndPushAppState( AppState* state );

protected:
    void init( AppState *state );

    std::vector<AppState*> m_ActiveStateStack;
    std::vector<AppState*> m_States;
    bool                   m_bShutdown;
};

#endif // APP_STATE_MANAGER_HPP
