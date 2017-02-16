#ifndef FRETGUIDE_H
#define FRETGUIDE_H
#include <string>
#include <vector>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "SceneSettings.h"
#include "Bar.h"
#include "Chord.h"
#include "Elements.h"

/**
 * @brief Basic guide for single element
 */
class FretTrail {
public:
    Ogre::Entity*    m_fretTrailEntity; /**< Ogre entity */
    Ogre::SceneNode* m_fretTrailNode; /**< Ogre scene node */
    Ogre::SceneManager* m_sceneMgr; /**< Ogre scene manager */

    int m_size;
    int m_fret;
    float m_timePosition;
    float m_duration;

    /**
     * @brief Creates a single fret trail
     *
     * @param pSceneMgr
     * @param pFretGuideNode
     * @param fret
     * @param timePosition
     * @param size
     * @param duration
     */
    FretTrail( Ogre::SceneManager *pSceneMgr, Ogre::SceneNode *pFretGuideNode, int fret, float timePosition, int size, float duration ){
        m_sceneMgr = pSceneMgr;
        m_fretTrailEntity = m_sceneMgr->createEntity( "trail.mesh" );
        m_fretTrailEntity->setMaterialName( "Frame/ChordMat" );
        m_fret = fret;
        m_size = size;
        m_timePosition = timePosition;
        m_duration = duration;

        m_fretTrailNode = pFretGuideNode->createChildSceneNode();
        m_fretTrailNode->attachObject( m_fretTrailEntity );
        m_fretTrailNode->setPosition( ( m_fret * SceneSettings::fretSpacing ) - ( SceneSettings::fretSpacing ), 0, -m_timePosition * SceneSettings::barScale );
        m_fretTrailNode->setScale( SceneSettings::fretSpacing * m_size, 1, (m_timePosition + (m_duration * SceneSettings::barScale)) );
    }
    void setAbsoluteLength(float length){
        m_fretTrailNode->setPosition( ( m_fret * SceneSettings::fretSpacing ) - ( SceneSettings::fretSpacing ), 0, (-m_timePosition * SceneSettings::barScale) + length );
        m_fretTrailNode->setScale( SceneSettings::fretSpacing * m_size, 1, length );
    }
    void setRelativeLength(float length){
        m_fretTrailNode->setPosition( ( m_fret * SceneSettings::fretSpacing ) - ( SceneSettings::fretSpacing ), 0, (-m_timePosition * SceneSettings::barScale) + length );
        m_fretTrailNode->setScale( SceneSettings::fretSpacing * m_size, 1, (m_timePosition + (length * SceneSettings::barScale)) );
    }
};

/**
 * @brief This class shows how to put fingers on the neck by placing rectangles between fretlines on the staff
 */
class FretGuide {
public:
    std::vector<Bar*> m_vectorBars; /**< Bar lines */
    std::vector<FretTrail*> m_vectorFretTrails; /**< TODO: describe */
    Ogre::SceneManager* m_sceneMgr; /**< Ogre scene manager */
    Ogre::SceneNode* m_fretGuideNode; /**< Ogre scene node */

    /**
     * @brief This constructor automatically creates bar lines
     *
     * @param pSceneMgr
     * @param pStaffNode
     */
    FretGuide( Ogre::SceneManager* pSceneMgr, Ogre::SceneNode* pStaffNode) {
        m_sceneMgr = pSceneMgr;
        m_fretGuideNode = pStaffNode;
        for (int itr = 0; itr <= SceneSettings::barCount + 2; itr++){
            m_vectorBars.push_back(new Bar(m_sceneMgr, pStaffNode, itr ));
        }
    }

    /**
     * @brief Generates whole fret guide
     *
     * @param elements
     */
    void createTrails( Elements* elements );
};

#endif // FRETGUIDE_H
