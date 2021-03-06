CMAKE_MINIMUM_REQUIRED(VERSION 3.5.0)
PROJECT(misc CXX)
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

# directories
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# rpath
SET(CMAKE_INSTALL_RPATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
IF(RPATH)
	SET(CMAKE_INSTALL_RPATH "${RPATH}:${CMAKE_INSTALL_RPATH}")
ENDIF(RPATH)
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

# include & link
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/lib)

# HDF5
IF(WITH_HDF5)
	ADD_DEFINITIONS(-DIOER_WITH_HDF5)
	FIND_PACKAGE(HDF5 COMPONENTS CXX)
	INCLUDE_DIRECTORIES(${HDF5_INCLUDE_DIRS})
ENDIF(WITH_HDF5)

# test
ENABLE_TESTING()

# sub directories
ADD_SUBDIRECTORY(include)
ADD_SUBDIRECTORY(misc_test)
