#include "FingerPlacement.h"

/*
    FingerPattern definition
    NOTE: needs to rewrite because it contains a redundant code
   ===============================================================================
*/
FingerPattern::FingerPattern( ChordPattern* pChordDefinition, std::string chordName, int fingerOnString4, int fingerOnString3, int fingerOnString2, int fingerOnString1 ) {
    m_chordName  = chordName;
    m_strings[3] = fingerOnString4;
    m_strings[2] = fingerOnString3;
    m_strings[1] = fingerOnString2;
    m_strings[0] = fingerOnString1;

    m_chordStrings[3] = pChordDefinition->m_fretOnString4;
    m_chordStrings[2] = pChordDefinition->m_fretOnString3;
    m_chordStrings[1] = pChordDefinition->m_fretOnString2;
    m_chordStrings[0] = pChordDefinition->m_fretOnString1;

    //loads fingers vector values
    for ( int i = 0; i <= 3; ++i ) {
        if ( m_strings[i] == 1 ) {
            indexFingerFret = m_chordStrings[i];
            fingers.push_back( {1, i, m_chordStrings[i]} );
        }
        if ( m_strings[i] == 2 ) {
            middleFingerFret = m_chordStrings[i];
            fingers.push_back( {2, i, m_chordStrings[i]} );
        }
        if ( m_strings[i] == 3 ) {
            ringFingerFret = m_chordStrings[i];
            fingers.push_back( {3, i, m_chordStrings[i]} );
        }
        if ( m_strings[i] == 4 ) {
            pinkyFingerFret = m_chordStrings[i];
            fingers.push_back( {4, i, m_chordStrings[i]} );
        }
        if ( m_strings[i] == 5 ) {
            fingers.push_back( {5, i, m_chordStrings[i]} );
        }
    }
    calculateBeginAndEnd();

    pChordDefinition->setBeginFret( m_beginFret );
    pChordDefinition->setEndFret( m_endFret );
}

//claculates range of fingers on chord
void FingerPattern::calculateBeginAndEnd() {
    int chordWidthBegin = indexFingerFret;

    if ( indexFingerFret == 0 && ( middleFingerFret != 0 ) )
        chordWidthBegin = middleFingerFret - 1;
    if ( middleFingerFret == 0 && ( ringFingerFret != 0 ) )
        chordWidthBegin = ringFingerFret - 2;
    if ( ringFingerFret == 0 && ( pinkyFingerFret != 0 ) )
        chordWidthBegin = pinkyFingerFret - 3;
    m_beginFret = chordWidthBegin;

    int chordWidthEnd = indexFingerFret;

    if ( middleFingerFret > chordWidthEnd )
        chordWidthEnd = middleFingerFret;
    if ( ringFingerFret > chordWidthEnd )
        chordWidthEnd = pinkyFingerFret;
    if ( chordWidthEnd < ( chordWidthBegin + 3 ) )
        chordWidthEnd = chordWidthBegin + 3;

    m_endFret = chordWidthEnd;
}

/*
    FingerPositions definition
   ===============================================================================
*/
FingerPositions::FingerPositions( xml_node<>* pRootNode, ChordList* pChordList ) {
    xml_node<>* currentNode = pRootNode->first_node( "fingerPatterns" )->first_node( "fingers" );
    while ( currentNode != NULL ) {

        fingerPatterns.push_back( new FingerPattern( pChordList->getChordPatternByName( currentNode->first_attribute( "chord" )->value() ),
                                                     currentNode->first_attribute( "chord" )->value(),
                                                     std::stoi( currentNode->first_attribute( "string4" )->value() ),
                                                     std::stoi( currentNode->first_attribute( "string3" )->value() ),
                                                     std::stoi( currentNode->first_attribute( "string2" )->value() ),
                                                     std::stoi( currentNode->first_attribute( "string1" )->value() ) ) );
        // jump to next element
        currentNode = currentNode->next_sibling();
    }
}
