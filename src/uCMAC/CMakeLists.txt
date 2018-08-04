#--------------------------------------------------------
# The CMakeLists.txt for:                           uCMAC
# Author(s):               Mike Benjamin, Daniel Williams
#--------------------------------------------------------

SET(SRC
    AppCastMonitor.cpp
    AppCastMonitor_Info.cpp
    main.cpp
)

SET(EXE uCMAC)

ADD_EXECUTABLE(${EXE} ${SRC})

TARGET_LINK_LIBRARIES(${EXE}
    ${SYSTEM_LIBS}
    ${CURSES_LIBRARIES}
    ${MOOS_LIBRARIES}
    genutil
    mbutil
    apputil
    m
    pthread)
