#ifndef STAFF_H
#define STAFF_H
#include "NotationFileParser.h"

#include "SceneSettings.h"
#include "Elements.h"
#include "Neck.h"

/*
===============================================================================

    Loads
            Staff elements
                Notes
                Chords

===============================================================================
*/

class Staff
{
private:

    // Position informations of all notes and chords
    Elements* m_elements;

    // Pointer of scene node
    Ogre::SceneNode* m_staffNode;

    Ogre::SceneManager* m_sceneMgr;
    NotationFileParser* m_notationFileParser;

    Neck* m_neck;

    // Number of the last element that passed through strings
    int m_lastPassedElement;
    int m_currentElement;
    // Number of next element that passing through strings
    int m_upcomingElement;

public:
    Staff( Ogre::SceneManager* pSceneMgr, Ogre::SceneNode* pStaffNode, Neck* pNeck );
    ~Staff();

    void loadElements();
    bool elementHasReachedTarget();
    bool elementIsInStringsRange();

    void update();

};

#endif // STAFF_H
