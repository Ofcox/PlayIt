#ifndef TARGETS_H
#define TARGETS_H
#include <string>
#include <vector>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "Chord.h"
#include "SceneSettings.h"

/**
 * @brief This class defines targets for upcoming notes
 */
class NoteTarget {
public:
    Ogre::Entity*    m_noteTargetEntity; /**< Ogre entity of target */
    Ogre::SceneNode* m_noteTargetNode; /**< Ogre node of target */

    /**
     * @brief
     *
     * @param string
     * @param fret
     */
    NoteTarget( int string, int fret ) {
        m_string = string;
        m_fret   = fret;
    }

    /**
     * @brief
     */
    ~NoteTarget(){
    }

    /**
     * @brief Returns fret where is the note target
     *
     * @return int
     */
    int getFret() { return m_fret; }

    /**
     * @brief Returns string where is the note target
     *
     * @return int
     */
    int getString() { return m_string; }

    /**
     * @brief Sets visibility of target
     *
     * @param isVisible
     */
    void setVisibility( bool isVisible ) { m_noteTargetNode->setVisible( isVisible ); }

private:
    int m_string; /**< String where is the note target */
    int m_fret; /**< Fret where is the note target */
};

/**
 * @brief Container of all targets stored in the field of arrays
 */
class Targets {
public:
    /**
     * @brief
     *
     * @param pSceneMgr
     * @param pNeckNode
     */
    Targets( Ogre::SceneManager* pSceneMgr, Ogre::SceneNode* pNeckNode );

    /**
     * @brief
     *
     */
    ~Targets();

    /**
     * @brief Shows target at defined position
     *
     * @param string
     * @param fret
     */
    void showTargetAt( int string, int fret ) { m_targets[string - 1][fret]->setVisibility( true ); }

    /**
     * @brief Hides target at defined position
     *
     * @param string
     * @param fret
     */
    void hideTargetAt( int string, int fret ) { m_targets[string - 1][fret]->setVisibility( false ); }

private:
    Ogre::SceneManager* m_sceneMgr; /**< Ogre scene manager */
    Ogre::SceneNode*    m_sceneNode; /**< Ogre scene node */

    NoteTarget* m_targets[4][24]; /**< Field of all note targets */
};

#endif // TARGETS_H
