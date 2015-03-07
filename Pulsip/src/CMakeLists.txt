
# C++ source files
set(PULSIP_SRC
	QuadTree.cpp
    QuadTreeNode.cpp
    QuadTreeOccupant.cpp
)


# Library to build
set(PULSIP_LIB ${PROJECT_NAME})


# Determine library suffixes depending on static/shared configuration
if(PULSIP_SHARED_LIBS)
	add_library(${PULSIP_LIB} SHARED ${PULSIP_SRC})
	set_target_properties(${PULSIP_LIB} PROPERTIES DEBUG_POSTFIX -d)
	pulsip_link_sfml(${PULSIP_LIB})
else()
	add_definitions(-DSFML_STATIC)
	add_library(${PULSIP_LIB} STATIC ${PULSIP_SRC})
	set_target_properties(${PULSIP_LIB} PROPERTIES DEBUG_POSTFIX -s-d)
	set_target_properties(${PULSIP_LIB} PROPERTIES RELEASE_POSTFIX -s)
endif()


# Install (use "bin" folder for DLL, "lib" for SO files)
if(WIN32)
	install(TARGETS ${PULSIP_LIB}
			RUNTIME DESTINATION bin
			LIBRARY DESTINATION lib
			ARCHIVE DESTINATION lib)
else()
	install(TARGETS ${PULSIP_LIB}
			RUNTIME DESTINATION lib
			LIBRARY DESTINATION lib
			ARCHIVE DESTINATION lib)
endif()
