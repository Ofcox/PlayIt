#include "Staff.h"

Staff::Staff( Ogre::SceneManager *pSceneMgr, Ogre::SceneNode *pStaffNode ) {
    m_pSceneMgr			= pSceneMgr;
    m_staffNode			= pStaffNode;
    m_lastPassedElement = 0;
    m_nextElement		= 0;
    m_currentElement	= 0;

    m_pNotationFileParser = new NotationFileParser( "notation.xml", elements );
}

Staff::~Staff() {
    m_staffNode->removeAndDestroyAllChildren();
    delete m_pNotationFileParser;

    while ( !elements.empty() ) {
        delete elements.back();
        elements.pop_back();
    }
}

void Staff::loadElements() {
    m_pNotationFileParser->loadElements( elements, m_pSceneMgr, m_staffNode );
}

bool Staff::elementHasReachedTarget() {
    ocx::Note*	NoteObject;
    ocx::Chord* ChordObject;
    float		noteWorldPosition;
    float		chordWorldPosition;

    if ( elements[m_currentElement]->m_type == NOTE ) {
        NoteObject		  = dynamic_cast<ocx::Note *>( elements[m_currentElement] );
        noteWorldPosition = m_staffNode->getPosition().z + NoteObject->m_noteNode->getPosition().z;

        if ( noteWorldPosition < 0 ) {
            return false;
        } else if ( noteWorldPosition >= 0 ) {
            return true;
        }
    }

    if ( elements[m_currentElement]->m_type == CHORD ) {
        ChordObject		   = dynamic_cast<ocx::Chord *>( elements[m_currentElement] );
        chordWorldPosition = m_staffNode->getPosition().z + ChordObject->m_chordNode->getPosition().z;

        if ( chordWorldPosition < 0 ) {
            return false;
        } else if ( chordWorldPosition >= 0 ) {
            return true;
        }
    }
}

bool Staff::elementIsInStringsRange( Element* element ) {
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

void Staff::update() {
    Element* element;

    //Kontrola, jestli je dalsi element v dosahu
    if ( elements[m_nextElement] != element ) {
        element = elements[m_nextElement];
    }

    if ( elementIsInStringsRange( element ) ) {

        if ( m_nextElement < ( elements.size() - 1 ) ) {
            ++m_nextElement;
        }

    }

    //check if next element reached the target
    if ( elementHasReachedTarget() ) {
        elements[m_currentElement]->setVisibility( false );
        if ( m_currentElement < ( elements.size() - 1 ) ) {
            ++m_currentElement;
        }
    }
}

void Staff::load() {
    // Loads all chords and notes
    //m_pNotationFileParser->loadElements( elements, m_pSceneMgr, m_staffNode );
}
