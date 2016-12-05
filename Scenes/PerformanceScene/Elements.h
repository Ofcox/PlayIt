#ifndef ELEMENTS_H
#define ELEMENTS_H
#include "Chord.h"
#include "NotationFileParser.h"
#include "Targets.h"

class Elements
{
public:
    // Number of the last element that passed through strings
    int m_lastPassedElement;
    int m_currentElement;
    // Number of next element that passing through strings
    int m_nextElement;

    Ogre::SceneNode*	m_staffNode;
    Ogre::SceneManager* m_sceneMgr;

    std::vector<Element*> m_elements;

    Targets* targets;

    Elements( Ogre::SceneManager *pSceneMgr, Ogre::SceneNode *pStaffNode );
    ~Elements();
    void loadElements( NotationFileParser* pNotationFileParser );
    void setTargets( Targets* pTargets ) {targets = pTargets; }
};

#endif // ELEMENTS_H
