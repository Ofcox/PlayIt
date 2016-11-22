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

    if ( elementWorldPosition > 0 ) {
        return false;
    } else {
        return true;
    }
}

bool Staff::elementIsInStringsRange() {
    int	  range = 180; // If next element is closer than this distance, the actual target will not show
    float elementWorldPosition;

    elementWorldPosition = m_staffNode->getPosition().z + m_elements->m_elements[m_upcomingElement]->getNode()->getPosition().z;

    if ( elementWorldPosition <= range ) {
        return true;
    } else {
        return false;
    }
}

//Not optimal yet, but it works
void Staff::update() {

    if ( m_elements->m_elements[m_upcomingElement] != NULL  &&  elementIsInStringsRange() ) {

        if ( m_elements->m_elements[m_upcomingElement]->m_type == NOTE ) {
            m_neck->getTargets()->showTargetAt( m_elements->m_elements[m_upcomingElement]->getString(),
                                                m_elements->m_elements[m_upcomingElement]->getFret() );

        } else if ( m_elements->m_elements[m_upcomingElement]->m_type == CHORD ) {
            for ( int i = 1; i <= 4; ++i ) {
                if ( m_elements->m_elements[m_upcomingElement]->getFretAt( i ) != 0 ) {
                    m_neck->getTargets()->showTargetAt( i, m_elements->m_elements[m_upcomingElement]->getFretAt( i ) );
                }
            }
        }

        if ( m_upcomingElement < ( m_elements->m_elements.size() - 1 ) ) {
            ++m_upcomingElement;
        }
    }
//    bool hideTarget = false;
    if ( elementHasReachedTarget() ) {
        m_elements->m_elements[m_currentElement]->setVisibility( false );

        if ( m_elements->m_elements[m_currentElement]->m_type == NOTE ) {
//            for ( int i = 1; i <= 5; ++i ) {
//                if(m_elements->m_elements[m_currentElement]->getString() )
//                    hideTarget
//            }
            //if ( m_elements->m_elements[m_currentElement]->getString1() != m_elements->m_elements[m_currentElement + 1]->getString1() )
            // Pokud je alespoň jeden následujících x elementů shodných a je v dosahu
            m_neck->getTargets()->hideTargetAt( m_elements->m_elements[m_currentElement]->getString(),
                                                m_elements->m_elements[m_currentElement]->getFret() );

        } else if ( m_elements->m_elements[m_currentElement]->m_type == CHORD ) {
            for ( int i = 1; i <= 4; ++i ) {
                if ( m_elements->m_elements[m_currentElement]->getFretAt( i ) != m_elements->m_elements[m_currentElement + 1]->getFretAt( i ) ) {
                    m_neck->getTargets()->hideTargetAt( i, m_elements->m_elements[m_currentElement]->getFretAt( i ) );
                }
            }
        }

        if ( m_currentElement < ( m_elements->m_elements.size() - 1 ) ) {
            ++m_currentElement;
        }
    }
}
