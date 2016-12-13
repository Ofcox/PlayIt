#include "Neck.h"

Neck::Neck( Ogre::SceneManager *pSceneMgr, Ogre::SceneNode *pNeckNode ) {
    m_strings = new Strings( pSceneMgr );
    m_strings->load( pNeckNode );

    m_targets = new Targets( pSceneMgr, pNeckNode );
}

Neck::~Neck()
{
    delete m_strings;
    delete m_targets;
}
