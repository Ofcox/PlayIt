#ifndef NOTATIONFILE_H
#define NOTATIONFILE_H

#include "dependencies/rapidxml/rapidxml.hpp"
#include <string>
#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Chord.h"

/*
===============================================================================

    Loads notation elements informations from file to buffer

===============================================================================
*/

using namespace rapidxml;

class NotationFile
{
public:
    xml_document<> m_notationFile;
    xml_node<>*	   m_rootNode;
    std::string	   m_type;
    int			   m_barNumber;
    ChordList*	   m_chordList;

    NotationFile();
    void loadNotationFile( std::string fileName );
    void loadChordList( ChordList *chordList );
    void loadFingerPositions( ChordList *chordList, FingerPattern* fingerPatterns );
    void loadElements( std::vector<Element *> &elements );
    void createElements( std::vector<Element *> &elements, Ogre::SceneManager *sceneMgr, Ogre::SceneNode *staffNode );
};

#endif // NOTATIONFILE_H
