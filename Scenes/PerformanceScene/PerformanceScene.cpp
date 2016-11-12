#include "performancescene.h"

PerformanceScene::PerformanceScene( Ogre::SceneManager *sceneMgr ) :
    m_direction( Ogre::Vector3::ZERO ) { // Kurva nezapomenout; samo se to nevynuluje
    m_direction.z = 100;
    m_sceneMgr	  = sceneMgr;
    m_fretguides  = new FretGuide( m_sceneMgr );
    m_strings	  = new Strings( m_sceneMgr );

}

PerformanceScene::~PerformanceScene() {
    delete m_fretguides;
    delete m_strings;
}

void PerformanceScene::scene() {
    //Hierarchy
    //rootSceneNode
    //      perfSceneNode
    //          fretGuide
    //          staffNode
    //              notes


    m_perfSceneNode = m_sceneMgr->getRootSceneNode()->createChildSceneNode( "PerfSceneNode" );



    ///staff node holds data about notes
    m_staffNode		= m_perfSceneNode->createChildSceneNode( "StaffNode" );
    m_fretLinesNode = m_perfSceneNode->createChildSceneNode( "FretLinesNode" );
    m_stringsNode	= m_perfSceneNode->createChildSceneNode( "StringsNode" );

    m_fretguides->load( m_fretLinesNode );
    m_strings->load( m_stringsNode );

    m_staffNode->setPosition( 0, 0, 0 );
    m_fretLinesNode->setPosition( 0, 0, 0 );
    m_stringsNode->setPosition( 0, 0, 0 );

}

void PerformanceScene::update( const Ogre::FrameEvent &evt ) {
    //m_direction.z = 100;
    ///ok
    m_staffNode->translate( m_direction * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL );
    //std::cerr << "indirect " << evt.timeSinceLastFrame << std::endl;
}
