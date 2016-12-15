#ifndef FRETGUIDE_H
#define FRETGUIDE_H
#include <string>
#include <vector>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "SceneSettings.h"
#include "Bar.h"

/*
===============================================================================

    This class shows how to put fingers on the neck by placing rectangles
    between fretlines on the staff
    TODO:   Implement this class, because it's crucial for automated camera
            Move to the Neck class

===============================================================================
*/

class FretTrail {
public:
    Ogre::Entity*    m_fretTrailEntity;
    Ogre::SceneNode* m_fretTrailNode;
    Ogre::SceneManager* m_sceneMgr;

    FretTrail( Ogre::SceneManager *pSceneMgr, Ogre::SceneNode *pFretGuideNode, int fret, float timePosition, float size ){
        m_sceneMgr = pSceneMgr;
        m_fretTrailEntity = m_sceneMgr->createEntity( "cube.mesh" );

        m_fretTrailNode = pFretGuideNode->createChildSceneNode();
        m_fretTrailNode->attachObject( m_fretTrailEntity );
        m_fretTrailNode->setPosition( 0, 0, -0 );
        m_fretTrailNode->setScale( 4, 4, 0.0 );
    }

};

class FretGuide {
public:
    std::vector<Bar*> m_vectorBars;
    std::vector<FretTrail*> m_vectorFretTrails;
    Ogre::SceneManager* m_sceneMgr;
    Ogre::SceneNode* m_fretGuideNode;

    FretGuide( Ogre::SceneManager* pSceneMgr, Ogre::SceneNode* pStaffNode) {
        m_sceneMgr = pSceneMgr;
        for (int itr = 0; itr <= SceneSettings::barCount + 2; itr++){
            m_vectorBars.push_back(new Bar(m_sceneMgr, pStaffNode,0 , 4, itr ));
        }
    }

};

#endif // FRETGUIDE_H
