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

/*
===============================================================================

    Loads notation elements informations from file

===============================================================================
*/

using namespace rapidxml;

//Load staff elements and saves them to NotationElements
class NotationFileParser {
public:
    NotationFileParser( std::string fileName );
    ~NotationFileParser() {
        delete m_chordList;
    }

    // converts a relative position to bars to an actual position on staff
    float actualPosition( float position ) { return m_barNumber + ( position / 4 ); }
    void loadElements( std::vector<Element *> &elements );
    void createElementsModels( std::vector<Element*>& elements, Ogre::SceneManager* pSceneMgr, Ogre::SceneNode* pStaffNode );
    void loadChordList( ChordList *chordList );
    void loadTargets();

private:
    int				 m_barNumber;
    std::string		 m_type;
    ChordList*		 m_chordList;
    ChordPattern*	 m_currentChord;
    FingerPositions* m_FingerPositions;
    std::string		 m_fileName;

    xml_document<> m_doc;
    xml_node<>*	   m_rootNode;
};

#endif // NOTATIONFILEPARSER_H
