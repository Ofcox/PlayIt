#ifndef ELEMENTS_H
#define ELEMENTS_H
#include "Chord.h"
#include "NotationFileParser.h"

class Elements
{
public:
    // Number of the last element that passed through strings
    int m_lastPassedElement;
    int m_currentElement;
    // Number of next element that passing through strings
    int m_nextElement;

    Ogre::SceneNode*	m_staffNode;
    Ogre::SceneManager* m_pSceneMgr;

    std::vector<Element*> m_elements;
    Elements( Ogre::SceneManager *pSceneMgr, Ogre::SceneNode *pStaffNode );
    ~Elements();
    void loadElements( NotationFileParser* pNotationFileParser );

    bool elementHasReachedTarget();
    bool elementIsInStringsRange( Element* element );
    void update();
};

#endif // ELEMENTS_H
