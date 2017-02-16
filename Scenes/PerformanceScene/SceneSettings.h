#ifndef SCENESETTINGS_H
#define SCENESETTINGS_H

#include <OgreSceneManager.h>
#include "../SongListScene/SongInfo.h"

/**
 * @brief This class contains a basic scene settings
 */
class SceneSettings {
public:
    static float         stringSpacing; /**< Space between strings */
    static int           fretSpacing; /**< Space between frets */
    static float         barScale; /**< Space between bars */
    static int           barCount; /**< Total number of bars */
    static Ogre::Vector3 direction; /**< Everything on the staff is in negative direction */
    static Ogre::Real    value; /**< Scale of staff */

    /**
     * @brief
     */
    SceneSettings();

    void setScale( Ogre::Real value /* basic 0.7 /*, float tempo = 60 /* basic 60 bpm*/ ) {
        direction.z = value / -10;
        barScale    = value * 400;
    }
};

#endif // SCENESETTINGS_H
