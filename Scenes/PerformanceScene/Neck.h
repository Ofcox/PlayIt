#ifndef NECK_H
#define NECK_H
#include "Strings.h"
#include "Targets.h"

/**
 * @brief This class contains all objects that are bound to the neck
 */
class Neck {
public:

    /**
     * @brief Simple consturctor
     *
     * @param pSceneMgr
     * @param pNeckNode
     */
    Neck( Ogre::SceneManager* pSceneMgr, Ogre::SceneNode* pNeckNode );

    /**
     * @brief
     *
     */
    ~Neck();

    /**
     * @brief Returns Targets object
     *
     * @return Targets
     */
    Targets* getTargets() { return m_targets; }

private:
    Strings* m_strings; /**< Strings object */
    Targets* m_targets; /**< Targets object */
};

#endif // NECK_H
