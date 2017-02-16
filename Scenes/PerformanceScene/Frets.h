#ifndef FRETS_H
#define FRETS_H
#include "SceneSettings.h"
#include "AdvancedOgreFramework.hpp"

/**
 * @brief This class contains all fres and fretlines in the scene
 */
class Frets {
public:
    /**
     * @brief Creates all frets and fretlines
     *
     * @param pSceneMgr
     */
    Frets( Ogre::SceneManager *pSceneMgr );

    /**
     * @brief
     */
    ~Frets();

    /**
     * @brief Creates models for all frets
     *
     * @param fretLinesNode
     */
    void createModels( Ogre::SceneNode* fretLinesNode );

private:
    static const int    NUM_FRETLINES = 25; /**< Total number of frets */
    Ogre::Entity*       m_fretLinesEntity[NUM_FRETLINES]; /**< Array of Ogre Entity of fretlines */
    Ogre::Entity*       m_fretsEntity[NUM_FRETLINES]; /**< Array of Ogre Entity of frets */
    Ogre::SceneNode*    m_fretLinesNode[NUM_FRETLINES]; /**< Array of Ogre Node of fretlines */
    Ogre::SceneNode*    m_fretsNode[NUM_FRETLINES]; /**< Array of Ogre Node of frets */
    Ogre::SceneManager* m_pSceneMgr; /**< Ogre scene manager */
    Ogre::SceneNode*    m_pFretLinesNode; /**< Ogre Node of frets */
};

#endif // FRETS_H
