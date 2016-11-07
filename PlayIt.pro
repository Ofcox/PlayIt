TEMPLATE = app
#CONFIG += console
#CONFIG -= app_bundle
CONFIG -= qt

#CONFIG += c++11

DEFINES -= UNICODE

unix {
    # You may need to change this include directory
    INCLUDEPATH += /usr/include/OGRE
    CONFIG += link_pkgconfig
    PKGCONFIG += OGRE
}


win32 {

    LIBS *= user32.lib
    LIBS += -L$(OGRE_HOME)\\boost\lib

    release:LIBS += -L$(OGRE_HOME)\\lib\\release
    debug:LIBS += -L$(OGRE_HOME)\\lib\\debug

    INCLUDEPATH += $(OGRE_HOME)\\include
    INCLUDEPATH += $(OGRE_HOME)\\include\OIS
    INCLUDEPATH += $(OGRE_HOME)\\include\OGRE
    INCLUDEPATH += $(OGRE_HOME)\\boost
    #INCLUDEPATH += D:\Libraries\OGRE-SDK-1.9.0-vc140-x64-12.03.2016\boost
    # If you are using Ogre 1.9 also include the following line:
    INCLUDEPATH += $(OGRE_HOME)\\include\OGRE\Overlay
}

debug {
    #LIBS += -L$(OGRE_HOME)\\lib\debug -lOgreMain_d -lOIS_d -lOgreOverlay_d
    TARGET = $$join(TARGET,,,d)
    #LIBS *= -lOgreMain_d -lOIS_d
    # If you are using Ogre 1.9 also include -lOgreOverlay_d, like this:
    LIBS *= -lOgreMain_d -lOIS_d -lOgreOverlay_d -lOgrePaging_d -lOgreTerrain_d
}
release {
    #LIBS += -L$(OGRE_HOME)\\lib\Release -lOgreMain -lOIS -lOgreOverlay
    LIBS *= -lOgreMain -lOIS
    # If you are using Ogre 1.9 also include -lOgreOverlay, like this:
    LIBS *= -lOgreMain -lOIS -lOgreOverlay
}

DISTFILES += \
    Project.txt

HEADERS += \
    dependencies/rapidxml/rapidxml.hpp \
    dependencies/rapidxml/rapidxml_iterators.hpp \
    dependencies/rapidxml/rapidxml_print.hpp \
    dependencies/rapidxml/rapidxml_utils.hpp \
    states/PerformanceScene/bars.h \
    states/PerformanceScene/FingerGuide.h \
    states/PerformanceScene/fretguide.h \
    states/PerformanceScene/performancescene.h \
    states/PerformanceScene/SceneSettings.h \
    states/PerformanceScene/strings.h \
    states/AppState.hpp \
    states/lang_cz.h \
    states/MenuState.hpp \
    states/PauseState.hpp \
    states/PerformanceState.hpp \
    states/SongListState.hpp \
    AdvancedOgreFramework.hpp \
    AppStateManager.hpp \
    DemoApp.hpp \
    DotSceneLoader.hpp \
    FingerPlacement.h \
    NotationFileParser.h \
    SongInfo.h \
    Chord.h \
    Note.h \
    Staff.h

SOURCES += \
    states/PerformanceScene/bars.cpp \
    states/PerformanceScene/fretguide.cpp \
    states/PerformanceScene/performancescene.cpp \
    states/PerformanceScene/SceneSettings.cpp \
    states/PerformanceScene/strings.cpp \
    states/MenuState.cpp \
    states/PauseState.cpp \
    states/PerformanceState.cpp \
    states/SongListState.cpp \
    AdvancedOgreFramework.cpp \
    AppStateManager.cpp \
    DemoApp.cpp \
    DotSceneLoader.cpp \
    FingerPlacement.cpp \
    main.cpp \
    NotationFileParser.cpp \
    SongInfo.cpp \
    Chord.cpp \
    Note.cpp \
    Staff.cpp
