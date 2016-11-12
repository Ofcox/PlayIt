#ifndef CHORD_H
#define CHORD_H

#include "Note.h"

#include "../../dependencies/rapidxml/rapidxml.hpp"

using namespace rapidxml;

namespace ocx {
    class Chord;
}

class FingerPattern;

/*
===============================================================================

    Basic structure for chord patterns

===============================================================================
*/

class ChordPattern
{
private:
    int			m_beginFret;
    int			m_endFret;
    std::string m_name;
    std::string m_englishName;
    std::string m_germanName;

public:
    int m_fretOnString4;
    int m_fretOnString3;
    int m_fretOnString2;
    int m_fretOnString1;

    ChordPattern( std::string name, std::string englishName, std::string germanName, int fretOnString4, int fretOnString3, int fretOnString2, int fretOnString1 );
    ~ChordPattern() {}

    void setBeginFret( int& beginFret ) { m_beginFret = beginFret; }
    void setEndFret( int& endFret ) { m_endFret = endFret; }
    int getBeginFret() { return m_beginFret; }
    int getEndFret() { return m_endFret; }

    std::string getName() {return m_name; }
    std::string getEnglishName() {return m_englishName; }
    std::string getGermanName() {return m_germanName; }

};

/*
===============================================================================

    Here are stored all needed chords and their finger placements

===============================================================================
*/
class ChordList {
public:
    std::vector<ChordPattern*>	chordPatterns;
    std::vector<FingerPattern*> fingerPatterns;

    ChordList();
    ~ChordList();

    // Returns chord pattern by name
    ChordPattern* getChordPatternByName( std::string chordName );
};


/*
===============================================================================

    Basic structure for chords

===============================================================================
*/
class ocx::Chord : public Element
{
private:
    std::string m_name;
    std::string m_germanName;
    int			m_beginFret;
    int			m_endFret;

public:
    std::vector<ocx::Note*>	   m_notes;
    std::vector<Ogre::Entity*> m_chordEntity;
    Ogre::SceneNode*		   m_chordNode;
    //?? možná FingerPattern?

    ocx::Note* note4;
    ocx::Note* note3;
    ocx::Note* note2;
    ocx::Note* note1;

    ocx::Chord( ChordPattern* chordDefinition, float timePosition, std::string germanName );
    virtual ~Chord();

    // Sets visibility of chords
    virtual void setVisibility( bool isVisible ) {
        m_notes[0]->m_noteNode->setVisible( isVisible );
        m_notes[1]->m_noteNode->setVisible( isVisible );
        m_notes[2]->m_noteNode->setVisible( isVisible );
        m_notes[3]->m_noteNode->setVisible( isVisible );
    }

    std::string getName() {return m_name; }
    std::string getGermanName() {return m_germanName; }
    int getBeginFret() {return m_beginFret; }
    int getEngFret() {return m_endFret; }
};

#endif // CHORD_H
