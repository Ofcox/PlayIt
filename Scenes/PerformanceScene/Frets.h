#ifndef FRETS_H
#define FRETS_H
#include "SceneSettings.h"
#include "AdvancedOgreFramework.hpp"

class Frets {
public:
    Frets( Ogre::SceneManager *pSceneMgr );
    ~Frets();

    void load( Ogre::SceneNode* fretLinesNode );

private:
    static const int    NUM_FRETLINES = 25;
    Ogre::Entity*       m_fretLinesEntity[NUM_FRETLINES];
    Ogre::Entity*       m_fretsEntity[NUM_FRETLINES];
    Ogre::SceneNode*    m_fretLinesNode[NUM_FRETLINES];
    Ogre::SceneNode*    m_fretsNode[NUM_FRETLINES];
    Ogre::SceneManager* m_pSceneMgr;
    Ogre::SceneNode*    m_pFretLinesNode;
    int                 m_width;
};

#endif // FRETS_H
