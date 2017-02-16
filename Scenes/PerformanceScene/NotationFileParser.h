#ifndef NOTATIONPARSER_H
#define NOTATIONPARSER_H

#include "../../dependencies/rapidxml/rapidxml.hpp"
#include <string>
#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <OgreSceneManager.h>
#include <OgreEntity.h>

#include "FingerPlacement.h"
#include "Chord.h"
#include "SceneSettings.h"

#include "LabelMaterial.h"

using namespace rapidxml;

/**
 * @brief Loads all elements from the file and saves them to NotationElements
 */
class NotationFileParser {
public:
    /**
     * @brief
     *
     * @param fileName
     */
    NotationFileParser( std::string fileName );

    /**
     * @brief
     */
    ~NotationFileParser() {
        delete m_chordList;
    }

    /**
     * @brief Converts a relative position to bar to an actual position on staff
     *
     * @param Relative position
     * @return Absolute position
     */
    float relativeToAbsolutePosition( float position ) { return m_barNumber + ( position / 4 ); }

    /**
     * @brief Loads elements to the vector
     *
     * @param vector of elements
     */
    void loadElements( std::vector<Element *> &elements, Ogre::SceneManager* pSceneMgr, Ogre::SceneNode* pStaffNode );

    /**
     * @brief Loads list of chords templates that are occuring in song
     *
     * @param chordList
     */
    void loadChordList( ChordTemplates *chordList );

private:
    int				 m_barNumber; /**< Currently processed bar */
    std::string		 m_type; /**< Currently processed type */
    ChordTemplates*	 m_chordList; /**< List of chords */
    ChordTemplate*	 m_currentChord; /**< Current chord template */
    FingerPositions* m_FingerPositions; /**< List of all finger positions */
    std::string		 m_fileName; /**< Name of notation file */

    xml_document<> m_document; /**< Whole notation file is loaded here */
    xml_node<>*	   m_rootNode; /**< Currently processed node */
};

#endif // NOTATIONFILEPARSER_H
