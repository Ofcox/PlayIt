#ifndef PERFORMANCESTATE_H
#define PERFORMANCESTATE_H

#include "AppState.hpp"

#include <OgreSubEntity.h>
#include <OgreMaterialManager.h>
#include <vector>

#include "PerformanceScene/Frets.h"
#include "PerformanceScene/Strings.h"
#include "PerformanceScene/Staff.h"
#include "PerformanceScene/Neck.h"

#include "PerformanceScene/NotationFileParser.h"

#include "SongListScene/SongInfo.h"

/*
===============================================================================

    This class is processing the scene where you play

    includes
    Notes
    FretGuide

    Neck
    Strings
    FretLines

    Notes and FretGuide are bound to the Staff. The Staff is shifting in Z axis.

===============================================================================
*/

class PerformanceState : public AppState{
public:
    PerformanceState( AppStateListener* AppStateManager );
    ~PerformanceState();

    void enter();
    void createScene();
    void exit();
    bool pause();
    void resume();

    void moveCamera();
    void getInput();
    void buildGUI();

    bool keyPressed( const OIS::KeyEvent &keyEventRef );
    bool keyReleased( const OIS::KeyEvent &keyEventRef );

    bool mouseMoved( const OIS::MouseEvent &arg );
    bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    void onLeftPressed( const OIS::MouseEvent &evt );
    void itemSelected( OgreBites::SelectMenu* menu );

    void update( double timeSinceLastFrame );

private:
    OgreBites::ParamsPanel* m_pDetailsPanel;
    bool m_bQuit;

    Ogre::Vector3 m_TranslateVector;
    Ogre::Real	  m_MoveSpeed;
    Ogre::Degree  m_RotateSpeed;
    float		  m_MoveScale;
    Ogre::Degree  m_RotScale;

    bool m_bLMouseDown, m_bRMouseDown;
    bool m_bSettingsMode;

    Ogre::Vector3 m_direction;

    Ogre::SceneNode* m_perfSceneNode = nullptr;
    Ogre::SceneNode* m_fretLinesNode = nullptr;
    Ogre::SceneNode* m_neckNode = nullptr;
    Ogre::SceneNode* m_staffNode = nullptr;

    Frets* m_frets = nullptr;
    Staff* m_staff = nullptr;
    Neck*  m_neck = nullptr;

    NotationFileParser* m_notationFileParser = nullptr;
};

#endif // PERFORMANCESTATE_H
