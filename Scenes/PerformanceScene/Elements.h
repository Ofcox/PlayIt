#ifndef ELEMENTS_H
#define ELEMENTS_H
#include "Chord.h"
#include "NotationFileParser.h"
#include "Targets.h"
using VectorElements = std::vector<Element*>;

class Elements {
public:
    Ogre::SceneNode*	m_staffNode;
    Ogre::SceneManager* m_sceneMgr;

    /*std::vector<Element*>*/ VectorElements m_elementsVector;

    Elements( Ogre::SceneManager *pSceneMgr, Ogre::SceneNode *pStaffNode );
    ~Elements();
    void loadElements( NotationFileParser* pNotationFileParser );
    void setTargets( Targets* pTargets ) {targets = pTargets; }
    VectorElements& getElementsVector(){return m_elementsVector;}


private:
    // Number of the last element that passed through strings
    int m_lastPassedElement;
    int m_currentElement;
    // Number of next element that passing through strings
    int m_nextElement;

    Targets* targets;
};

#endif // ELEMENTS_H
