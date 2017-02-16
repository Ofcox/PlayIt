#ifndef BAR_H
#define BAR_H
#include <string>
#include <vector>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "SceneSettings.h"

/**
 * @brief This class represents bar line in FretGuide object
 */
class Bar {
public:
    Ogre::Entity*       m_barEntity; /**< Ogre entity of bar */
    Ogre::SceneNode*    m_barNode; /**< Ogre node of bar */
    Ogre::SceneManager* m_sceneMgr; /**< Ogre scene manager pointer */
    float m_timeRelativePostion; /**< Relative time position that represents the bar number (eg. 1, 2, 3...) */
    float m_timeAbsolutePostion; /**< Absolute time position that represents the calculated time position */
    float m_beginFretPosition; /**< Position of the bar defined by left side */
    int   m_width; /**< Width of the bar defined by number of frets */

    /**
     * @brief Returns bar number
     *
     * @return float
     */
    float getRelativeTimePosition(){return m_timeRelativePostion;}

    /**
     * @brief Returns calculated time position
     *
     * @return float
     */
    float getAbsoluteTimePosition(){return m_timeAbsolutePostion;}

    /**
     * @brief Sets begining position defined by left side
     *
     * @param beginFret
     */
    void setBeginFret(int beginFret){ m_beginFretPosition = beginFret;
                                      m_barNode->setPosition( (beginFret * SceneSettings::fretSpacing) + SceneSettings::fretSpacing, 0, m_timeAbsolutePostion );}

    /**
     * @brief Sets width of the bar
     *
     * @param width Nuber of frets
     */
    void setWidth(int width){
        m_width = width ;
        m_barNode->setScale( SceneSettings::fretSpacing * m_width, 0.2, 1 );}

    /**
     * @brief This constructor requires only bar number. Aditional informations have to be defined later.
     *
     * @param pSceneMgr Pointer to Ogre scene manager
     * @param pFretGuideNode Pointer to the parent FretGuideNode
     * @param barNumber Number of the bar
     */
    Bar( Ogre::SceneManager *pSceneMgr, Ogre::SceneNode *pFretGuideNode, int barNumber){
        m_sceneMgr = pSceneMgr;
        m_barEntity = m_sceneMgr->createEntity( "cube.mesh" );
        m_timeRelativePostion = barNumber;
        m_timeAbsolutePostion = -(barNumber * SceneSettings::barScale);

        m_barNode = pFretGuideNode->createChildSceneNode();
        m_barNode->attachObject( m_barEntity );
        m_barNode->setPosition( (SceneSettings::fretSpacing * 25) / 2, 0, m_timeAbsolutePostion );
        m_barNode->setScale( SceneSettings::fretSpacing * 25, 0.2, 1 );
    }
};

#endif // BAR_H
