#include "NotationFileParser.h"

NotationFileParser::NotationFileParser( std::string fileName, std::vector<Element *> &elements ) {
    /// Alternative way to read the xml file into a vector
//    ifstream notationFile("notation.xml");
//    vector<char> buffer((istreambuf_iterator<char>(notationFile)), istreambuf_iterator<char>());
//    buffer.push_back('\0');
//    notationFile.close();

    std::ifstream	  file( fileName );
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string content( buffer.str() );

    // Parse the buffer using the xml file parsing library into doc
    doc.parse<0>( &content[0] );

    // Find our root node
    root_node = doc.first_node( "song" );

    m_chordList = new ChordList();
    loadChordList( m_chordList );
    m_FingerPositions = new FingerPositions( root_node, m_chordList );

    //loop variable
    xml_node<>* currentBarNode = root_node->first_node( "staff" )->first_node( "bar" );

    //loop through all bars
    while ( currentBarNode != NULL ) {

        //define loop variables
        m_barNumber = std::stoi( currentBarNode->first_attribute( "number" )->value() );
        xml_node<>* currentElementNode = currentBarNode->first_node( "element" );

        //Loop through elements in actual bar
        while ( currentElementNode != NULL ) {
            m_type = currentElementNode->first_attribute( "type" )->value();
            std::cout << currentElementNode->first_attribute( "name" )->value() << std::endl;

            if ( m_type == "chord" ) {
                m_currentChord = m_chordList->getChordPatternByName( currentElementNode->first_attribute( "name" )->value() );
                ocx::Chord* ChordObject = new ocx::Chord(  m_currentChord,
                                                           actualPosition( std::stof( currentElementNode->first_attribute( "position" )->value() ) ),
                                                           m_currentChord->m_germanName ) ;

                elements.push_back( ChordObject );
            } else if ( m_type == "note" ) {
                ocx::Note* NoteObject = new ocx::Note( std::stoi( currentElementNode->first_attribute( "string" )->value() ),
                                                       std::stoi( currentElementNode->first_attribute( "fret" )->value() ),
                                                       actualPosition( std::stof( currentElementNode->first_attribute( "position" )->value() ) ) );
                elements.push_back( NoteObject );
            }
            //Next element
            currentElementNode = currentElementNode->next_sibling();
        }
        //Next Bar
        currentBarNode = currentBarNode->next_sibling();
    }
}

/*
    REMOVE
*/
void NotationFileParser::loadElements( std::vector<Element*>& elements, Ogre::SceneManager* m_pSceneMgr, Ogre::SceneNode* m_staffNode ) {
    std::vector<Element*>::iterator itr;

    ocx::Note*	NoteObject;
    ocx::Chord* ChordObject;

    for ( itr = elements.begin(); itr != elements.end(); ++itr ) {

        if ( ( *itr )->m_type == NOTE ) {
            NoteObject				 = dynamic_cast<ocx::Note *>( *itr );
            NoteObject->m_noteEntity = m_pSceneMgr->createEntity( "cube.mesh" );
            switch ( NoteObject->m_string ) {
            case 1:
                NoteObject->m_noteEntity->setMaterialName( "Fret/String1Mat" );
                break;
            case 2:
                NoteObject->m_noteEntity->setMaterialName( "Fret/String2Mat" );
                break;
            case 3:
                NoteObject->m_noteEntity->setMaterialName( "Fret/String3Mat" );
                break;
            case 4:
                NoteObject->m_noteEntity->setMaterialName( "Fret/String4Mat" );
                break;
            }

            NoteObject->m_noteNode = m_staffNode->createChildSceneNode();
            NoteObject->m_noteNode->attachObject( NoteObject->m_noteEntity );
            NoteObject->m_noteNode->setPosition( ( NoteObject->m_fret * SceneSettings::fretSpacing ) - ( SceneSettings::fretSpacing / 2 ),
                                                 ( NoteObject->m_string * SceneSettings::stringSpacing ),
                                                 -NoteObject->m_timePosition * SceneSettings::barScale );
            NoteObject->m_noteNode->setScale( 8, 4, 4 );

        } else if ( ( *itr )->m_type == CHORD ) {
            ChordObject = dynamic_cast<ocx::Chord *>( *itr );
            for ( int i = 0; i <= 3; ++i ) {
                ChordObject->m_notes[i]->m_noteEntity = m_pSceneMgr->createEntity( "cube.mesh" );

                switch ( ChordObject->m_notes[i]->m_string ) {
                case 1:
                    ChordObject->m_notes[i]->m_noteEntity->setMaterialName( "Fret/String1Mat" );
                    break;
                case 2:
                    ChordObject->m_notes[i]->m_noteEntity->setMaterialName( "Fret/String2Mat" );
                    break;
                case 3:
                    ChordObject->m_notes[i]->m_noteEntity->setMaterialName( "Fret/String3Mat" );
                    break;
                case 4:
                    ChordObject->m_notes[i]->m_noteEntity->setMaterialName( "Fret/String4Mat" );
                    break;
                }

                ChordObject->m_chordNode			= m_staffNode->createChildSceneNode();
                ChordObject->m_notes[i]->m_noteNode = ChordObject->m_chordNode->createChildSceneNode();
                ChordObject->m_notes[i]->m_noteNode->attachObject( ChordObject->m_notes[i]->m_noteEntity );
                ChordObject->m_notes[i]->m_noteNode->setPosition(  ( ChordObject->m_notes[i]->m_fret * SceneSettings::fretSpacing ) - ( SceneSettings::fretSpacing / 2 ),
                                                                   ( ChordObject->m_notes[i]->m_string * SceneSettings::stringSpacing ),
                                                                   0 );

                if ( !ChordObject->m_notes[i]->m_isNullFret ) {
                    ChordObject->m_chordNode->setPosition( 0, 0, -ChordObject->m_timePosition * SceneSettings::barScale );
                    ChordObject->m_notes[i]->m_noteNode->setScale( 8, 4, 4 );
                } else {
                    ChordObject->m_chordNode->setPosition( 0, 0, -ChordObject->m_timePosition * SceneSettings::barScale );
                    ChordObject->m_notes[i]->m_noteNode->setPosition( ( /*7.5+15 + */ ( ChordObject->m_beginFret * SceneSettings::fretSpacing ) + ( SceneSettings::fretSpacing ) /* position from finger guide class */ ),
                                                                      ( ChordObject->m_notes[i]->m_string * SceneSettings::stringSpacing ),
                                                                      0 );
                    ChordObject->m_notes[i]->m_noteNode->setScale( SceneSettings::fretSpacing * 4, 1, 1 );
                }
            }
            /* Chord Frame */

            ////            ChordObject->m_chordEntity.push_back(m_pSceneMgr->createEntity("cube.mesh"));
            ////            ChordObject->m_chordEntity.back()->setMaterialName("Fret/StringMat");
            ////            ChordObject->m_chordNode = m_staffNode->createChildSceneNode();
            ////            ChordObject->m_chordNode = ChordObject->m_chordNode->createChildSceneNode();
            ////            ChordObject->m_chordNode->attachObject(ChordObject->m_chordEntity.back());
        }
    }
}

void NotationFileParser::loadChordList( ChordList *chordList ) {
    xml_node<>* currentNode = root_node->first_node( "chordList" )->first_node( "chordPattern" );
    while ( currentNode != NULL ) {

        chordList->chordPatterns.push_back( new ChordPattern(  currentNode->first_attribute( "name" )->value(),
                                                               currentNode->first_attribute( "englishName" )->value(),
                                                               currentNode->first_attribute( "germanName" )->value(),
                                                               std::stoi( currentNode->first_attribute( "string4" )->value() ),
                                                               std::stoi( currentNode->first_attribute( "string3" )->value() ),
                                                               std::stoi( currentNode->first_attribute( "string2" )->value() ),
                                                               std::stoi( currentNode->first_attribute( "string1" )->value() ) ) );
        // jump to next element
        currentNode = currentNode->next_sibling();
    }
}
