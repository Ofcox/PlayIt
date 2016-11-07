#include "fretguide.h"
#include "AdvancedOgreFramework.hpp"

FretGuide::FretGuide(Ogre::SceneManager* pSceneMgr)
{
    m_pSceneMgr = pSceneMgr;
    m_width = 5;
}

FretGuide::~FretGuide()
{

}

void FretGuide::load(Ogre::SceneNode *fretLinesNode)
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Loading performance scene...");
    m_pFretLinesNode = fretLinesNode;

    //fretLinesNode = sceneMgr->getRootSceneNode()->createChildSceneNode();

    int x = 0;
    for (int i = 0; i < NUM_FRETLINES; i++)
    {
        m_fretLinesEntity[i] = m_pSceneMgr->createEntity("cube.mesh");

        m_fretLinesNode[i] = fretLinesNode->createChildSceneNode();
        m_fretLinesNode[i]->attachObject(m_fretLinesEntity[i]);
        m_fretLinesNode[i]->setPosition(x, 0, -200);
        m_fretLinesNode[i]->setScale(0.8, 0.2, 400.0);

        m_fretsEntity[i] = m_pSceneMgr->createEntity("cube.mesh");
        m_fretsEntity[i]->setMaterialName("Fret/FretMat");
        m_fretsNode[i] = fretLinesNode->createChildSceneNode();
        m_fretsNode[i]->attachObject(m_fretsEntity[i]);
        m_fretsNode[i]->setPosition(x, 20, 1);
        m_fretsNode[i]->setScale(0.5, 30, 0.5);

        x+=SceneSettings::fretSpacing;
    }
}

void FretGuide::unload()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Unloading performance scene...");
//    for (int i = 0; i < NUM_FRETLINES; i++)
//    {
//        m_pSceneMgr->destroyEntity(m_fretLinesEntity[i]);
//        //m_pFretLinesNode->removeAndDestroyChild(m_fretLinesNode[i]);
//        m_pSceneMgr->destroyEntity(m_fretsEntity[i]);
//        //m_pFretLinesNode->removeAndDestroyChild(m_fretsNode[i]);

//    }
//    m_pFretLinesNode->removeAllChildren();
    m_pFretLinesNode->removeAndDestroyAllChildren();
}

