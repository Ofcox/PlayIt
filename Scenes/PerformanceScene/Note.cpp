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

ocx::Note::~Note()
{
    // Destroy entity
    Ogre::SceneNode* parent = m_noteEntity->getParentSceneNode();
    parent->detachObject(m_noteEntity);
    m_sceneMgr->destroyEntity(m_noteEntity->getName());

    // Destroy node
    m_sceneMgr->destroySceneNode(m_noteNode->getName());
}
