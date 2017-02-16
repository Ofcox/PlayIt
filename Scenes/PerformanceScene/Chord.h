#ifndef CHORD_H
#define CHORD_H

#include "Note.h"

#include "../../dependencies/rapidxml/rapidxml.hpp"
#include <OgreMeshManager.h>
#include "LabelMaterial.h"

using namespace rapidxml;

namespace ocx {
    class Chord;
}

class FingerPattern;

/**
 * @brief Basic class for chord templates
 * TODO: Change all strings to a single array
 */
class ChordTemplate {
private:
    int         m_beginFret; /**< Begin of the chord defined by left fret */
    int         m_endFret; /**< End of the chord defined by right fret */
    std::string m_name; /**< Identification name of the chord template */
    std::string m_englishName; /**< English name used interntionally */
    std::string m_germanName; /**< German name used mostly in European countries */

public:
    int m_fretOnString4; /**< which fret is held on string 4 */
    int m_fretOnString3; /**< which fret is held on string 3 */
    int m_fretOnString2; /**< which fret is held on string 2 */
    int m_fretOnString1; /**< which fret is held on string 1 */

    LabelMaterial* m_labelTexture; /**< Label texture of the chord */

    /**
     * @brief This constructor requires all informations at initialization
     *
     * @param name
     * @param englishName
     * @param germanName
     * @param fretOnString4
     * @param fretOnString3
     * @param fretOnString2
     * @param fretOnString1
     */
    ChordTemplate( std::string name, std::string englishName, std::string germanName, int fretOnString4, int fretOnString3, int fretOnString2, int fretOnString1 );

    /**
     * @brief
     */
    ~ChordTemplate() { }

    /**
     * @brief Sets begin of the chord defined by left fret
     *
     * @param beginFret
     */
    void setBeginFret( int& beginFret ) { m_beginFret = beginFret; }

    /**
     * @brief Sets end of the chord defined by right fret
     *
     * @param endFret
     */
    void setEndFret( int& endFret ) { m_endFret = endFret; }

    /**
     * @brief Returns begin of the chord defined by left fret
     *
     * @return int
     */
    int getBeginFret() { return m_beginFret; }

    /**
     * @brief Sets end of the chord defined by right fret
     *
     * @return int
     */
    int getEndFret() { return m_endFret; }

    /**
     * @brief Returns name of the chord template
     *
     * @return std::string
     */
    std::string getName() { return m_name; }

    /**
     * @brief Returns english name of the chord template
     *
     * @return std::string
     */
    std::string getEnglishName() { return m_englishName; }

    /**
     * @brief Returns german name of the chord template
     *
     * @return std::string
     */
    std::string getGermanName() { return m_germanName; }
};

/**
 * @brief Here are stored all needed chords
 */
class ChordTemplates {
public:
    std::vector<ChordTemplate*> chordTemplate;

    ChordTemplates();

    ~ChordTemplates();

    /**
     * @brief Returns chord pattern by name
     *
     * @param chordName
     * @return ChordTemplate
     */
    ChordTemplate* getChordPatternByName( std::string chordName );
};

/**
 * @brief Basic class for chords
 */
class ocx::Chord : public Element {
public:

    /**
     * @brief
     */
    ocx::Chord(ChordTemplate* chordDefinition, int bar, float timePosition, float value);

    /**
     * @brief
     */
    virtual ~Chord();

    /**
     * @brief Sets visibility of the chord
     *
     * @param isVisible
     */
    virtual void setVisibility( bool isVisible ) { m_chordNode->setVisible( isVisible ); }

    /**
     * @brief Returns chord node
     *
     * @return Ogre::SceneNode
     */
    virtual Ogre::SceneNode* getNode() { return m_chordNode; }

    /**
     * @brief Returns german name
     *
     * @return std::string
     */
    std::string getGermanName() { return m_germanName; }

    /**
     * @brief Returns english name
     *
     * @return std::string
     */
    std::string getEnglishName() { return m_englishName; }

    /**
     * @brief Returns begin of the chord defined by left fret
     *
     * @return int
     */
    int getBeginFret() { return m_beginFret; }

    /**
     * @brief Returns end of the chord defined by right fret
     *
     * @return int
     */
    int getEndFret() { return m_endFret; }

    /**
     * @brief This creates objects and models for the scene using dependency injection - lazy init
     *
     * @param staffNode
     * @param sceneMgr
     */
    void createEntire( Ogre::SceneNode* staffNode, Ogre::SceneManager* sceneMgr );
    void createFrame( Ogre::SceneNode* staffNode, Ogre::SceneManager* sceneMgr );

private:
    Ogre::SceneNode*    m_chordNode; /**< Ogre node for chord */
    Ogre::SceneManager* m_sceneMgr; /**< Ogre scenene manager */

    std::vector<ocx::Note*> m_notes; /**< Vector of notes from chord consists */

    Ogre::Entity*    m_labelEntity; /**< Ogre entity of label */
    Ogre::SceneNode* m_labelNode; /**< Ogre scene node */

    Ogre::Entity*    m_frameEntity; /**< Ogre entity of frame */
    Ogre::SceneNode* m_frameNode; /**< Ogre scene node */

    std::string m_germanName; /**< German name */
    std::string m_englishName; /**< english name */
    int         m_beginFret; /**< Begin of the chord defined by left fret */
    int         m_endFret; /**< End of the chord defined by right fret */

    ocx::Note* note4; /**< Note object on string 4 */
    ocx::Note* note3; /**< Note object on string 3 */
    ocx::Note* note2; /**< Note object on string 2 */
    ocx::Note* note1; /**< Note object on string 1 */
};

#endif // CHORD_H
