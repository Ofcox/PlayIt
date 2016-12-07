#include "Targets.h"

Targets::Targets(Ogre::SceneManager *pSceneMgr, Ogre::SceneNode *pNeckNode) {
    m_sceneNode = pNeckNode;
    m_sceneMgr  = pSceneMgr;
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

Targets::~Targets() {
    for ( int y = 0; y <= 3; ++y ) {
        for ( int x = 0; x < 23; ++x ) {
            delete m_targets[y][x];
        }
    }
}
