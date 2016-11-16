#include "Elements.h"

Elements::Elements( Ogre::SceneManager *pSceneMgr, Ogre::SceneNode *pStaffNode ) {
    m_lastPassedElement = 0;
    m_nextElement		= 0;
    m_currentElement	= 0;
    m_pSceneMgr			= pSceneMgr;
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
    pNotationFileParser->createElementsModels( m_elements, m_pSceneMgr, m_staffNode );
}

bool Elements::elementHasReachedTarget() {
    ocx::Note*	NoteObject;
    ocx::Chord* ChordObject;
    float		noteWorldPosition  = 0;
    float		chordWorldPosition = 0;

    if ( m_elements[m_currentElement]->m_type == NOTE ) {
        NoteObject		  = dynamic_cast<ocx::Note *>( m_elements[m_currentElement] );
        noteWorldPosition = m_staffNode->getPosition().z + NoteObject->m_noteNode->getPosition().z;

        if ( noteWorldPosition < 0 ) {
            return false;
        } else if ( noteWorldPosition >= 0 ) {
            return true;
        }
    }

    if ( m_elements[m_currentElement]->m_type == CHORD ) {
        ChordObject		   = dynamic_cast<ocx::Chord *>( m_elements[m_currentElement] );
        chordWorldPosition = m_staffNode->getPosition().z + ChordObject->m_chordNode->getPosition().z;

        if ( chordWorldPosition < 0 ) {
            return false;
        } else if ( chordWorldPosition >= 0 ) {
            return true;
        }
    }
}

bool Elements::elementIsInStringsRange( Element *element ) {
    ocx::Note*	NoteObject;
    ocx::Chord* ChordObject;
    int			range = 280;
    float		noteWorldPosition;
    float		chordWorldPosition;

    if ( element->m_type == NOTE ) {
        NoteObject		  = dynamic_cast<ocx::Note *>( element );
        noteWorldPosition = m_staffNode->getPosition().z + NoteObject->m_noteNode->getPosition().z;

        if ( noteWorldPosition <= 0 && noteWorldPosition > -range ) {
            return true;
        } else { //if (noteWorldPosition > 0)
            return false;
        }
    }

    if ( element->m_type == CHORD ) {
        ChordObject		   = dynamic_cast<ocx::Chord *>( element );
        chordWorldPosition = m_staffNode->getPosition().z + ChordObject->m_chordNode->getPosition().z;

        if ( chordWorldPosition <= 0 && chordWorldPosition > -range ) {
            return true;
        } else { //if (chordWorldPosition > 0)
            return false;
        }
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
