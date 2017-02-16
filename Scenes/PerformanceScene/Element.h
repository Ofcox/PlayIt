#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>
#include <OgreSceneManager.h>

#include "SceneSettings.h"

/**
 * @brief Enumeration of all types of elements
 */
enum ElementType { NOTE,
                   CHORD };

/**
 * @brief This class is a base class for all elements like Notes and Chords
 */
class Element {
public:
    ElementType m_type; /**< Type of the element */

    /**
     * @brief This constructor only declares element in the Elements vector
     */
    Element();

    /**
     * @brief
     */
    virtual ~Element() { }

    /**
     * @brief Sets visibility of the element
     *
     * @param isVisible
     */
    virtual void setVisibility( bool isVisible ) {}

    /**
     * @brief Returns bar to which element belongs
     *
     * @return int
     */
    virtual int getBar() {return m_bar;}

    /**
     * @brief Returns position on the bar
     *
     * @return float
     */
    virtual float getRelativeTimePosition() { return m_barPosition; }

    /**
     * @brief Returns calculated time position
     *
     * @return float
     */
    virtual float getAbsoluteTimePosition() { return -(m_barPosition * SceneSettings::barScale); }

    /**
     * @brief Returns Ogre node
     *
     * @return Ogre::SceneNode
     */
    virtual Ogre::SceneNode* getNode() { return nullptr; }

    /**
     * @brief Returns identification name
     *
     * @return std::string
     */
    virtual std::string getName() { return m_name; }

    /**
     * @brief Returns string for single note element
     *
     * @return int
     */
    virtual int getString() { return m_fret; }

    /**
     * @brief Returns fret for single note element
     *
     * @return int
     */
    virtual int getFret() { return m_string; }

    /**
     * @brief Returns fret number for given string
     *
     * @param string
     * @return int
     */
    virtual int getFretAt( int string ) { return m_strings[( string - 1 )]; }

    /**
     * @brief Returns duration of element
     *
     * @return float
     */
    virtual float getValue() { return m_value; }

protected:
    std::string m_name; /**< Identification name of the element */
    int         m_bar; /**< Bar to which element belongs */
    float       m_barPosition; /**< Position of element on the bar */
    float       m_value; /**< duration of the element */
    bool        m_hit        = false; /**< Was element hit? */
    bool        m_hasReached = false; /**< Has element reached the target? */
    // Because dynamic casting is expensive, I rather use this array. For notes there will be waste of four ints, but it's
    // still much cheaper.
    int         m_strings[4] = {0,0,0,0}; /**< This array stores at which frets are strings held */
    int         m_string; /**< String for single note element */
    int         m_fret; /**< Fret for single note element */
};

#endif // ELEMENT_H
