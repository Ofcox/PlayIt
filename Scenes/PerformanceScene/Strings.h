#ifndef STRINGS_H
#define STRINGS_H
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "SceneSettings.h"

/**
 * @brief String that are part of the performance scene
 */
class Strings {
private:
    static const int	NUM_STRINGS = 4; /**< Number of strings */
    Ogre::Entity*		m_stringsEntity[NUM_STRINGS]; /**< Ogre entities of all strings */
    Ogre::SceneNode*	m_stringsNode[NUM_STRINGS]; /**< Ogre nodes of all strings */
    Ogre::SceneManager* m_sceneMgr; /**< Ogre scene manager */
    Ogre::SceneNode*	m_pStringsNode; /**< Parent Ogre node of string */

public:
    /**
     * @brief
     *
     * @param pSceneMgr
     */
    Strings( Ogre::SceneManager* pSceneMgr );

    /**
     * @brief
     */
    ~Strings();

    /**
     * @brief Loads models of all strings
     *
     * @param stringsNode
     */
    void load( Ogre::SceneNode* stringsNode );
};

#endif // STRINGS_H
