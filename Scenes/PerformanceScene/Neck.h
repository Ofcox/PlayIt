#ifndef NECK_H
#define NECK_H
#include "Strings.h"
#include "Targets.h"

class Neck
{
private:
    Strings* m_strings;
    Targets* m_targets;

public:
    Neck( Ogre::SceneManager *pSceneMgr, Ogre::SceneNode *pNeckNode );
    Targets* getTargets() {return m_targets; }
};

#endif // NECK_H
