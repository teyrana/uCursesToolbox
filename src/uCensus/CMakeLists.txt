#--------------------------------------------------------
# The CMakeLists.txt for:                     pXRelayTest
# Author(s):                                Mike Benjamin
#--------------------------------------------------------

# Set System Specific Libraries

SET(EXE uCensus)

SET(SRC
    curses-input-handler.cpp
    curses-renderer.cpp
    display-column.cpp
    track-cache.cpp
    track-monitor.cpp
    track-monitor-info.cpp
    report.cpp
    track.cpp
    main.cpp
)

ADD_EXECUTABLE(${EXE} ${SRC})

target_compile_definitions(${EXE} PRIVATE DEBUG=1)

TARGET_LINK_LIBRARIES(${EXE} PRIVATE
    ${SYSTEM_LIBS}
    ${CURSES_LIBRARIES}
    ${MOOS_LIBRARIES}
    # ${MOOS_IVP_LIBRARIES}
    ${PROJ_LIBRARIES}
    genutil
    mbutil
    apputil)

TARGET_COMPILE_OPTIONS(${EXE} PRIVATE -Wall)
