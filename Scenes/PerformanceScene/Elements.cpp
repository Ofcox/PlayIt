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

//bool Elements::elementHasReachedTarget() {
//    float elementWorldPosition = 0;

//    elementWorldPosition = m_staffNode->getPosition().z + m_elements[m_currentElement]->getNode()->getPosition().z;

//    if ( elementWorldPosition <= 0 ) {
//        return false;
//    } else {
//        return true;
//    }
//}

//bool Elements::elementIsInStringsRange() {
//    int	  range = 280;
//    float elementWorldPosition;

//    elementWorldPosition = m_staffNode->getPosition().z + m_elements[m_nextElement]->getNode()->getPosition().z;

//    if ( elementWorldPosition >= -range ) {
//        return true;
//    } else {
//        return false;
//    }
//}

//void Elements::update() {

//    if ( m_elements[m_nextElement] != NULL  &&  elementIsInStringsRange() ) {

//        if ( m_nextElement < ( m_elements.size() - 1 ) ) {
//            ++m_nextElement;
//        }
//    }

//    if ( elementHasReachedTarget() ) {
//        m_elements[m_currentElement]->setVisibility( false );
//        if ( m_currentElement < ( m_elements.size() - 1 ) ) {
//            ++m_currentElement;
//        }
//    }
//}
