#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <vector>

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "SceneSettings.h"

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
public:
    ElementType m_type;
    int         m_string;
    int         m_fret;

    Element() { }
    virtual ~Element() {}

    virtual void setVisibility( bool isVisible ) {}
    virtual float getTimePosition() { return m_timePosition; }
    virtual Ogre::SceneNode* getNode() { return nullptr; }
    virtual std::string getName() { return m_name; }
    virtual int getString() { return m_fret; }
    virtual int getFret() { return m_string; }
    virtual int getFretAt( int string ) { return m_strings[( string - 1 )]; }

protected:
    std::string m_name;
    float       m_timePosition;
    bool        m_hit        = false;
    bool        m_hasReached = false;
    // Because dynamic casting is expensive, I rather use this array. For notes there will be waste of four ints, but it's
    // still much cheaper.
    int m_strings[4] = {0,0,0,0};

};

class ocx::Note : public Element {
public:
    Ogre::Entity*    m_noteEntity;
    Ogre::SceneNode* m_noteNode;
    Ogre::SceneManager* m_sceneMgr;

    ocx::Note( int string, int fret, float timePosition );
    ocx::Note( int string, int fret, float timePosition, bool isNullFret );
    virtual ~Note();

    void create( Ogre::SceneNode* staffNode, Ogre::SceneManager* sceneMgr );

    int getFret() { return m_fret; }
    int getString() { return m_string; }
    bool getIsNullFret() { return m_isNullFret; }

    virtual void setVisibility( bool isVisible ) { m_noteNode->setVisible( isVisible ); }
    virtual Ogre::SceneNode* getNode() { return m_noteNode; }

private:
    bool m_isNullFret;
};

#endif // NOTE_H
