#ifndef BAR_H
#define BAR_H
#include <string>
#include <vector>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "SceneSettings.h"

class Bar {
public:
    Ogre::Entity*    m_barEntity;
    Ogre::SceneNode* m_barNode;
    Ogre::SceneManager* m_sceneMgr;

    Bar( Ogre::SceneManager *pSceneMgr, Ogre::SceneNode *pFretGuideNode, int fret, int size, int barNumber){
        m_sceneMgr = pSceneMgr;
        m_barEntity = m_sceneMgr->createEntity( "cube.mesh" );

        m_barNode = pFretGuideNode->createChildSceneNode();
        m_barNode->attachObject( m_barEntity );
        m_barNode->setPosition( 0, 0, -(barNumber * SceneSettings::barScale) );
        m_barNode->setScale( 40, 0.2, 1 );
    }
};

#endif // BAR_H
