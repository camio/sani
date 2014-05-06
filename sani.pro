NAME=sani
include( ../smake/lib.pri )

## Dependencies

addBoostDependency($$BOOST_PATH)
addStaticLibDependency($$SBASE_PATH,sbase)

## Sources

SOURCES += src/sani_animation.cpp
SOURCES += src/sani_drawing.cpp
SOURCES += src/sani_interactiveanimation.cpp
HEADERS += include/sani/interactiveanimationview.hpp
SOURCES += src/sani_interactiveanimationview.cpp
SOURCES += src/sani_userinput.cpp

## Build Options

QT += opengl svg
