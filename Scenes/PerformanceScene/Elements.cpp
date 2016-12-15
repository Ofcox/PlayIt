#include "Elements.h"

Elements::Elements( Ogre::SceneManager *pSceneMgr, Ogre::SceneNode *pStaffNode ) {
    m_lastPassedElement = 0;
    m_nextElement		= 0;
    m_currentElement	= 0;
    m_sceneMgr			= pSceneMgr;
    m_staffNode			= pStaffNode;
}

Elements::~Elements() {
    while ( !m_elementsVector.empty() ) {
        delete m_elementsVector.back();
        m_elementsVector.pop_back();
    }
}

void Elements::loadElements( NotationFileParser * pNotationFileParser ) {
    pNotationFileParser->loadElements( m_elementsVector );
    pNotationFileParser->createElementsModels( m_elementsVector, m_sceneMgr, m_staffNode );
}
