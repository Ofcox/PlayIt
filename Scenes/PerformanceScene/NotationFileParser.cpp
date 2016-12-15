#include "NotationFileParser.h"

NotationFileParser::NotationFileParser( std::string fileName ) {
    m_fileName = fileName;
}

void NotationFileParser::loadElements( std::vector<Element *> &elements ) {
    std::ifstream	  file( m_fileName );
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string content( buffer.str() );

    // Parse the buffer using the xml file parsing library into doc
    m_doc.parse<0>( &content[0] );
    // Find our root node
    m_rootNode = m_doc.first_node( "song" );

    m_chordList = new ChordList();
    loadChordList( m_chordList );
    m_FingerPositions = new FingerPositions( m_rootNode, m_chordList );

    //loop variable
    xml_node<>* currentBarNode = m_rootNode->first_node( "staff" )->first_node( "bar" );

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
                                                           actualPosition( std::stof( currentElementNode->first_attribute( "position" )->value() ) ) ) ;
                elements.push_back( ChordObject );

                //Kdyz je chord
                //zjistit nazev jeho pocatecni a konecny prazec
                //set begin set end ulozit akord
                //je dalsi akord?
                //ano pokracovat dokud neni zmena
                //ne konec drahy

            } else if ( m_type == "note" ) {
                ocx::Note* NoteObject = new ocx::Note( std::stoi( currentElementNode->first_attribute( "string" )->value() ),
                                                       std::stoi( currentElementNode->first_attribute( "fret" )->value() ),
                                                       actualPosition( std::stof( currentElementNode->first_attribute( "position" )->value() ) ) );
                elements.push_back( NoteObject );

                //Kdyz je note
                //Uloz jeji pozici
                //Pokud j
                //pokud je dalsi element
            }
            //Next element
            currentElementNode = currentElementNode->next_sibling();
        }
        //Next Bar
        currentBarNode = currentBarNode->next_sibling();
    }
    SceneSettings::barCount = m_barNumber;
}

void NotationFileParser::createElementsModels( std::vector<Element*>& elements, Ogre::SceneManager* pSceneMgr, Ogre::SceneNode* pStaffNode ) {
    std::vector<Element*>::iterator itr;

    ocx::Note*	NoteObject;
    ocx::Chord* ChordObject;

    for ( itr = elements.begin(); itr != elements.end(); ++itr ) {

        if ( ( *itr )->m_type == NOTE ) {
            NoteObject = dynamic_cast<ocx::Note*>( *itr );
            NoteObject->create(pStaffNode, pSceneMgr);

        } else if ( ( *itr )->m_type == CHORD ) {
            ChordObject				 = dynamic_cast<ocx::Chord*>( *itr );
            ChordObject->create(pStaffNode, pSceneMgr);
        }
    }
}

void NotationFileParser::loadChordList( ChordList *chordList ) {
    xml_node<>* currentNode = m_rootNode->first_node( "chordList" )->first_node( "chordPattern" );
    while ( currentNode != NULL ) {

        chordList->chordPatterns.push_back( new ChordPattern(  currentNode->first_attribute( "name" )->value(),
                                                               currentNode->first_attribute( "englishName" )->value(),
                                                               currentNode->first_attribute( "germanName" )->value(),
                                                               std::stoi( currentNode->first_attribute( "string4" )->value() ),
                                                               std::stoi( currentNode->first_attribute( "string3" )->value() ),
                                                               std::stoi( currentNode->first_attribute( "string2" )->value() ),
                                                               std::stoi( currentNode->first_attribute( "string1" )->value() ) ) );
        chordList->chordPatterns.back()->m_labelTexture = new LabelMaterial( currentNode->first_attribute( "germanName" )->value() );
        // jump to next element
        currentNode = currentNode->next_sibling();
    }
}
