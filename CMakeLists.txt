cmake_minimum_required(VERSION 3.0.0)
project(ezloml VERSION 0.0.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_definitions(-DVISUAL_DEBUG=1)

IF(AUTO_BUILDING)
    add_definitions(-DIS_RELEASE_BUILD=1)
ENDIF(AUTO_BUILDING)

option(DEBUG_OPTION "DEBUG_OPTION" OFF)
if(DEBUG_OPTION)
    set(BUILD_TYPE "Debug")
    message("Compiling in Debug mode....")
    set(GCC_COVERAGE_COMPILE_FLAGS "-O1  -g3 -pthread -Wall -Wno-format -w")
    add_definitions(-DWITHGPERFTOOLS=1)
else()
    set(BUILD_TYPE "Release")
    message("Compiling in Release mode....")
    set(GCC_COVERAGE_COMPILE_FLAGS "-pthread -s -Wall -Wno-format -w")
endif()

SET(requiredlibs)
FIND_PACKAGE(CURL)
IF(CURL_FOUND)
  INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR})
  SET(requiredlibs ${requiredlibs} ${CURL_LIBRARIES} )
ELSE(CURL_FOUND)
  MESSAGE(FATAL_ERROR "Could not find the CURL library and development files.")
ENDIF(CURL_FOUND)

set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS} -no-pie -Wno-psabi" )
set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )

find_package(PkgConfig REQUIRED)




############################# curl-test #############################

add_executable(curl-test curl_test.cpp )
#-------------------------------------------------------------------------------------
#--------------------------------- LINKLIBS ------------------------------------------
#-------------------------------------------------------------------------------------
set(LINKLIBS_CURL
    stdc++
    c    
    curl    
    ssl
)
# target_link_libraries(micro_kernel ${LINKLIBS})
# target_link_libraries(ha-vidood ${LINKLIBS})
target_link_libraries(curl-test ${LINKLIBS_CURL})
