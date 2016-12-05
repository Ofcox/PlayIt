#ifndef CHORD_H
#define CHORD_H

#include "Note.h"

#include "../../dependencies/rapidxml/rapidxml.hpp"
#include <OgreMeshManager.h>
#include "LabelTexture.h"

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
    int         m_beginFret;
    int         m_endFret;
    std::string m_name;
    std::string m_englishName;
    std::string m_germanName;

public:
    int m_fretOnString4;
    int m_fretOnString3;
    int m_fretOnString2;
    int m_fretOnString1;

    ChordPattern( std::string name, std::string englishName, std::string germanName, int fretOnString4, int fretOnString3, int fretOnString2, int fretOnString1 );
    ~ChordPattern() {
    }

    void setBeginFret( int& beginFret ) {
        m_beginFret = beginFret;
    }
    void setEndFret( int& endFret ) {
        m_endFret = endFret;
    }
    int getBeginFret() {
        return m_beginFret;
    }
    int getEndFret() {
        return m_endFret;
    }

    std::string getName() {
        return m_name;
    }
    std::string getEnglishName() {
        return m_englishName;
    }
    std::string getGermanName() {
        return m_germanName;
    }

};

/*
   ===============================================================================

    Here are stored all needed chords

   ===============================================================================
 */
class ChordList {
public:
    std::vector<ChordPattern*> chordPatterns;

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
    std::string m_germanName;
    std::string m_englishName;
    int         m_beginFret;
    int         m_endFret;

public:
    std::vector<ocx::Note*> m_notes;
    Ogre::SceneNode*        m_chordNode;
    LabelTexture*           m_labelTexture;

    Ogre::Entity*    m_labelEntity;
    Ogre::SceneNode* m_labelNode;

    Ogre::Entity*    m_frameEntity;
    Ogre::SceneNode* m_frameNode;

    ocx::Note* note4;
    ocx::Note* note3;
    ocx::Note* note2;
    ocx::Note* note1;

    ocx::Chord(ChordPattern* chordDefinition, float timePosition);
    virtual ~Chord();

    // Sets visibility of chords
    virtual void setVisibility( bool isVisible ) {
        m_chordNode->setVisible( isVisible );
    }

    virtual Ogre::SceneNode* getNode() {
        return m_chordNode;
    }
    std::string getGermanName() {
        return m_germanName;
    }
    std::string getEnglishName() {
        return m_englishName;
    }
    int getBeginFret() {
        return m_beginFret;
    }
    int getEngFret() {
        return m_endFret;
    }
};

#endif // CHORD_H
