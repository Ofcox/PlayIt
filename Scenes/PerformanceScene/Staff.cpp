#include "Staff.h"

Staff::Staff( Ogre::SceneManager *pSceneMgr, Ogre::SceneNode *pStaffNode, Neck *pNeck ) {
    m_sceneMgr  = pSceneMgr;
    m_staffNode = pStaffNode;
    m_neck      = pNeck;

    m_lastPassedElement = 0;
    m_upcomingElement   = 0;
    m_currentElement    = 0;

    m_elements           = new Elements( m_sceneMgr, m_staffNode );
    m_notationFileParser = new NotationFileParser( "notation.xml" );

}

Staff::~Staff() {
    //m_staffNode->removeAndDestroyAllChildren();
    delete m_notationFileParser;
    delete m_elements;
}

void Staff::loadElements() {
    m_elements->loadElements( m_notationFileParser );
    // Fret Guide
    m_fretGuide = new FretGuide(m_sceneMgr, m_staffNode);
}

bool Staff::elementHasReachedTarget() {
    float elementWorldPosition = 0;

    elementWorldPosition = m_staffNode->getPosition().z + m_elements->m_elementsVector[m_currentElement]->getNode()->getPosition().z;

    if ( elementWorldPosition <= 0 ) {
        return false;
    } else {
        return true;
    }
}

bool Staff::elementIsInStringsRange() {
    int   range = 380; // If next element is closer than this distance, the actual target will not show
    float elementWorldPosition;

    elementWorldPosition = m_staffNode->getPosition().z + m_elements->m_elementsVector[m_upcomingElement]->getNode()->getPosition().z;

    if ( elementWorldPosition >= -range ) {
        return true;
    } else {
        return false;
    }
}

//Not optimal yet, but it works
void Staff::update() {
    if (!m_elements->m_elementsVector.empty()){
        if ( m_elements->m_elementsVector[m_upcomingElement] != NULL  &&  elementIsInStringsRange() ) {

            if ( m_elements->m_elementsVector[m_upcomingElement]->m_type == NOTE ) {
                m_neck->getTargets()->showTargetAt( m_elements->m_elementsVector[m_upcomingElement]->getString(),
                                                    m_elements->m_elementsVector[m_upcomingElement]->getFret() );

            } else if ( m_elements->m_elementsVector[m_upcomingElement]->m_type == CHORD ) {
                for ( int i = 1; i <= 4; ++i ) {
                    if ( m_elements->m_elementsVector[m_upcomingElement]->getFretAt( i ) != 0 ) {
                        m_neck->getTargets()->showTargetAt( i, m_elements->m_elementsVector[m_upcomingElement]->getFretAt( i ) );
                    }
                }
            }

            if ( m_upcomingElement < ( m_elements->m_elementsVector.size() - 1 ) ) {
                ++m_upcomingElement;
            }
        }
        // If element has reached taret
        if ( elementHasReachedTarget() ) {
            m_elements->m_elementsVector[m_currentElement]->setVisibility( false );

            if ( m_elements->m_elementsVector[m_currentElement]->m_type == NOTE ) {
                m_neck->getTargets()->hideTargetAt( m_elements->m_elementsVector[m_currentElement]->getString(),
                                                    m_elements->m_elementsVector[m_currentElement]->getFret() );

            } else if ( m_elements->m_elementsVector[m_currentElement]->m_type == CHORD ) {
                // if the next element does exists
                if( m_currentElement < ( m_elements->m_elementsVector.size() - 1 ) ){
                    for ( int i = 1; i <= 4; ++i ) {
                        if ( m_elements->m_elementsVector[m_currentElement]->getFretAt( i ) != (m_elements->m_elementsVector[m_currentElement + 1]->getFretAt( i ) ) ){
                            m_neck->getTargets()->hideTargetAt( i, m_elements->m_elementsVector[m_currentElement]->getFretAt( i ) );
                        }
                    }
                    //if the next element does not exist, then clear all notes
                } else {
                    for ( int i = 1; i <= 4; ++i ) {
                        m_neck->getTargets()->hideTargetAt( i, m_elements->m_elementsVector[m_currentElement]->getFretAt( i ) );
                    }

                    // TODO: End of track
                }
            }

            if ( m_currentElement < ( m_elements->m_elementsVector.size() - 1 ) ) {
                ++m_currentElement;
            }
        }
    }
}
