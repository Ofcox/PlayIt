#include "SongInfo.h"
#include <string>

float SongInfo::m_tempo = 0;

SongInfo::SongInfo( std::string fileName ) {
    std::ifstream	  file( fileName );
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string content( buffer.str() );

    // Parse the buffer using the xml file parsing library into doc
    doc.parse<0>( &content[0] );

    // Find our root node
    root_node = doc.first_node( "song" );

    m_artistName  = root_node->first_node( "artistName" )->value();
    m_songName	  = root_node->first_node( "songName" )->value();
    m_albumName	  = root_node->first_node( "albumName" )->value();
    m_albumYear	  = std::stoi( root_node->first_node( "albumYear" )->value() );
    m_arrangement = root_node->first_node( "arrangement" )->value();
    m_songLength  = std::stof( root_node->first_node( "songLength" )->value() );
    m_tempo		  = std::stof( root_node->first_node( "tempo" )->value() );
    m_tuning	  = root_node->first_node( "tuning" )->value();

}

float SongInfo::getTempoMultiplier() {
    return 60 / m_tempo;
}
