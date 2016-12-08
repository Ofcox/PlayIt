#ifndef NECK_H
#define NECK_H
#include "Strings.h"
#include "Targets.h"

/*
===============================================================================

    This class holds all elements bound to the neck like strings or targets

===============================================================================
*/

class Neck {
public:
    Neck( Ogre::SceneManager* pSceneMgr, Ogre::SceneNode* pNeckNode );
    ~Neck();
    Targets* getTargets() { return m_targets; }

private:
    Strings* m_strings;
    Targets* m_targets;
};

#endif // NECK_H
