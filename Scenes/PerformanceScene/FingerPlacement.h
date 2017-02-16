#ifndef FINGERPLACEMENT_H
#define FINGERPLACEMENT_H
#include "Chord.h"

/**
 * @brief Typedef for Finger struct
 */
typedef struct {
    int fingerNumber; /**< Represents particuar finger on hand by number [1 = index finger, 2 = middle finger, 3 = ring finger, 4 = pinky finger, 5 = thumb] */
    int string; /**< Which string is held by finger */
    int fret; /**< Which fret is held by finger */
/**
 * @brief Struct representing individual fingers
 */
} Finger;

/**
 * @brief Basic structure for finger pattern.
 * @brief Stores info about which string is pressed by which figner and creates informations about chord frames
 */
class FingerPattern {
public:

    /**
     * @brief Contructor sets begin and end fret of ChordDefinition
     *
     * @param pChordDefinition
     * @param chordName
     * @param fingerOnString4
     * @param fingerOnString3
     * @param fingerOnString2
     * @param fingerOnString1
     */
    FingerPattern( ChordTemplate* pChordDefinition, std::string chordName, int fingerOnString4, int fingerOnString3, int fingerOnString2, int fingerOnString1 );

private:
    std::vector<Finger> fingers; /**< Container of all fingers holding current chord */

    std::string m_chordName; /**< Identification name of chord */
    int         m_beginFret; /**< Generated begin fret of chord frame*/
    int         m_endFret; /**< Generated end fret of chord frame */
    int         m_width; /**< Calculated width of the chord frame */

    int indexFingerFret  = 0; /**< Which fret is held by index finger */
    int middleFingerFret = 0; /**< Which fret is held by middle finger */
    int ringFingerFret   = 0; /**< Which fret is held by ring finger */
    int pinkyFingerFret  = 0; /**< Which fret is held by pinky finger */

    int m_strings[4]; /**< Which string is pressed by which figner */

    int m_chordStrings[4]; /**< Which fret is pressed on which string */

    /**
     * @brief Calculate begin and end of the chord frame
     */
    void calculateBeginAndEnd();
};

/**
 * @brief Here are stored all finger patterns
 * TODO: refactoring after implementation of Labels and Targets
 */
class FingerPositions {
public:
    std::vector<FingerPattern*> fingerPatterns;

    /**
     * @brief Loads finger patterns from notation file
     *
     * @param pRootNode
     * @param pChordList
     */
    FingerPositions( xml_node<>* pRootNode, ChordTemplates* pChordList );
};

#endif // FINGERPLACEMENT_H
