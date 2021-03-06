#include "fretguide.h"
#include "AdvancedOgreFramework.hpp"

FretGuide::FretGuide( Ogre::SceneManager* pSceneMgr ) {
    m_pSceneMgr = pSceneMgr;
    m_width		= 5;
}

FretGuide::~FretGuide() {
    for ( int i = 0; i < NUM_FRETLINES; i++ ) {
        Ogre::SceneNode* parent = m_fretLinesEntity[i]->getParentSceneNode();
        parent->detachObject(m_fretLinesEntity[i]);
        m_pSceneMgr->destroyEntity(m_fretLinesEntity[i]->getName());
        // entity is now destroyed, don't try to use the pointer anymore!

        // optionally destroy node
        m_pSceneMgr->destroySceneNode(m_fretLinesNode[i]->getName());

        Ogre::SceneNode* parent_2 = m_fretsEntity[i]->getParentSceneNode();
        parent_2->detachObject(m_fretsEntity[i]);
        m_pSceneMgr->destroyEntity(m_fretsEntity[i]->getName());
        // entity is now destroyed, don't try to use the pointer anymore!

        // optionally destroy node
        m_pSceneMgr->destroySceneNode(m_fretsNode[i]->getName());
    }
}

void FretGuide::load( Ogre::SceneNode *fretLinesNode ) {
    OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Loading performance scene..." );
    m_pFretLinesNode = fretLinesNode;

    int x = 0;
    for ( int i = 0; i < NUM_FRETLINES; i++ ) {
        m_fretLinesEntity[i] = m_pSceneMgr->createEntity( "cube.mesh" );

        m_fretLinesNode[i] = fretLinesNode->createChildSceneNode();
        m_fretLinesNode[i]->attachObject( m_fretLinesEntity[i] );
        m_fretLinesNode[i]->setPosition( x, 0, -600 );
        m_fretLinesNode[i]->setScale( 0.4, 0.2, 1200.0 );

        m_fretsEntity[i] = m_pSceneMgr->createEntity( "cube.mesh" );
        m_fretsEntity[i]->setMaterialName( "Fret/FretMat" );
        m_fretsNode[i] = fretLinesNode->createChildSceneNode();
        m_fretsNode[i]->attachObject( m_fretsEntity[i] );
        m_fretsNode[i]->setPosition( x, 15, 1 );
        m_fretsNode[i]->setScale( 0.5, 25, 0.5 );

        x += SceneSettings::fretSpacing;
    }
}
