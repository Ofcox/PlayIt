#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <vector>

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "Element.h"

namespace ocx {
    class Note;
}

/**
 * @brief Basic class for notes
 */
class ocx::Note : public Element {
public:
    Ogre::Entity*    m_noteEntity; /**< Ogre entity of note */
    Ogre::SceneNode* m_noteNode; /**< Ogre node of note */
    Ogre::SceneManager* m_sceneMgr; /**< Ogre scene node */

    /**
     * @brief Constructor for notes
     *
     * @param string
     * @param fret
     * @param bar
     * @param timePosition
     * @param value
     */
    ocx::Note( int string, int fret, int bar, float timePosition, float value );

    /**
     * @brief Constructor mostly for open notes
     *
     * @param string
     * @param fret
     * @param bar
     * @param timePosition
     * @param value
     * @param isNullFret
     */
    ocx::Note( int string, int fret, int bar, float timePosition, float value, bool isNullFret );

    /**
     * @brief
     */
    virtual ~Note();

    /**
     * @brief Creates model for note
     *
     * @param staffNode
     * @param sceneMgr
     */
    void create( Ogre::SceneNode* staffNode, Ogre::SceneManager* sceneMgr );

    /**
     * @brief Returns fret where is the note
     *
     * @return int
     */
    int getFret() { return m_fret; }

    /**
     * @brief Returns string where is the note
     *
     * @return int
     */
    int getString() { return m_string; }

    /**
     * @brief Returns if its a null fret
     *
     * @return bool
     */
    bool getIsNullFret() { return m_isNullFret; }


    /**
     * @brief Sets visibility of note
     *
     * @param isVisible
     */
    virtual void setVisibility( bool isVisible ) { m_noteNode->setVisible( isVisible ); }

    /**
     * @brief Returns Ogre node of the note
     *
     * @return Ogre::SceneNode
     */
    virtual Ogre::SceneNode* getNode() { return m_noteNode; }

private:
    bool m_isNullFret; /**< Is note open? */
};

#endif // NOTE_H
