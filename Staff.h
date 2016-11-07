#ifndef STAFF_H
#define STAFF_H
//#include <vector>
#include "NotationFileParser.h"
//#include <OgreSceneManager.h>
//#include <OgreEntity.h>
#include "states/PerformanceScene/SceneSettings.h"
#include "states/PerformanceScene/strings.h"

/*
===============================================================================

    TODO change name to Staff
    Loads staff elements
    Notes
    Chords
    Targets?

===============================================================================
*/

class Staff
{
    // Pointer of scene node
    Ogre::SceneNode* m_staffNode;

public:
    Staff( Ogre::SceneManager* pSceneMgr, Ogre::SceneNode* pStaffNode );
    ~Staff();

    Ogre::SceneManager* m_pSceneMgr;
    NotationFileParser* m_pNotationFileParser;

    Strings* m_strings;

    // Position informations of all notes and chords
    std::vector<Element*> elements;
    // Number of the last element that passed through strings
    int m_lastPassedElement;
    int m_currentElement;
    // Number of next element that passing through strings
    int m_nextElement;

    void loadElements();
    void showTarget();
    bool elementHasReachedTarget();
    bool elementIsInStringsRange( Element *element );

    //void setSringsObject(Strings* pStringsObject){m_strings = pStringsObject;}

    void update();
    void load();
    void unload();
};

#endif // STAFF_H
