cmake_minimum_required(VERSION 3.25)
project(RavelEngine_API LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

option(BUILD_TEST "Build as exe" OFF)

SET(COMPILE_DEFINES WIN32
)

add_compile_definitions(${COMPILE_DEFINES})

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Source)

if(BUILD_TEST)
set_target_properties(RavelEngine_API PROPERTIES 
						VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Build_Test/${build_location}/$<CONFIG>
						VS_DEBUGGER_COMMAND ${CMAKE_SOURCE_DIR}/Build_Test/${build_location}/$<CONFIG>/RavelEngine.exe
						MSVC_DEBUG_INFORMATION_FORMAT ProgramDatabase
						VS_STARTUP_PROJECT RavelEngine_API
						RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Build_Test/${build_location}/)
						
set(LIB DirectXTK.lib
		lua5.4.lib
		opengl32.lib
		glew32.lib
		glfw3dll.lib
		XINPUT9_1_0.lib
)

target_link_libraries(RavelEngine_API ${LIB})

else()
set_target_properties(RavelEngine_API PROPERTIES 
						VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/API_Build/$<CONFIG>/
						MSVC_DEBUG_INFORMATION_FORMAT ProgramDatabase
						ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Build/
						)
set(CMAKE_LIBRARY_OUTPUT "${CMAKE_SOURCE_DIR}/Build/")
endif()
		


target_compile_options(RavelEngine_API PRIVATE /W3 /sdl /MP /Od /Ob0 /Gy /GR)

target_link_options(RavelEngine_API PRIVATE /DEBUG /LARGEADDRESSAWARE /OPT:REF /OPT:ICF /SUBSYSTEM:WINDOWS)

