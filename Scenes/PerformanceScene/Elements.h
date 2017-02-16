#ifndef ELEMENTS_H
#define ELEMENTS_H
#include "Element.h"
#include "NotationFileParser.h"

/**
 * @brief Represents vector of Elements pointers std::vector<Element*>
 */
using VectorElements = std::vector<Element*>;

/**
 * @brief This is the base class for notes and chords
 */
class Elements {
public:
    Ogre::SceneNode*	m_staffNode; /**< Ogre node of Staff */
    Ogre::SceneManager* m_sceneMgr; /**< Ogre scene manager */

    VectorElements m_elementsVector; /**< Container for elements */

    Elements( Ogre::SceneManager *pSceneMgr, Ogre::SceneNode *pStaffNode );
    ~Elements();

    /**
     * @brief Loads all elements into the vector of Elements
     *
     * @param pNotationFileParser
     */
    void loadElements( NotationFileParser* pNotationFileParser );

    /**
     * @brief Returns vector of Elements
     *
     * @return VectorElements
     */
    VectorElements& getElementsVector(){return m_elementsVector;}

private:
    int m_lastPassedElement; /**< Index of the last element that passed through strings */
    int m_currentElement; /**< Index of current element being processsed */
    int m_nextElement; /**< Index of next element that passing through strings */
};

#endif // ELEMENTS_H
