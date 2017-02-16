#include "fretguide.h"

void FretGuide::createTrails(Elements *elements)
{
    Element* PreviousElementObject;
    ocx::Chord* ChordObject;
    ocx::Note* NoteObject;
    float currentBeginPosition = 0;
    float currentEndPostition = 0;
    int currentTrailBeginFret = 0;
    int currentTrailSize = 0;
    int currentBar = 0;

    ///std::vector<Element*>::iterator itr;
//        for ( itr = elements.begin(); itr != elements.end(); ++itr )
//        {
//            ( *itr )->getName();
//        }
    ///for ( itr = elements->getElementsVector().begin(); itr != elements->getElementsVector().end(); ++itr ){
    //for (Element* itr : elements->getElementsVector()){
    for (int i = 0; i < elements->m_elementsVector.size(); ++i){
        //currentBar = elements->m_elementsVector[i]->getBar();
        ///if ( (*itr)->m_type == CHORD ) {
        //if ( itr->m_type == CHORD ) {
        if ( elements->m_elementsVector[i]->m_type == CHORD ) {
            ///ChordObject = dynamic_cast<ocx::Chord*>( *itr );
            //ChordObject = dynamic_cast<ocx::Chord*>( itr );
            ChordObject = dynamic_cast<ocx::Chord*>( elements->m_elementsVector[i] );
            m_vectorFretTrails.push_back(new FretTrail(m_sceneMgr, m_fretGuideNode, ChordObject->getBeginFret(), ChordObject->getRelativeTimePosition(), (ChordObject->getEndFret() - ChordObject->getBeginFret() + 1), ChordObject->getValue() ));
            currentTrailBeginFret = ChordObject->getBeginFret();
            currentTrailSize = (ChordObject->getEndFret() - ChordObject->getBeginFret() + 1);
            currentEndPostition = (ChordObject->getAbsoluteTimePosition() - (ChordObject->getValue() * SceneSettings::barScale));
            if(elements->m_elementsVector[i+1] != nullptr ){
                m_vectorFretTrails[i]->setAbsoluteLength(elements->m_elementsVector[i+1]->getAbsoluteTimePosition() - elements->m_elementsVector[i]->getAbsoluteTimePosition());
            }

        ///} else if ( (*itr)->m_type == NOTE ) {
        //} else if ( itr->m_type == NOTE ) {
        } else if ( elements->m_elementsVector[i]->m_type == NOTE ) {
            ///NoteObject = dynamic_cast<ocx::Note*>( *itr );
            //NoteObject = dynamic_cast<ocx::Note*>( itr );
            NoteObject = dynamic_cast<ocx::Note*>( elements->m_elementsVector[i] );
            m_vectorFretTrails.push_back(new FretTrail(m_sceneMgr, m_fretGuideNode, NoteObject->getFret(), NoteObject->getRelativeTimePosition(), 1, NoteObject->getValue() ));
            //if(currentBar = elements->m_elementsVector[i+1]->getBar()!= currentBar){

            //}
        }

        ///PreviousElementObject = *itr;
        PreviousElementObject = elements->m_elementsVector[i];
        while((m_vectorBars[currentBar]->getAbsoluteTimePosition() <= currentBeginPosition)
              && (m_vectorBars[currentBar]->getAbsoluteTimePosition() > currentEndPostition)){

            if( currentBar <= SceneSettings::barCount + 2 ) {
                m_vectorBars[currentBar]->setBeginFret(currentTrailBeginFret);
                m_vectorBars[currentBar]->setWidth(currentTrailSize);

                currentBeginPosition = ChordObject->getAbsoluteTimePosition();
                currentBar++;
            }
        }
    }
}
