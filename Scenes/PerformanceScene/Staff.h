#ifndef STAFF_H
#define STAFF_H
#include "NotationFileParser.h"

#include "SceneSettings.h"
#include "strings.h"

/*
===============================================================================

    Loads staff elements
    Notes
    Chords
    Targets?

===============================================================================
*/

class Staff
{
private:
    Strings* m_strings;

    // Number of the last element that passed through strings
    int m_lastPassedElement;
    int m_currentElement;
    // Number of next element that passing through strings
    int m_nextElement;

    // Position informations of all notes and chords
    std::vector<Element*> elements;

    // Pointer of scene node
    Ogre::SceneNode* m_staffNode;

    Ogre::SceneManager* m_pSceneMgr;
    NotationFileParser* m_pNotationFileParser;

    void showTarget();
    bool elementHasReachedTarget();
    bool elementIsInStringsRange( Element *element );

public:
    Staff( Ogre::SceneManager* pSceneMgr, Ogre::SceneNode* pStaffNode );
    ~Staff();

    void loadElements();

    //void setSringsObject(Strings* pStringsObject){m_strings = pStringsObject;}

    void update();
    void load();
    void unload();
};

#endif // STAFF_H
