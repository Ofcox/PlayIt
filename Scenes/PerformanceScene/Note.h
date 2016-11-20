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
protected:
    float m_timePosition;
    bool  m_hit		   = false;
    bool  m_hasReached = false;

public:
    ElementType m_type;

    Element() {}
    virtual ~Element() {}

    virtual void setVisibility( bool isVisible ) { }
    virtual float getTimePosition() {return m_timePosition; }
    virtual Ogre::SceneNode* getNode() {return nullptr; }
};

class ocx::Note : public Element
{
private:
    bool		m_isNullFret;
    std::string m_name;
    int			m_string;
    int			m_fret;

public:
    Ogre::Entity*	 m_noteEntity;
    Ogre::SceneNode* m_noteNode;

    ocx::Note( int string, int fret, float timePosition );
    ocx::Note( int string, int fret, float timePosition, bool isNullFret );

    int getFret() { return m_fret; }
    int getString() { return m_string; }
    std::string getName() {return m_name; }
    bool getIsNullFret() {return m_isNullFret; }

    //Simple dependency injection
    void setEntityAndSceneNode( Ogre::Entity* noteEntity, Ogre::SceneNode* noteNode ) {
        m_noteEntity = noteEntity;
        m_noteNode	 = noteNode;
    }

    virtual void setVisibility( bool isVisible ) {
        m_noteNode->setVisible( isVisible );
    }
    virtual Ogre::SceneNode* getNode() {return m_noteNode; }
};

#endif // NOTE_H
