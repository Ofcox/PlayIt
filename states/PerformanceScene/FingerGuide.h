//#ifndef FINGERGUIDE_H
//#define FINGERGUIDE_H


//class FingerGuide
//{
//public:
//    FingerGuide();
//    int m_beginFret;
//    int m_endFret;
//    int m_size;
//    // struny jsou proto, ze jeden prst muze drzet vice strun, zatimco dalsi nemusi byt zapojeny
//    // je jednodussi vyznacit, ktere struny drzi jaky prst
//    int m_strings[4];

//    xml_document<>      doc;
//    xml_node<>*         root_node;
//    int fingerGuideSize;

//    FingerGuide(){
//        xml_node<>* currentNode = root_node->first_node("fingerPattern")->first_node("finger");
//        while (currentNode !=NULL ){

//            chords.push_back(new ChordDefinition(currentNode->first_attribute("name")->value(),
//                                                 currentNode->first_attribute("englishName")->value(),
//                                                 currentNode->first_attribute("germanName")->value(),
//                                                 std::stoi(currentNode->first_attribute("string4")->value()),
//                                                 std::stoi(currentNode->first_attribute("string3")->value()),
//                                                 std::stoi(currentNode->first_attribute("string2")->value()),
//                                                 std::stoi(currentNode->first_attribute("string1")->value())) );
//           // jump to next element
//           currentNode = currentNode->next_sibling();
//        };
//    }

//    int fingerGuideSize;




//}

#endif // FINGERGUIDE_H
