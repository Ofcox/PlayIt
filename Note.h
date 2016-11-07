#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <vector>

#include <OgreSceneManager.h>
#include <OgreEntity.h>

namespace ocx {
    class Note;
}

enum ElementType { NOTE, CHORD };

class Element {
public:
    ElementType m_type;
    float		m_timePosition;
    bool		m_hit		 = false;
    bool		m_hasReached = false;

    Element() {}
    virtual ~Element() {}

    virtual void setVisibility( bool isVisible ) {
        //dodelat, aby se cile ve Strings tride zneviditelnily
    }
};

class ocx::Note : public Element
{
public:
    Ogre::Entity*	 m_noteEntity;
    Ogre::SceneNode* m_noteNode;

    bool		m_isNullFret;
    std::string m_name;
    int			m_string;
    int			m_fret;

    ocx::Note( int string, int fret, float timePosition );
    ocx::Note( int string, int fret, float timePosition, bool isNullFret );

    int getFret() { return m_fret; }
    int getString() { return m_string; }
    float GetTimePosition() { return m_timePosition; }
    void setEntityAndSceneNode( Ogre::Entity* noteEntity, Ogre::SceneNode* noteNode ) {
        m_noteEntity = noteEntity;
        m_noteNode	 = noteNode;
    }

    virtual void setVisibility( bool isVisible ) {
        m_noteNode->setVisible( isVisible );
    }
};

#endif // NOTE_H
