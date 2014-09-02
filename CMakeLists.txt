cmake_minimum_required(VERSION 2.8)
# Specify default build type if none provided (before project() command)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# For generators with multiple configurations (like VS), only allow Debug and Release
if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited configurations" FORCE)
	mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
endif()
project("Pulsip")

add_definitions(-DPULSIP_EXPORTS)
include_directories(${PROJECT_SOURCE_DIR}/Pulsip/include)

set(PULSIP_SHARED_LIBS TRUE CACHE BOOL "Build shared libraries (use shared SFML librares)")
set(PULSIP_BUILD_EXAMPLES FALSE CACHE BOOL "Build example projects")
set(PULSIP_BUILD_DOC FALSE CACHE BOOL "Create HTML documentation (requires Doxygen)")

if(WIN32)
	set(PULSIP_STATIC_STD_LIBS FALSE CACHE BOOL "Use statically linked standard/runtime libraries? This option must match the one used for SFML.")

	# Determine whether we're dealing with a TDM compiler or not
	if(CMAKE_COMPILER_IS_GNUCXX)
		execute_process(COMMAND "${CMAKE_CXX_COMPILER}" "--version" OUTPUT_VARIABLE GCC_COMPILER_VERSION)
		string(REGEX MATCHALL ".*(tdm[64]*-[1-9]).*" COMPILER_GCC_TDM "${GCC_COMPILER_VERSION}")
	endif()

	# Modify compiler flags globally
	if(PULSIP_STATIC_STD_LIBS)
		if(PULSIP_SHARED_LIBS)
			message("\n-> PULSIP_STATIC_STD_LIBS and PULSIP_SHARED_LIBS are not compatible.")#err?
			message("-> They lead to multiple runtime environments which result in undefined behavior.\n")
		elseif(MSVC)
			foreach(flag CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE)
				if(${flag} MATCHES "/MD")
					string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
				endif()
			endforeach()
		elseif(CMAKE_COMPILER_IS_GNUCXX AND NOT COMPILER_GCC_TDM)
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
		endif()
	elseif(COMPILER_GCC_TDM)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -shared-libgcc -shared-libstdc++")
	endif()
endif()

# Compiler-specific flags and definitions
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -stdlib=libc++")
endif()


# Variable for install directory
if(UNIX)
	set(PULSIP_EXAMPLE_INSTALL_DIR share/Pulsip)
	set(PULSIP_DOC_INSTALL_DIR share/doc/Pulsip)
else()
	set(PULSIP_EXAMPLE_INSTALL_DIR .)
	set(PULSIP_DOC_INSTALL_DIR .)
endif()


# Add directory containing FindSFML.cmake to module path
set (CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules/;${CMAKE_MODULE_PATH}")


# Find SFML
if(NOT PULSIP_SHARED_LIBS)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()
find_package(SFML 2 COMPONENTS graphics window system)

if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
else()
	set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
	message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
	message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()


# Macro to link SFML
macro(pulsip_link_sfml PULSIP_TARGET)
	target_link_libraries(${PULSIP_TARGET} ${SFML_LIBRARIES})
endmacro()

# Documentation
if(PULSIP_BUILD_DOC)
	add_subdirectory(doc)
endif()


# C++ source code
add_subdirectory(Pulsip/src)

if(PULSIP_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()


# Install include directory and license files
install(DIRECTORY Pulsip/include
		DESTINATION .)

install(FILES license.txt
		RENAME license-pulsip.txt
		DESTINATION ${PULSIP_DOC_INSTALL_DIR})
