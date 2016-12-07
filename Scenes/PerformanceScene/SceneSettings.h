#ifndef SCENESETTINGS_H
#define SCENESETTINGS_H

#include <OgreSceneManager.h>
#include "../SongListScene/SongInfo.h"
/*
===============================================================================

    This class contains a basic scene settings

===============================================================================
*/

class SceneSettings {
public:
    static float         stringSpacing;
    static int           fretSpacing;
    static float         barScale;
    static Ogre::Vector3 direction;
    static Ogre::Real    value;

    SceneSettings();

    void setScale( Ogre::Real value /* basic 0.7 /*, float tempo = 60 /* basic 60 bpm*/ ) {
        direction.z = value / -10;
        barScale    = value * 400;
    }
};

#endif // SCENESETTINGS_H
