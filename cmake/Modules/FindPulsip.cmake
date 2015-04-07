# This script locates the Pulsip library
# Based on FindSFML.cmake module
#
# Usage
# -----
# Pulsip's libraries use the same configuration (static/dynamic linking) as SFML's.
# If the variable SFML_STATIC_LIBRARIES is set to TRUE before calling find_package(Pulsip),
# the static libraries of Pulsip are found. Otherwise, the dynamic ones are found. 
#
# Output
# ------
#
# This script defines the following variables:
# - PULSIP_LIBRARY_DEBUG:   the name of the debug library (set to PULSIP_LIBRARY_RELEASE if no debug version is found)
# - PULSIP_LIBRARY_RELEASE: the name of the release library (set to PULSIP_LIBRARY_DEBUG if no release version is found)
# - PULSIP_LIBRARY:         the name of the library to link to(includes both debug and release names if necessary)
# - PULSIP_FOUND:        true if at least one of the debug or release libraries are found
# - PULSIP_INCLUDE_DIR:  the path where Pulsip headers are located (the directory containing the Pulsip/Config.hpp file)

# Deduce the libraries suffix from the options
set(FINDPULSIP_LIB_SUFFIX "")
if(SFML_STATIC_LIBRARIES)
	set(FINDPULSIP_LIB_SUFFIX "-s")
endif()

# Find the Pulsip include directory
find_path(PULSIP_INCLUDE_DIR Pulsip/Config.hpp
		  PATH_SUFFIXES include
		  PATHS
		  ${PULSIP_ROOT}
		  $ENV{PULSIP_ROOT}
		  /usr/local/
		  /usr/
		  /sw          # Fink
		  /opt/local/  # DarwinPorts
		  /opt/csw/    # Blastwave
		  /opt/)

# Find the requested modules
set(FINDPULSIP_LIB_PATHS
	${PULSIP_ROOT}
	$ENV{PULSIP_ROOT}
	/usr/local
	/usr
	/sw
	/opt/local
	/opt/csw
	/opt)

# Debug library
find_library(PULSIP_LIBRARY_DEBUG
			 NAMES Pulsip${FINDPULSIP_LIB_SUFFIX}-d
			 PATH_SUFFIXES lib64 lib
			 PATHS ${FINDPULSIP_LIB_PATHS})

# Release library
find_library(PULSIP_LIBRARY_RELEASE
			 NAMES Pulsip${FINDPULSIP_LIB_SUFFIX}
			 PATH_SUFFIXES lib64 lib
			 PATHS ${FINDPULSIP_LIB_PATHS})

if(PULSIP_LIBRARY_DEBUG OR PULSIP_LIBRARY_RELEASE)
	# Library found
	set(PULSIP_FOUND TRUE)

	# If both are found, set PULSIP_LIBRARY to contain both
	if(PULSIP_LIBRARY_DEBUG AND PULSIP_LIBRARY_RELEASE)
		set(PULSIP_LIBRARY debug	 ${PULSIP_LIBRARY_DEBUG}
						 optimized ${PULSIP_LIBRARY_RELEASE})
	endif()

	# If only one debug/release variant is found, set the other to be equal to the found one
	if(PULSIP_LIBRARY_DEBUG AND NOT PULSIP_LIBRARY_RELEASE)
		# debug and not release
		set(PULSIP_LIBRARY_RELEASE ${PULSIP_LIBRARY_DEBUG})
		set(PULSIP_LIBRARY		 ${PULSIP_LIBRARY_DEBUG})
	endif()
	if(PULSIP_LIBRARY_RELEASE AND NOT PULSIP_LIBRARY_DEBUG)
		# release and not debug
		set(PULSIP_LIBRARY_DEBUG ${PULSIP_LIBRARY_RELEASE})
		set(PULSIP_LIBRARY	   ${PULSIP_LIBRARY_RELEASE})
	endif()
else()
	# Library not found
	set(PULSIP_FOUND FALSE)
	set(PULSIP_LIBRARY "")
	set(FINDPULSIP_MISSING "${FINDPULSIP_MISSING} PULSIP_LIBRARY")
endif()

# Mark variables as advanced
mark_as_advanced(PULSIP_INCLUDE_DIR
				 PULSIP_LIBRARY
				 PULSIP_LIBRARY_RELEASE
				 PULSIP_LIBRARY_DEBUG)

# Result
if(PULSIP_FOUND)
	# Success
	message(STATUS "Found Pulsip: ${PULSIP_INCLUDE_DIR}")
else()
	# include directory or library not found
	set(FINDPULSIP_ERROR "Could NOT find Pulsip (missing: ${FINDPULSIP_MISSING})")

	if(PULSIP_FIND_REQUIRED)
		# Fatal error
		message(FATAL_ERROR ${FINDPULSIP_ERROR})
	elseif(NOT PULSIP_FIND_QUIETLY)
		# Error, but continue
		message("${FINDPULSIP_ERROR}")
	endif()
endif()
