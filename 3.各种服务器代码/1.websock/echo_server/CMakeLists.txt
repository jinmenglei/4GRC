cmake_minimum_required(VERSION 3.10)
# Initialize target.
macro (init_target NAME)
  set (TARGET_NAME ${NAME})
	message ("** " ${TARGET_NAME})

  # Include our own module path. This makes #include "x.h"
  # work in project subfolders to include the main directory headers.
	include_directories (${CMAKE_CURRENT_SOURCE_DIR} )
	include_directories ( ${WEBSOCKETPP_LIB}  )
endmacro ()
# Build executable for executables
set(EBSOCKETPP_BOOST_LIBS,"/usr/local/lib")
macro (build_executable TARGET_NAME)
  set (TARGET_LIB_TYPE "EXECUTABLE")
  message (STATUS "-- Build Type:")
  message (STATUS "       " ${TARGET_LIB_TYPE})

  add_executable (${TARGET_NAME} ${ARGN})

	include_directories (${WEBSOCKETPP_ROOT} ${WEBSOCKETPP_INCLUDE})

	target_link_libraries(${TARGET_NAME} ${WEBSOCKETPP_PLATFORM_LIBS} ${WEBSOCKETPP_BOOST_LIBS}/libboost_chrono.a ${WEBSOCKETPP_BOOST_LIBS}/libboost_system.a ${WEBSOCKETPP_BOOST_LIBS}/libboost_random.a)

  #    set_target_properties (${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY /Users/yin/code/go_proj/src/aggregated-exchange/)
	set_target_properties (${TARGET_NAME} PROPERTIES DEBUG_POSTFIX d)
endmacro ()

# Build executable and register as test
macro (build_test TARGET_NAME)
  build_executable (${TARGET_NAME} ${ARGN})

  if (${CMAKE_VERSION} VERSION_LESS 3)
	  message(WARNING "CMake too old to register ${TARGET_NAME} as a test")
  else ()
	  add_test(NAME ${TARGET_NAME} COMMAND $<TARGET_FILE:${TARGET_NAME}>)
	endif ()
endmacro ()

# Finalize target for all types
macro (final_target)
  if ("${TARGET_LIB_TYPE}" STREQUAL "EXECUTABLE")
    install (TARGETS ${TARGET_NAME}
    RUNTIME DESTINATION "bin"
	  CONFIGURATIONS ${CMAKE_CONFIGURATION_TYPES})
	endif ()

  install (DIRECTORY ${CMAKE_SOURCE_DIR}/${TARGET_NAME}
	DESTINATION include/
	FILES_MATCHING PATTERN "*.hpp*")
endmacro ()

macro (link_boost)
  target_link_libraries (${TARGET_NAME} ${Boost_LIBRARIES})
	set_property(TARGET ${TARGET_NAME} APPEND PROPERTY INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
endmacro ()

macro (link_openssl)
  target_link_libraries (${TARGET_NAME} ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY})
  set_property(TARGET ${TARGET_NAME} APPEND PROPERTY INCLUDE_DIRECTORIES ${OPENSSL_INCLUDE_DIR})
endmacro ()

macro (link_zlib)
  target_link_libraries (${TARGET_NAME} ${ZLIB_LIBRARIES})
	set_property(TARGET ${TARGET_NAME} APPEND PROPERTY INCLUDE_DIRECTORIES ${ZLIB_INCLUDE_DIR})
endmacro ()

macro (include_subdirs PARENT)
  file (GLOB SDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${PARENT}/*")
  foreach (SUBDIR ${SDIRS})
	  if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR}/CMakeLists.txt")
		  add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR}")
		endif ()
  endforeach ()
endmacro()

set(WEBSOCKETPP_LIB /root/websocketpp )
file (GLOB SOURCE_FILES *.cpp)
file (GLOB HEADER_FILES *.hpp)

init_target (echo_server)
build_executable (${TARGET_NAME} ${SOURCE_FILES} ${HEADER_FILES})

link_boost ()
final_target ()

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "examples")
