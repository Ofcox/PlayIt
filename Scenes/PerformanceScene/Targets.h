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
    int	  m_string;
    int	  m_fret;
    float m_timePosition;

    Ogre::Entity*	 m_noteTargetEntity;
    Ogre::SceneNode* m_noteTargetNode;

    NoteTarget();
    NoteTarget( int string, int fret, float timePosition );
    int getFret() { return m_fret; }
    int getString() { return m_string; }
    float GetTimePosition() { return m_timePosition; }
    virtual void setVisibility( bool isVisible ) {
        m_noteTargetNode->setVisible( isVisible );
    }
};

class ChordTarget : public Target {
    std::vector<Ogre::Entity*> m_chordTargetEntity;

    NoteTarget* string4;
    NoteTarget* string3;
    NoteTarget* string2;
    NoteTarget* string1;
    ChordTarget();

    virtual void setVisibility( bool isVisible ) {
        string4->m_noteTargetNode->setVisible( isVisible );
        string3->m_noteTargetNode->setVisible( isVisible );
        string2->m_noteTargetNode->setVisible( isVisible );
        string1->m_noteTargetNode->setVisible( isVisible );
    }
};

class Targets {
    std::vector<Target*> targets;
    Ogre::SceneManager*	 m_pSceneMgr;
    Ogre::SceneNode*	 m_stringsNode;

    Targets( std::vector<Element*>& elements, Ogre::SceneManager* sceneMgr, Ogre::SceneNode* stringsNode ) {
        m_pSceneMgr	  = sceneMgr;
        m_stringsNode = stringsNode;
        std::vector<Element*>::iterator itr;

        ocx::Note*	 noteObject;
        ocx::Chord*	 chordObject;
        NoteTarget*	 NoteTargetObject;
        ChordTarget* ChordTargetObject;

        for ( itr = elements.begin(); itr != elements.end(); ++itr ) {
            if ( ( *itr )->m_type == NOTE ) {
                NoteTargetObject = new NoteTarget();
                noteObject		 = dynamic_cast<ocx::Note *>( *itr );

                NoteTargetObject->m_noteTargetEntity = m_pSceneMgr->createEntity( "cube.mesh" );
                switch ( noteObject->getString() ) {
                case 1:
                    NoteTargetObject->m_noteTargetEntity->setMaterialName( "Fret/String1Mat" );
                    break;
                case 2:
                    NoteTargetObject->m_noteTargetEntity->setMaterialName( "Fret/String2Mat" );
                    break;
                case 3:
                    NoteTargetObject->m_noteTargetEntity->setMaterialName( "Fret/String3Mat" );
                    break;
                case 4:
                    NoteTargetObject->m_noteTargetEntity->setMaterialName( "Fret/String4Mat" );
                    break;
                }

                NoteTargetObject->m_noteTargetNode = m_stringsNode->createChildSceneNode();
                NoteTargetObject->m_noteTargetNode->attachObject( NoteTargetObject->m_noteTargetEntity );
                NoteTargetObject->m_noteTargetNode->setPosition( ( noteObject->getFret() * SceneSettings::fretSpacing ) - ( SceneSettings::fretSpacing / 2 ),
                                                                 ( noteObject->getString() * SceneSettings::stringSpacing ),
                                                                 0 );
                NoteTargetObject->m_noteTargetNode->setScale( 8, 4, 1 );
                targets.push_back( NoteTargetObject );
            }
        }
    }
    void loadTargets();
};

#endif // TARGETS_H
