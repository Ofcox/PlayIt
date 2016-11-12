#ifndef PERFORMANCESTATE_H
#define PERFORMANCESTATE_H

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AppState.hpp"

#include "../DotSceneLoader.hpp"

#include <OgreSubEntity.h>
#include <OgreMaterialManager.h>
#include <vector>

#include "PerformanceScene/fretguide.h"
#include "PerformanceScene/strings.h"
#include "PerformanceScene/Staff.h"

#include "SongListScene/SongInfo.h"

/*
===============================================================================

    Performance scene where you actually play

===============================================================================
*/

class PerformanceState : public AppState
{
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

    std::vector<Ogre::Entity*>	  m_tabEntity;
    std::vector<Ogre::SceneNode*> m_tabNode;

private:
    Ogre::SceneNode*  m_pOgreHeadNode;
    Ogre::Entity*	  m_pOgreHeadEntity;
    Ogre::MaterialPtr m_pOgreHeadMat;
    Ogre::MaterialPtr m_pOgreHeadMatHigh;

    OgreBites::ParamsPanel* m_pDetailsPanel;
    bool					m_bQuit;

    Ogre::Vector3 m_TranslateVector;
    Ogre::Real	  m_MoveSpeed;
    Ogre::Degree  m_RotateSpeed;
    float		  m_MoveScale;
    Ogre::Degree  m_RotScale;

    bool m_bLMouseDown, m_bRMouseDown;
    bool m_bSettingsMode;

    Ogre::Vector3 m_direction;

    Ogre::SceneNode* m_fretLinesNode;
    Ogre::SceneNode* m_stringsNode;
    Ogre::SceneNode* m_staffNode;

    FretGuide* m_pFretGuides;
    Strings*   m_pStrings;
    Staff*	   m_staff;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif // PERFORMANCESTATE_H
