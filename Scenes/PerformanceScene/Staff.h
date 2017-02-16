#ifndef STAFF_H
#define STAFF_H
#include "NotationFileParser.h"

#include "SceneSettings.h"
#include "Elements.h"
#include "Neck.h"
#include "FretGuide.h"

/**
 * @brief This class holds all objects that are on staff
 */
class Staff {
public:

    /**
     * @brief
     *
     * @param pSceneMgr
     * @param pStaffNode
     * @param pNeck
     */

    Staff( Ogre::SceneManager* pSceneMgr, Ogre::SceneNode* pStaffNode, Neck* pNeck );
    /**
     * @brief
     */
    ~Staff();

    /**
     * @brief Loads all elements
     */
    void loadElements();

    /**
     * @brief Check if current element has reached its destination on neck
     *
     * @return bool
     */
    bool elementHasReachedTarget();

    /**
     * @brief Check if next element is in the range that shows the target
     *
     * @return bool
     */
    bool elementIsInStringsRange();

    /**
     * @brief Updates the Staff and all of its parts
     */
    void update();
    Elements* m_elements = nullptr; /**< Object of Elements */

private:
    Ogre::SceneNode* m_staffNode = nullptr; /**< Ogre scene node */

    Ogre::SceneManager* m_sceneMgr = nullptr; /**< Ogre scene manager */
    NotationFileParser* m_notationFileParser = nullptr; /**< Object of NotationParser */

    Neck* m_neck = nullptr; /**< Object of Neck */
    FretGuide* m_fretGuide = nullptr; /**< Object of FreGuide */

    int m_lastPassedElement; /**< Number of the last element that passed through strings */
    int m_currentElement; /**< Index of currently controlled element */
    int m_upcomingElement; /**< Number of next element that passing through strings */
};

#endif // STAFF_H
