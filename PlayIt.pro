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
    AdvancedOgreFramework.hpp \
    AppStateManager.hpp \
    DotSceneLoader.hpp \
    Dependencies/rapidxml/rapidxml.hpp \
    Dependencies/rapidxml/rapidxml_iterators.hpp \
    Dependencies/rapidxml/rapidxml_print.hpp \
    Dependencies/rapidxml/rapidxml_utils.hpp \
    Scenes/AppState.hpp \
    Scenes/MenuState.hpp \
    Scenes/PauseState.hpp \
    Scenes/PerformanceState.hpp \
    Scenes/SongListState.hpp \
    Scenes/PerformanceScene/Bars.h \
    Scenes/PerformanceScene/FingerPlacement.h \
    Scenes/PerformanceScene/FretGuide.h \
    Scenes/PerformanceScene/Chord.h \
    Scenes/PerformanceScene/NotationFileParser.h \
    Scenes/PerformanceScene/Note.h \
    Scenes/PerformanceScene/SceneSettings.h \
    Scenes/PerformanceScene/Staff.h \
    Scenes/PerformanceScene/Strings.h \
    Scenes/SongListScene/SongInfo.h \
    PlayIt.hpp \
    Scenes/PerformanceScene/Targets.h \
    Scenes/PerformanceScene/Elements.h \
    Scenes/PerformanceScene/Neck.h


SOURCES += \
    AdvancedOgreFramework.cpp \
    AppStateManager.cpp \
    DotSceneLoader.cpp \
    main.cpp \
    Scenes/MenuState.cpp \
    Scenes/PauseState.cpp \
    Scenes/PerformanceState.cpp \
    Scenes/SongListState.cpp \
    Scenes/PerformanceScene/Bars.cpp \
    Scenes/PerformanceScene/FingerPlacement.cpp \
    Scenes/PerformanceScene/FretGuide.cpp \
    Scenes/PerformanceScene/Chord.cpp \
    Scenes/PerformanceScene/NotationFileParser.cpp \
    Scenes/PerformanceScene/Note.cpp \
    Scenes/PerformanceScene/SceneSettings.cpp \
    Scenes/PerformanceScene/Staff.cpp \
    Scenes/PerformanceScene/Strings.cpp \
    Scenes/SongListScene/SongInfo.cpp \
    PlayIt.cpp \
    Scenes/PerformanceScene/Targets.cpp \
    Scenes/PerformanceScene/Elements.cpp \
    Scenes/PerformanceScene/Neck.cpp
