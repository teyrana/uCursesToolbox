#--------------------------------------------------------
# The CMakeLists.txt for:                     pXRelayTest
# Author(s):                                Mike Benjamin
#--------------------------------------------------------

# Set System Specific Libraries

SET(EXE uCensus)

SET(SRC
    CursesInputHandler.cpp
    CursesRenderer.cpp
    TrackCache.cpp
    TrackMonitor.cpp
    TrackMonitorInfo.cpp
    Report.cpp
    Track.cpp
    main.cpp
)

ADD_EXECUTABLE(${EXE} ${SRC})

# Linux and Apple Libraries
SET(SYSTEM_LIBS
  m
  pthread )


TARGET_LINK_LIBRARIES(${EXE} PRIVATE
    ${SYSTEM_LIBS}
    ${CURSES_LIBRARIES}
    ${MOOS_LIBRARIES}
    # ${MOOS_IVP_LIBRARIES})
    genutil
    mbutil
    apputil)

SET_PROPERTY(TARGET ${EXE} PROPERTY CXX_STANDARD 11)

TARGET_COMPILE_OPTIONS(${EXE} PRIVATE -Wall)
