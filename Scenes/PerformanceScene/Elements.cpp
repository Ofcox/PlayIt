#include "Elements.h"

Elements::Elements( Ogre::SceneManager *pSceneMgr, Ogre::SceneNode *pStaffNode ) {
    m_lastPassedElement = 0;
    m_nextElement		= 0;
    m_currentElement	= 0;
    m_sceneMgr			= pSceneMgr;
    m_staffNode			= pStaffNode;
}

Elements::~Elements() {
    while ( !m_elements.empty() ) {
        delete m_elements.back();
        m_elements.pop_back();
    }
}

void Elements::loadElements( NotationFileParser * pNotationFileParser ) {
    pNotationFileParser->loadElements( m_elements );
    pNotationFileParser->createElementsModels( m_elements, m_sceneMgr, m_staffNode );
}
