NAME=sani
include( ../smake/lib.pri )

## Dependencies

addBoostDependency($$BOOST_PATH)
addStaticLibDependency($$SBASE_PATH,sbase)

## Sources

# SOURCES += src/sani_animation.cpp
# SOURCES += src/sani_brushinternalsmodule.cpp
# SOURCES += src/sani_brushpattern.cpp
# SOURCES += src/sani_colorinternalsmodule.cpp
# SOURCES += src/sani_colorinternalsmodule.t.cpp
SOURCES += src/sani_drawing.cpp
# SOURCES += src/sani_drawinginternalsmodule.cpp
# SOURCES += src/sani_fontinternalsmodule.cpp
# SOURCES += src/sani_interactiveanimation.cpp
# HEADERS += include/sani/interactiveanimationview.hpp
# SOURCES += src/sani_interactiveanimationview.cpp
# SOURCES += src/sani_interactiveanimationview.t.cpp
# SOURCES += src/sani_matrix33internalsmodule.cpp
# SOURCES += src/sani_matrix33internalsmodule.t.cpp
# SOURCES += src/sani_modules.cpp
# SOURCES += src/sani_pencapstyle.cpp
# SOURCES += src/sani_peninternalsmodule.cpp
# SOURCES += src/sani_penjoinstyle.cpp
# SOURCES += src/sani_penstyle.cpp
# SOURCES += src/sani_rectinternalsmodule.cpp
# SOURCES += src/sani_tests.cpp
# SOURCES += src/sani_userinput.cpp
# HEADERS += include/sani/valueselector.hpp
# SOURCES += src/sani_valueselector.cpp
# SOURCES += src/sani_valueselectorstate.cpp
# SOURCES += src/sani_valueselectorstateserialize.cpp

## Build Options

QT += opengl svg
