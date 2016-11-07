#ifndef FINGERPLACEMENT_H
#define FINGERPLACEMENT_H
#include "Chord.h"
//#include "NotationParser.h"

typedef struct
{
    int fingerNumber;
    int string;
    int fret;
} Finger;

/*
===============================================================================

    Basic structure for finger pattern

===============================================================================
*/

class FingerPattern
{
public:
    std::string			m_chordName;
    int					m_beginFret;
    int					m_endFret;
    int					m_size;
    std::vector<Finger> fingers;
    // struny jsou proto, ze jeden prst muze drzet vice strun, zatimco dalsi nemusi byt zapojeny
    // je jednodussi vyznacit, ktere struny drzi jaky prst

    //Na ktere stune je jaky prst
    int m_strings[4];
    //na ktere strune je jaka pozice noty v podobe prazce
    int chordStrings[4];

    int indexFingerFret	 = 0;
    int middleFingerFret = 0;
    int ringFingerFret	 = 0;
    int pinkyFingerFret	 = 0;

    FingerPattern( ChordPattern* pChordDefinition, std::string chordName, int string4, int fingerOnString3, int fingerOnString2, int fingerOnString1 );

    void calculateBeginAndEnd();
};

/*
===============================================================================

    Here are stored all finger patterns

===============================================================================
*/
class FingerPositions
{
public:
    xml_document<>				doc;
    xml_node<>*					root_node;
    std::vector<FingerPattern*> fingerPatterns;

    FingerPositions( xml_node<>* root_node, ChordList* pChordList );
};

#endif // FINGERPLACEMENT_H
