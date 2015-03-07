#Fing gtest
find_package(GTest)
if(GTEST_FOUND)
	include_directories(${GTEST_INCLUDE_DIRS})
else()
	set(GTEST_ROOT "" CACHE PATH "GTest top-level directory")
	message("\n-> GTest directory not found. Set GTEST_ROOT to GTest's top-level path (containing \"include\" and \"lib\" directories).")
endif()

#Include Pulsip and SFML
include_directories (${PULSIP_INCLUDE_DIRS}
                     ${SFML_INCLUDE_DIRS}
                     )
add_executable(PulsipTest main.cpp)
target_link_libraries (PulsipTest
                       ${PULSIP_LIB}
                       ${SFML_LIBRARIES}
                       ${GTEST_LIBRARIES}
                       )
enable_testing()
add_test(NAME PulsipTest COMMAND PulsipTest)