#ifndef SONGINFO_H
#define SONGINFO_H

#include "dependencies/rapidxml/rapidxml.hpp"
#include <string>
#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>

using namespace rapidxml;

/*
===============================================================================

    Access to informations about song

===============================================================================
*/

class SongInfo
{
public:

    std::string	 m_artistName;
    std::string	 m_songName;
    std::string	 m_albumName;
    int			 m_albumYear;
    std::string	 m_arrangement;
    float		 m_songLength;
    static float m_tempo;
    std::string	 m_tuning;

    xml_document<> doc;
    xml_node<>*	   root_node;

    SongInfo( std::string fileName );
    static float getTempoMultiplier();
};

#endif // SONGINFO_H
