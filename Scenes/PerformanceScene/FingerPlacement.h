#ifndef FINGERPLACEMENT_H
#define FINGERPLACEMENT_H
#include "Chord.h"

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
private:
    std::string m_chordName;
    int			m_beginFret;
    int			m_endFret;
    int			m_width;

    int indexFingerFret	 = 0;
    int middleFingerFret = 0;
    int ringFingerFret	 = 0;
    int pinkyFingerFret	 = 0;

    // struny jsou proto, ze jeden prst muze drzet vice strun, zatimco dalsi nemusi byt zapojeny
    // je jednodussi vyznacit, ktere struny drzi jaky prst

    //Na ktere stune je jaky prst
    int m_strings[4];

    //na ktere strune je jaka pozice noty v podobe prazce
    int chordStrings[4];

    void calculateBeginAndEnd();

public:

    // Container of all fingers holding current chord
    std::vector<Finger> fingers;

    // Contructor sets begin and end fret of ChordDefinition
    FingerPattern( ChordPattern* pChordDefinition, std::string chordName, int fingerOnString4, int fingerOnString3, int fingerOnString2, int fingerOnString1 );

};

/*
===============================================================================

    Here are stored all finger patterns
    TODO refactoring after implementation of Labels and Targets

===============================================================================
*/
class FingerPositions
{
public:
    std::vector<FingerPattern*> fingerPatterns;

    FingerPositions( xml_node<>* pRootNode, ChordList* pChordList );
};

#endif // FINGERPLACEMENT_H
