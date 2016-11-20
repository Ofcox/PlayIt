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

bool Elements::elementHasReachedTarget() {
    float elementWorldPosition = 0;

    elementWorldPosition = m_staffNode->getPosition().z + m_elements[m_currentElement]->getNode()->getPosition().z;

    if ( elementWorldPosition < 0 ) {
        return false;
    } else if ( elementWorldPosition >= 0 ) {
        return true;
    }
}

bool Elements::elementIsInStringsRange( Element *element ) {
    int	  range = 280;
    float elementWorldPosition;

    elementWorldPosition = m_staffNode->getPosition().z + element->getNode()->getPosition().z;

    if ( elementWorldPosition <= 0 && elementWorldPosition > -range ) {
        return true;
    } else {     //if (chordWorldPosition > 0)
        return false;
    }
}

void Elements::update() {
    Element* element;

    //Kontrola, jestli je dalsi element v dosahu
    if ( m_elements[m_nextElement] != element ) {
        element = m_elements[m_nextElement];
    }

    if ( elementIsInStringsRange( element ) ) {

        if ( m_nextElement < ( m_elements.size() - 1 ) ) {
            ++m_nextElement;
        }

    }

    //check if next element reached the target
    if ( elementHasReachedTarget() ) {
        m_elements[m_currentElement]->setVisibility( false );
        if ( m_currentElement < ( m_elements.size() - 1 ) ) {
            ++m_currentElement;
        }
    }
}
