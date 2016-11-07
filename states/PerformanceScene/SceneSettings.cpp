#include "SceneSettings.h"

Ogre::Real SceneSettings::value = 2.0; //default 0.7

float SceneSettings::stringSpacing = 8;
int SceneSettings::fretSpacing = 14;
float SceneSettings::barScale = value*400; //280
Ogre::Vector3 SceneSettings::direction = Ogre::Vector3(0.0, 0.0, value/10); //0.07

SceneSettings::SceneSettings()
{


}
