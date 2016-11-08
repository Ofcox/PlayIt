#ifndef FRETGUIDE_H
#define FRETGUIDE_H
#include <string>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "SceneSettings.h"

/*
===============================================================================

    This class shows, how to put hands on the neck by placing rectangles
    between fretlines

===============================================================================
*/

class FretGuide
{
private:
    static const int	NUM_FRETLINES = 25;
    Ogre::Entity*		m_fretLinesEntity[NUM_FRETLINES];
    Ogre::Entity*		m_fretsEntity[NUM_FRETLINES];
    Ogre::SceneNode*	m_fretLinesNode[NUM_FRETLINES];
    Ogre::SceneNode*	m_fretsNode[NUM_FRETLINES];
    Ogre::SceneManager* m_pSceneMgr;
    Ogre::SceneNode*	m_pFretLinesNode;
    int					m_width;
public:
    FretGuide( Ogre::SceneManager *pSceneMgr );
    ~FretGuide();

//    static int const MAX_ENTITIES = 512;       // max number of guides

//    float m_timePositionBegin[MAX_ENTITIES];
//    float m_timePositionEnd[MAX_ENTITIES];
//    short m_fret[MAX_ENTITIES];           // position on the timeline
//    short m_size[MAX_ENTITIES];               //size for inclusion of the next fretlines



    void load( Ogre::SceneNode* fretLinesNode );
    void unload();
};

#endif // FRETGUIDE_H
