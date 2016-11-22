#include "Staff.h"

Staff::Staff( Ogre::SceneManager *pSceneMgr, Ogre::SceneNode *pStaffNode, Neck *pNeck ) {
    m_sceneMgr	= pSceneMgr;
    m_staffNode = pStaffNode;
    m_neck		= pNeck;

    m_lastPassedElement = 0;
    m_upcomingElement	= 0;
    m_currentElement	= 0;

    m_elements			 = new Elements( m_sceneMgr, m_staffNode );
    m_notationFileParser = new NotationFileParser( "notation.xml" );
}

Staff::~Staff() {
    m_staffNode->removeAndDestroyAllChildren();
    delete m_notationFileParser;
}

void Staff::loadElements() {
    m_elements->loadElements( m_notationFileParser );
}

bool Staff::elementHasReachedTarget() {
    float elementWorldPosition = 0;

    elementWorldPosition = m_staffNode->getPosition().z + m_elements->m_elements[m_currentElement]->getNode()->getPosition().z;

    if ( elementWorldPosition <= 0 ) {
        return false;
    } else {
        return true;
    }
}

bool Staff::elementIsInStringsRange() {
    int	  range = 180; // If next element is closer than this distance, the actual target will not show
    float elementWorldPosition;

    elementWorldPosition = m_staffNode->getPosition().z + m_elements->m_elements[m_upcomingElement]->getNode()->getPosition().z;

    if ( elementWorldPosition >= -range ) {
        return true;
    } else {
        return false;
    }
}

void Staff::update() {

    if ( m_elements->m_elements[m_upcomingElement] != NULL  &&  elementIsInStringsRange() ) {

        if ( m_elements->m_elements[m_upcomingElement]->m_type == NOTE ) {
            m_neck->getTargets()->showTargetAt( m_elements->m_elements[m_upcomingElement]->getString1(),
                                                m_elements->m_elements[m_upcomingElement]->getString2() );
        } else if ( m_elements->m_elements[m_upcomingElement]->m_type == CHORD ) {
            if ( m_elements->m_elements[m_upcomingElement]->getString1() != 0 ) {
                m_neck->getTargets()->showTargetAt( 1, m_elements->m_elements[m_upcomingElement]->getString1() );
            }
            if ( m_elements->m_elements[m_upcomingElement]->getString2() != 0 ) {
                m_neck->getTargets()->showTargetAt( 2, m_elements->m_elements[m_upcomingElement]->getString2() );
            }
            if ( m_elements->m_elements[m_upcomingElement]->getString3() != 0 ) {
                m_neck->getTargets()->showTargetAt( 3, m_elements->m_elements[m_upcomingElement]->getString3() );
            }
            if ( m_elements->m_elements[m_upcomingElement]->getString4() != 0 ) {
                m_neck->getTargets()->showTargetAt( 4, m_elements->m_elements[m_upcomingElement]->getString4() );
            }
        }

        if ( m_upcomingElement < ( m_elements->m_elements.size() - 1 ) ) {
            ++m_upcomingElement;
        }
    }

    if ( elementHasReachedTarget() ) {
        m_elements->m_elements[m_currentElement]->setVisibility( false );

        if ( m_elements->m_elements[m_currentElement]->m_type == NOTE ) {
            m_neck->getTargets()->hideTargetAt( m_elements->m_elements[m_currentElement]->getString1(),
                                                m_elements->m_elements[m_currentElement]->getString2() );
        } else if ( m_elements->m_elements[m_currentElement]->m_type == CHORD ) {
            m_neck->getTargets()->hideTargetAt( 1, m_elements->m_elements[m_currentElement]->getString1() );
            m_neck->getTargets()->hideTargetAt( 2, m_elements->m_elements[m_currentElement]->getString2() );
            m_neck->getTargets()->hideTargetAt( 3, m_elements->m_elements[m_currentElement]->getString3() );
            m_neck->getTargets()->hideTargetAt( 4, m_elements->m_elements[m_currentElement]->getString4() );
        }

        if ( m_currentElement < ( m_elements->m_elements.size() - 1 ) ) {
            ++m_currentElement;
        }
    }
}
