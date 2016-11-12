#ifndef STRINGS_H
#define STRINGS_H
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "SceneSettings.h"

class Strings {
private:
    static const int	NUM_STRINGS = 4;
    Ogre::Entity*		m_stringsEntity[NUM_STRINGS];
    Ogre::SceneNode*	m_stringsNode[NUM_STRINGS];
    Ogre::SceneManager* m_sceneMgr;
    Ogre::SceneNode*	m_pStringsNode;

public:
    Strings( Ogre::SceneManager* pSceneMgr );
    ~Strings();

    void load( Ogre::SceneNode* stringsNode );
};

#endif // STRINGS_H
