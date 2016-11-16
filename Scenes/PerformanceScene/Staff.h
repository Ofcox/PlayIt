#ifndef STAFF_H
#define STAFF_H
#include "NotationFileParser.h"

#include "SceneSettings.h"
#include "Strings.h"
#include "Elements.h"

/*
===============================================================================

    Loads   Strings
            Staff elements
                Notes
                Chords

===============================================================================
*/

class Staff
{
private:
    Strings* m_strings;

    // Position informations of all notes and chords
    Elements* m_elements;

    // Pointer of scene node
    Ogre::SceneNode* m_staffNode;

    Ogre::SceneManager* m_pSceneMgr;
    NotationFileParser* m_pNotationFileParser;

public:
    Staff( Ogre::SceneManager* pSceneMgr, Ogre::SceneNode* pStaffNode );
    ~Staff();

    void loadElements();

    void update();

};

#endif // STAFF_H
