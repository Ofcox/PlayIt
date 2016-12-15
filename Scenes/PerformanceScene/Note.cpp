#include "Note.h"

ocx::Note::Note( int string, int fret, float timePosition ) {
    m_type					  = NOTE;
    m_isNullFret			  = false;
    m_name					  = "";
    m_string				  = string;
    m_fret					  = fret;
    m_strings[( string - 1 )] = fret;
    m_timePosition			  = timePosition;
}

ocx::Note::Note( int string, int fret, float timePosition, bool isNullFret ) {
    m_type					  = NOTE;
    m_isNullFret			  = isNullFret;
    m_name					  = "";
    m_string				  = string;
    m_fret					  = fret;
    m_strings[( string - 1 )] = fret;
    m_timePosition			  = timePosition;
}

ocx::Note::~Note() {
    // Destroy entity
    Ogre::SceneNode* parent = m_noteEntity->getParentSceneNode();
    parent->detachObject(m_noteEntity);
    m_sceneMgr->destroyEntity(m_noteEntity->getName());

    // Destroy node
    m_sceneMgr->destroySceneNode(m_noteNode->getName());
}

void ocx::Note::create(Ogre::SceneNode *staffNode, Ogre::SceneManager *sceneMgr) {
    m_sceneMgr = sceneMgr;
    m_noteEntity = sceneMgr->createEntity( "cube.mesh" );
    switch ( m_string ) {
    case 1:
        m_noteEntity->setMaterialName( "Fret/String1Mat" );
        break;
    case 2:
        m_noteEntity->setMaterialName( "Fret/String2Mat" );
        break;
    case 3:
        m_noteEntity->setMaterialName( "Fret/String3Mat" );
        break;
    case 4:
        m_noteEntity->setMaterialName( "Fret/String4Mat" );
        break;
    }

    m_noteNode = staffNode->createChildSceneNode();
    m_noteNode->attachObject( m_noteEntity );
    m_noteNode->setPosition( ( m_fret * SceneSettings::fretSpacing ) - ( SceneSettings::fretSpacing / 2 ),
                             ( m_string * SceneSettings::stringSpacing ),
                             -m_timePosition * SceneSettings::barScale );
    m_noteNode->setScale( 8, 4, 4 );
}
