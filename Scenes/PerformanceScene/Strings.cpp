#include "strings.h"

Strings::Strings( Ogre::SceneManager *pSceneMgr ) {
    m_sceneMgr = pSceneMgr;
}

Strings::~Strings() {

}

void Strings::load( Ogre::SceneNode *stringsNode ) {
    m_pStringsNode = stringsNode;
    int y = 0;
    for ( int i = 0; i < NUM_STRINGS; i++ )
    {
        m_stringsEntity[i] = m_sceneMgr->createEntity( "cube.mesh" );
        switch ( i ) {
        case 0:
            m_stringsEntity[i]->setMaterialName( "Fret/String1Mat" );
            break;
        case 1:
            m_stringsEntity[i]->setMaterialName( "Fret/String2Mat" );
            break;
        case 2:
            m_stringsEntity[i]->setMaterialName( "Fret/String3Mat" );
            break;
        case 3:
            m_stringsEntity[i]->setMaterialName( "Fret/String4Mat" );
            break;
        }

        y				+= SceneSettings::stringSpacing;
        m_stringsNode[i] = stringsNode->createChildSceneNode();
        m_stringsNode[i]->attachObject( m_stringsEntity[i] );
        m_stringsNode[i]->setPosition( 200, y, 0 );
        m_stringsNode[i]->setScale( 400, 0.5, 0.5 );
    }

}
