#ifndef SONGLISTSTATE_H
#define SONGLISTSTATE_H

#include "AppState.hpp"
#include "../SongInfo.h""

class SongListState : public AppState
{
public:
    SongInfo* m_pSongInfo;

    SongListState(AppStateListener *AppStateManager);
    ~SongListState();

    void enter();
    void createScene();
    void exit();

    bool keyPressed(const OIS::KeyEvent &keyEventRef);
    bool keyReleased(const OIS::KeyEvent &keyEventRef);

    bool mouseMoved(const OIS::MouseEvent &evt);
    bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

    void buttonHit(OgreBites::Button* button);

    void update(double timeSinceLastFrame);
};

#endif // SONGLISTSTATE_H
