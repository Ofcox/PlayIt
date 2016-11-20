#include "Neck.h"

Neck::Neck( Ogre::SceneManager *pSceneMgr, Ogre::SceneNode *pNeckNode, Staff *pStaff ) {
    m_strings = new Strings( pSceneMgr );
    m_strings->load( pNeckNode );

    m_targets = new Targets( pStaff->getElements()->m_elements, pSceneMgr, pNeckNode );
}
