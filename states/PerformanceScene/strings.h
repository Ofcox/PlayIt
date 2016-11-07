#ifndef STRINGS_H
#define STRINGS_H
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "SceneSettings.h"

class Strings{
public:
    Ogre::SceneNode* m_pStringsNode;

    Strings(Ogre::SceneManager* pSceneMgr);
    ~Strings();
    static const int NUM_STRINGS = 4;
    Ogre::Entity* m_stringsEntity[NUM_STRINGS];
    Ogre::SceneNode* m_stringsNode[NUM_STRINGS];
    Ogre::SceneManager* m_sceneMgr;

    void load(Ogre::SceneNode* stringsNode);
};

#endif // STRINGS_H
