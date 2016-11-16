#include "Staff.h"

Staff::Staff( Ogre::SceneManager *pSceneMgr, Ogre::SceneNode *pStaffNode ) {
    m_pSceneMgr = pSceneMgr;
    m_staffNode = pStaffNode;

    m_elements			  = new Elements( m_pSceneMgr, m_staffNode );
    m_pNotationFileParser = new NotationFileParser( "notation.xml" );
    //m_pNotationFileParser->loadElements( m_elements->m_elements );
}

Staff::~Staff() {
    m_staffNode->removeAndDestroyAllChildren();
    delete m_pNotationFileParser;
}

void Staff::loadElements() {
    m_elements->loadElements( m_pNotationFileParser );
}

void Staff::update() {
    m_elements->update();
}
