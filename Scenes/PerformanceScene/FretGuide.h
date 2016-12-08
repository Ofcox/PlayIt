#ifndef FRETGUIDE_H
#define FRETGUIDE_H
#include <string>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "SceneSettings.h"

/*
===============================================================================

    This class shows how to put fingers on the neck by placing rectangles
    between fretlines on the staff
    TODO:   Implement this class, because it's crucial for automated camera
            Move to the Neck class

===============================================================================
*/

class FretGuide {
public:
    FretGuide( Ogre::SceneManager *pSceneMgr );
    ~FretGuide();

    void load( Ogre::SceneNode* fretLinesNode );

private:
    static const int    NUM_FRETLINES = 25;
    Ogre::Entity*       m_fretLinesEntity[NUM_FRETLINES];
    Ogre::Entity*       m_fretsEntity[NUM_FRETLINES];
    Ogre::SceneNode*    m_fretLinesNode[NUM_FRETLINES];
    Ogre::SceneNode*    m_fretsNode[NUM_FRETLINES];
    Ogre::SceneManager* m_pSceneMgr;
    Ogre::SceneNode*    m_pFretLinesNode;
    int                 m_width;
};

#endif // FRETGUIDE_H
