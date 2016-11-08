#ifndef PERFORMANCESCENE_H
#define PERFORMANCESCENE_H

#include <string>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "note.h"
#include "fretguide.h"
#include "strings.h"

/*
===============================================================================

    This class is processing the scene where you play

    includes
    Notes
    FretGuide

    Neck
    Strings
    FretLines

    Notes and FretGuide are bound to the Staff. The Staff is shifting in Z axis.

===============================================================================
*/

class PerformanceScene
{
private:
    Ogre::SceneManager* m_sceneMgr;
    Ogre::Vector3		m_direction;

    Ogre::SceneNode* m_perfSceneNode;
    Ogre::SceneNode* m_staffNode;
    Ogre::SceneNode* m_fretLinesNode;
    Ogre::SceneNode* m_stringsNode;

    FretGuide* m_fretguides;
    Strings*   m_strings;
public:
    PerformanceScene( Ogre::SceneManager *sceneMgr );
    ~PerformanceScene();

    void scene();
    void update( const Ogre::FrameEvent &evt );

};

#endif // PERFORMANCESCENE_H
