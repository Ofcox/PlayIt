#include "SceneSettings.h"

Ogre::Real SceneSettings::value = 2.0; //default 0.7

float		  SceneSettings::stringSpacing = 6.0f;
int			  SceneSettings::fretSpacing   = 14;
float		  SceneSettings::barScale	   = value * 400; //280
int           SceneSettings::barCount      = 0;
Ogre::Vector3 SceneSettings::direction	   = Ogre::Vector3( 0.0f, 0.0f, value / 10 ); //0.07

SceneSettings::SceneSettings() {

}
