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
    Stores info about which string is pressed by which figner

   ===============================================================================
 */

class FingerPattern
{
private:
    std::string m_chordName;
    int         m_beginFret;
    int         m_endFret;
    int         m_width;

    int indexFingerFret  = 0;
    int middleFingerFret = 0;
    int ringFingerFret   = 0;
    int pinkyFingerFret  = 0;

    //Which string is pressed by which figner
    int m_strings[4];

    //Which fret is pressed on which string
    int m_chordStrings[4];

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
    TODO: refactoring after implementation of Labels and Targets

   ===============================================================================
 */
class FingerPositions
{
public:
    std::vector<FingerPattern*> fingerPatterns;

    FingerPositions( xml_node<>* pRootNode, ChordList* pChordList );
};

#endif // FINGERPLACEMENT_H
