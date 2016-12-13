#ifndef TARGETS_H
#define TARGETS_H
#include <string>
#include <vector>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "Chord.h"
#include "SceneSettings.h"

/*
===============================================================================

    This class defines targets for upcoming notes

===============================================================================
*/

class NoteTarget {
public:
    Ogre::Entity*    m_noteTargetEntity;
    Ogre::SceneNode* m_noteTargetNode;

    NoteTarget( int string, int fret ) {
        m_string = string;
        m_fret   = fret;
    }
    ~NoteTarget(){
    }

    int getFret() { return m_fret; }
    int getString() { return m_string; }
    void setVisibility( bool isVisible ) { m_noteTargetNode->setVisible( isVisible ); }

private:
    int m_string;
    int m_fret;
};

class Targets {
public:
    Targets( Ogre::SceneManager* pSceneMgr, Ogre::SceneNode* pNeckNode );
    ~Targets();

    void showTargetAt( int string, int fret ) { m_targets[string - 1][fret]->setVisibility( true ); }
    void hideTargetAt( int string, int fret ) { m_targets[string - 1][fret]->setVisibility( false ); }

private:
    Ogre::SceneManager* m_sceneMgr;
    Ogre::SceneNode*    m_sceneNode;

    NoteTarget* m_targets[4][24];
};

#endif // TARGETS_H
