#include "NotationFileParser.h"

NotationFileParser::NotationFileParser( std::string fileName ) {
    m_fileName = fileName;
    m_barNumber = -1;
}

void NotationFileParser::loadElements( std::vector<Element *> &elements, Ogre::SceneManager* pSceneMgr, Ogre::SceneNode* pStaffNode ) {
    std::ifstream	  file( m_fileName );
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string content( buffer.str() );

    bool isNoteLastElement = true;
//    int previousBar;
    std::string lastChordName = "";
//    bool isNextChordFrame = false;
    bool isFirstElementOfBar = true;

    // Parse the buffer using the xml file parsing library into doc
    m_document.parse<0>( &content[0] );
    // Find our root node
    m_rootNode = m_document.first_node( "song" );

    m_chordList = new ChordTemplates();
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
                ocx::Chord* ChordObject = new ocx::Chord(  m_currentChord, m_barNumber,
                                                           relativeToAbsolutePosition( std::stof( currentElementNode->first_attribute( "position" )->value() ) ),
                                                           std::stof( currentElementNode->first_attribute( "value" )->value() ));
                elements.push_back( ChordObject );

                //pokud se jmeno predesleho neshoduje se soucasnym
                if (isFirstElementOfBar || (ChordObject->getName() != lastChordName) || isNoteLastElement){
                    ChordObject->createEntire(pStaffNode, pSceneMgr);
                } else {
                    ChordObject->createFrame(pStaffNode, pSceneMgr);
                }

                lastChordName = ChordObject->getName();
                isNoteLastElement = false;

            } else if ( m_type == "note" ) {
                ocx::Note* NoteObject = new ocx::Note( std::stoi( currentElementNode->first_attribute( "string" )->value() ),
                                                       std::stoi( currentElementNode->first_attribute( "fret" )->value() ),
                                                       m_barNumber,
                                                       relativeToAbsolutePosition( std::stof( currentElementNode->first_attribute( "position" )->value() ) ),
                                                       std::stof( currentElementNode->first_attribute( "value" )->value() ));
                elements.push_back( NoteObject );
                NoteObject->create(pStaffNode, pSceneMgr);
                isNoteLastElement = true;
            }
            //Next element
            currentElementNode = currentElementNode->next_sibling();
            isFirstElementOfBar = false;
        }
        //Next Bar
        currentBarNode = currentBarNode->next_sibling();
        isFirstElementOfBar = true;
    }
    SceneSettings::barCount = m_barNumber;
}

void NotationFileParser::loadChordList( ChordTemplates *chordList ) {
    xml_node<>* currentNode = m_rootNode->first_node( "chordList" )->first_node( "chordTemplate" );
    while ( currentNode != NULL ) {

        chordList->chordTemplate.push_back( new ChordTemplate( currentNode->first_attribute( "name" )->value(),
                                                               currentNode->first_attribute( "englishName" )->value(),
                                                               currentNode->first_attribute( "germanName" )->value(),
                                                               std::stoi( currentNode->first_attribute( "string4" )->value() ),
                                                               std::stoi( currentNode->first_attribute( "string3" )->value() ),
                                                               std::stoi( currentNode->first_attribute( "string2" )->value() ),
                                                               std::stoi( currentNode->first_attribute( "string1" )->value() ) ) );
        chordList->chordTemplate.back()->m_labelTexture = new LabelMaterial( currentNode->first_attribute( "germanName" )->value() );
        // jump to next element
        currentNode = currentNode->next_sibling();
    }
}
