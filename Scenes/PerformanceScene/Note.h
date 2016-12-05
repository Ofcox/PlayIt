#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <vector>

#include <OgreSceneManager.h>
#include <OgreEntity.h>

/*
   ===============================================================================

    This class contains definitions of elements base class and Notes

   ===============================================================================
 */

namespace ocx {
    class Note;
}

enum ElementType { NOTE, CHORD };

class Element {
protected:
    std::string m_name;
    float       m_timePosition;
    bool        m_hit        = false;
    bool        m_hasReached = false;
    // Because dynamic casting is expensive, I rather use this array. For notes there will be waste of four ints, but it's
    // still much cheaper.
    int m_strings[4] = {0,0,0,0};

public:
    ElementType m_type;
    int         m_string;
    int         m_fret;

    Element() {
    }
    virtual ~Element() {
    }

    virtual void setVisibility( bool isVisible ) {
    }
    virtual float getTimePosition() {
        return m_timePosition;
    }
    virtual Ogre::SceneNode* getNode() {
        return nullptr;
    }
    virtual std::string getName() {
        return m_name;
    }
    virtual int getString() {
        return m_fret;
    }
    virtual int getFret() {
        return m_string;
    }
    virtual int getFretAt( int string ) {
        return m_strings[( string - 1 )];
    }
};

class ocx::Note : public Element
{
private:
    bool m_isNullFret;

public:
    Ogre::Entity*    m_noteEntity;
    Ogre::SceneNode* m_noteNode;

    ocx::Note( int string, int fret, float timePosition );
    ocx::Note( int string, int fret, float timePosition, bool isNullFret );

    int getFret() {
        return m_fret;
    }
    int getString() {
        return m_string;
    }
    bool getIsNullFret() {
        return m_isNullFret;
    }

    //Simple dependency injection
    void setEntityAndSceneNode( Ogre::Entity* noteEntity, Ogre::SceneNode* noteNode ) {
        m_noteEntity = noteEntity;
        m_noteNode   = noteNode;
    }

    virtual void setVisibility( bool isVisible ) {
        m_noteNode->setVisible( isVisible );
    }
    virtual Ogre::SceneNode* getNode() {
        return m_noteNode;
    }
};

#endif // NOTE_H
