#ifndef NOTATIONPARSER_H
#define NOTATIONPARSER_H

#include "dependencies/rapidxml/rapidxml.hpp"
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
#include "states/PerformanceScene/SceneSettings.h"

/*
===============================================================================

    Loads notation elements informations from file

===============================================================================
*/

using namespace rapidxml;

//Load staff elements and saves them to NotationElements
class NotationFileParser {
private:
    int				 m_barNumber;
    std::string		 m_type;
    ChordList*		 m_chordList;
    ChordPattern*	 m_currentChord;
    FingerPositions* m_FingerPositions;

public:
    Ogre::SceneManager* m_pSceneMgr;
    Ogre::SceneNode*	m_staffNode;

    xml_document<> doc;
    xml_node<>*	   root_node;

    NotationFileParser( std::string fileName, std::vector<Element*> &elements );
    ~NotationFileParser() {
        delete m_chordList;
    }

    // converts a relative position to bars to an actual position on staff
    float actualPosition( float position ) { return m_barNumber + ( position / 4 ); }
    void loadElements( std::vector<Element*>& elements, Ogre::SceneManager* m_pSceneMgr, Ogre::SceneNode* m_staffNode );
    void loadChordList( ChordList *chordList );
    void loadTargets();

};

#endif // NOTATIONFILEPARSER_H
