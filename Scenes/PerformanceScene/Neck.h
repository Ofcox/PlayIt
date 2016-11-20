#ifndef NECK_H
#define NECK_H
#include "Strings.h"
#include "Targets.h"
#include "Staff.h"

class Neck
{
public:
    Strings* m_strings;
    Targets* m_targets;

    Elements* m_elements;

    Neck( Ogre::SceneManager *pSceneMgr, Ogre::SceneNode *pNeckNode, Staff* pStaff );
};

#endif // NECK_H
