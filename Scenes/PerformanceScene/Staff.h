#ifndef STAFF_H
#define STAFF_H
#include "NotationFileParser.h"

#include "SceneSettings.h"
#include "Elements.h"
#include "Neck.h"
#include "FretGuide.h"

/*
===============================================================================

    This class holds all objects that are on staff

===============================================================================
*/

class Staff {
public:
    Staff( Ogre::SceneManager* pSceneMgr, Ogre::SceneNode* pStaffNode, Neck* pNeck );
    ~Staff();

    void loadElements();
    bool elementHasReachedTarget();
    bool elementIsInStringsRange();

    void update();
    Elements* m_elements = nullptr;

private:
    // Pointer of scene node
    Ogre::SceneNode* m_staffNode = nullptr;

    Ogre::SceneManager* m_sceneMgr = nullptr;
    NotationFileParser* m_notationFileParser = nullptr;

    Neck* m_neck = nullptr;
    FretGuide* m_fretGuide = nullptr;

    // Number of the last element that passed through strings
    int m_lastPassedElement;
    int m_currentElement;
    // Number of next element that passing through strings
    int m_upcomingElement;
};

#endif // STAFF_H
