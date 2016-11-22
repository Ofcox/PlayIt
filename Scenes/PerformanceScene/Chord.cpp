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
ocx::Chord::Chord( ChordPattern *chordDefinition, float timePosition, std::string germanName ) {
    m_type		   = CHORD;
    m_timePosition = timePosition;
    m_germanName   = germanName;
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
}
