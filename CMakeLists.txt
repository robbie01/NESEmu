cmake_minimum_required(VERSION 3.5)
project(NESEmu)

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${NESEmu_SOURCE_DIR}/cmake")
# Set an output directory for our binaries
set(BIN_DIR ${NESEmu_SOURCE_DIR}/bin)

# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g -gdwarf-2")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (MSVC)
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

file(GLOB NESEmu_SRC "${NESEmu_SOURCE_DIR}/src/*.cpp")
find_package(SFML 2 COMPONENTS system window graphics audio)
add_executable(NESEmu ${NESEmu_SRC})
set_property(TARGET NESEmu PROPERTY CXX_STANDARD 11)
target_include_directories(NESEmu PRIVATE ${SFML_INCLUDE_DIR} include)
target_link_libraries(NESEmu ${SFML_LIBRARIES})

install(TARGETS NESEmu RUNTIME DESTINATION ${BIN_DIR})
