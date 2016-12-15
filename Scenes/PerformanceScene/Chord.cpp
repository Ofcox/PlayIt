#include "Chord.h"
#include "FingerPlacement.h"

/*
    ChordPatterns definition
===============================================================================
*/
ChordPattern::ChordPattern( std::string name, std::string englishName, std::string germanName, int fretOnString4, int fretOnString3, int fretOnString2, int fretOnString1 ) {
    m_name			= name;
    m_englishName	= englishName;
    m_germanName	= germanName;
    m_fretOnString4 = fretOnString4;
    m_fretOnString3 = fretOnString3;
    m_fretOnString2 = fretOnString2;
    m_fretOnString1 = fretOnString1;

    m_beginFret = 10;
    m_endFret	= 10;
}

ChordPattern *ChordList::getChordPatternByName( std::string chordName ) {
    std::vector<ChordPattern*>::iterator itr;

    for ( itr = chordPatterns.begin(); itr != chordPatterns.end(); ++itr )
    {
        if ( ( *itr )->getName() == chordName ) {
            return *itr;
        }
    }
    //else
    return NULL;
}

/*
    ChordList definition
===============================================================================
*/
ChordList::ChordList() {
}

ChordList::~ChordList() {
    while ( !chordPatterns.empty() )
    {
        delete chordPatterns.back();
        chordPatterns.pop_back();
    }
}

/*
    Chords definition
===============================================================================
*/
ocx::Chord::Chord( ChordPattern *chordDefinition, float timePosition) {
    m_type		   = CHORD;
    m_timePosition = timePosition;
    m_germanName   = chordDefinition->getGermanName();
    m_englishName  = chordDefinition->getEnglishName();
    m_beginFret	   = chordDefinition->getBeginFret();
    m_endFret	   = chordDefinition->getEndFret();

    note4 = new Note( 4, chordDefinition->m_fretOnString4, m_timePosition, chordDefinition->m_fretOnString4 == 0 ? true : false );
    note3 = new Note( 3, chordDefinition->m_fretOnString3, m_timePosition, chordDefinition->m_fretOnString3 == 0 ? true : false );
    note2 = new Note( 2, chordDefinition->m_fretOnString2, m_timePosition, chordDefinition->m_fretOnString2 == 0 ? true : false );
    note1 = new Note( 1, chordDefinition->m_fretOnString1, m_timePosition, chordDefinition->m_fretOnString1 == 0 ? true : false );

    m_strings[0] = chordDefinition->m_fretOnString1;
    m_strings[1] = chordDefinition->m_fretOnString2;
    m_strings[2] = chordDefinition->m_fretOnString3;
    m_strings[3] = chordDefinition->m_fretOnString4;

    m_notes.push_back( note4 );
    m_notes.push_back( note3 );
    m_notes.push_back( note2 );
    m_notes.push_back( note1 );
}

ocx::Chord::~Chord() {

    while ( !m_notes.empty() )
    {
        delete m_notes.back();
        m_notes.pop_back();
    }

    // Destroy labelEntity
    Ogre::SceneNode* labelParent = m_labelEntity->getParentSceneNode();
    labelParent->detachObject(m_labelEntity);
    m_sceneMgr->destroyEntity(m_labelEntity->getName());

    // Destroy frameEntity
    Ogre::SceneNode* frameParent = m_frameEntity->getParentSceneNode();
    frameParent->detachObject(m_frameEntity);
    m_sceneMgr->destroyEntity(m_frameEntity->getName());

    // Destroy labelNode
    m_sceneMgr->destroySceneNode(m_labelNode->getName());

    // Destroy frameNode
    m_sceneMgr->destroySceneNode(m_frameNode->getName());

    // Destroy chordNode
    m_sceneMgr->destroySceneNode(m_chordNode->getName());
}

void ocx::Chord::create(Ogre::SceneNode *staffNode, Ogre::SceneManager *sceneMgr){
    m_sceneMgr = sceneMgr;
    m_chordNode = staffNode->createChildSceneNode();

    for ( int i = 0; i <= 3; ++i ) {
        m_notes[i]->m_sceneMgr = m_sceneMgr;
        m_notes[i]->m_noteEntity = m_sceneMgr->createEntity( "cube.mesh" );

        switch ( m_notes[i]->getString() ) {
        case 1:
            m_notes[i]->m_noteEntity->setMaterialName( "Fret/String1Mat" );
            break;
        case 2:
            m_notes[i]->m_noteEntity->setMaterialName( "Fret/String2Mat" );
            break;
        case 3:
            m_notes[i]->m_noteEntity->setMaterialName( "Fret/String3Mat" );
            break;
        case 4:
            m_notes[i]->m_noteEntity->setMaterialName( "Fret/String4Mat" );
            break;
        }
        m_notes[i]->m_noteNode = m_chordNode->createChildSceneNode();
        m_notes[i]->m_noteNode->attachObject( m_notes[i]->m_noteEntity );
        m_notes[i]->m_noteNode->setPosition(  ( m_notes[i]->getFret() * SceneSettings::fretSpacing ) - ( SceneSettings::fretSpacing / 2 ),
                                              ( m_notes[i]->getString() * SceneSettings::stringSpacing ),
                                              0 );

        if ( !m_notes[i]->getIsNullFret() ) {
            m_chordNode->setPosition( 0, 0, -getTimePosition() * SceneSettings::barScale );
            m_notes[i]->m_noteNode->setScale( 8, 4, 4 );
        } else {
            m_chordNode->setPosition( 0, 0, -getTimePosition() * SceneSettings::barScale );
            m_notes[i]->m_noteNode->setPosition( ( /*7.5+15 + */ ( m_beginFret * SceneSettings::fretSpacing ) + ( SceneSettings::fretSpacing ) /* position from finger guide class */ ),
                                                 ( m_notes[i]->getString() * SceneSettings::stringSpacing ),
                                                 0 );
            m_notes[i]->m_noteNode->setScale( SceneSettings::fretSpacing * 4, 1, 1 );
        }
    }

    m_frameEntity = m_sceneMgr->createEntity( "frame.mesh" );
    m_frameNode   = m_chordNode->createChildSceneNode();
    m_frameNode->attachObject( m_frameEntity );
    m_frameNode->setScale( 20,20,0 );
    m_frameNode->setPosition( ( m_beginFret * SceneSettings::fretSpacing ) - ( SceneSettings::fretSpacing ), 0, 0 );

    m_frameEntity->setMaterialName( "Frame/ChordMat" );

    m_labelEntity = m_sceneMgr->createEntity( "plane.mesh" );
    m_labelNode   = m_chordNode->createChildSceneNode();
    m_labelNode->attachObject( m_labelEntity );
    m_labelNode->setScale( 10,10,0 );
    m_labelNode->setPosition( ( m_beginFret * SceneSettings::fretSpacing ) -20, SceneSettings::stringSpacing * 5, 0 );

    m_labelEntity->setMaterialName( m_germanName.c_str() );
}
