#ifndef TARGETS_H
#define TARGETS_H
#include <string>
#include <vector>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "Chord.h"
#include "SceneSettings.h"

class Target
{
public:
    std::string m_type;
    Target() {}
    virtual ~Target() {}
    virtual void setVisibility( bool isVisible ) {}

};

class NoteTarget : public Target {
public:
    int m_string;
    int m_fret;

    Ogre::Entity*	 m_noteTargetEntity;
    Ogre::SceneNode* m_noteTargetNode;

    NoteTarget( int string, int fret ) {
        m_string = string;
        m_fret	 = fret;
    }

    int getFret() { return m_fret; }
    int getString() { return m_string; }
    virtual void setVisibility( bool isVisible ) {
        m_noteTargetNode->setVisible( isVisible );
    }
};

class Targets {
public:
    Ogre::SceneManager* m_sceneMgr;
    Ogre::SceneNode*	m_sceneNode;

    NoteTarget* m_targets[4][24];

    Targets( Ogre::SceneManager* pSceneMgr, Ogre::SceneNode* pNeckNode ) {
        m_sceneNode = pNeckNode;
        m_sceneMgr	= pSceneMgr;
        for ( int y = 0; y <= 3; ++y ) {
            for ( int x = 0; x < 23; ++x ) {

                m_targets[y][x] = new NoteTarget( y + 1, x );

                m_targets[y][x]->m_noteTargetEntity = m_sceneMgr->createEntity( "cube.mesh" );
                switch ( y ) {
                case 0:
                    m_targets[y][x]->m_noteTargetEntity->setMaterialName( "Fret/String1Mat" );
                    break;
                case 1:
                    m_targets[y][x]->m_noteTargetEntity->setMaterialName( "Fret/String2Mat" );
                    break;
                case 2:
                    m_targets[y][x]->m_noteTargetEntity->setMaterialName( "Fret/String3Mat" );
                    break;
                case 3:
                    m_targets[y][x]->m_noteTargetEntity->setMaterialName( "Fret/String4Mat" );
                    break;
                }

                m_targets[y][x]->m_noteTargetNode = m_sceneNode->createChildSceneNode();
                m_targets[y][x]->m_noteTargetNode->attachObject( m_targets[y][x]->m_noteTargetEntity );
                m_targets[y][x]->m_noteTargetNode->setPosition( ( x * SceneSettings::fretSpacing ) -( SceneSettings::fretSpacing / 2 ),
                                                                ( ( y + 1 ) * SceneSettings::stringSpacing ),
                                                                0 );
                m_targets[y][x]->m_noteTargetNode->setScale( 8, 4, 1 );

                m_targets[y][x]->setVisibility( false );
            }
        }
    }

    void showTargetAt( int string, int fret ) {m_targets[string - 1][fret]->setVisibility( true ); }
    void hideTargetAt( int string, int fret ) {m_targets[string - 1][fret]->setVisibility( false ); }
};

#endif // TARGETS_H
