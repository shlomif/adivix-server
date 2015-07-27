CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT (adivix-server)

INCLUDE(FindThreads)

SET (exe "adivix-server")
ADD_EXECUTABLE ("${exe}" srv.c daemon.c util.c signal.c test/test.c C-Thread-Pool/thpool.c)

IF (CMAKE_USE_PTHREADS_INIT)
    TARGET_LINK_LIBRARIES("${exe}" "pthread")
ENDIF (CMAKE_USE_PTHREADS_INIT)

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/adivix")
