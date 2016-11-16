#include "Staff.h"

Staff::Staff( Ogre::SceneManager *pSceneMgr, Ogre::SceneNode *pStaffNode ) {
    m_sceneMgr	= pSceneMgr;
    m_staffNode = pStaffNode;

    m_elements			 = new Elements( m_sceneMgr, m_staffNode );
    m_notationFileParser = new NotationFileParser( "notation.xml" );
}

Staff::~Staff() {
    m_staffNode->removeAndDestroyAllChildren();
    delete m_notationFileParser;
}

void Staff::loadElements() {
    m_elements->loadElements( m_notationFileParser );
}

void Staff::update() {
    m_elements->update();
}
