set(HEADER_FILES_COMPONENT "")
set(SOURCE_FILES_COMPONENT "")
set(HEADER_FILES_BEHAVIOUR "")
set(SOURCE_FILES_BEHAVIOUR "")
set(HEADER_FILES_CONTROLLER "")
set(SOURCE_FILES_CONTROLLER "")
set(HEADER_FILES_GAMEOBJECT "")
set(SOURCE_FILES_GAMEOBJECT "")
set(HEADER_FILES_GAMESTATEMANAGER "")
set(SOURCE_FILES_GAMESTATEMANAGER "")
set(HEADER_FILES_MATH "")
set(SOURCE_FILES_MATH "")
set(HEADER_FILES_STRUCTURE "")
set(SOURCE_FILES_STRUCTURE "")
set(HEADER_FILES_SYSTEM_AI "")
set(SOURCE_FILES_SYSTEM_AI "")
set(HEADER_FILES_SYSTEM_AI_TASK "")
set(SOURCE_FILES_SYSTEM_AI_TASK "")
set(HEADER_FILES_SYSTEM_COLLISION "")
set(SOURCE_FILES_SYSTEM_COLLISION "")
set(HEADER_FILES_SYSTEM_CORE "")
set(SOURCE_FILES_SYSTEM_CORE "")
set(HEADER_FILES_SYSTEM_DEBUG "")
set(SOURCE_FILES_SYSTEM_DEBUG "")
set(HEADER_FILES_SYSTEM_GRAPHICS "")
set(SOURCE_FILES_SYSTEM_GRAPHICS "")
set(HEADER_FILES_SYSTEM_DX "")
set(SOURCE_FILES_SYSTEM_DX "")
set(HEADER_FILES_SYSTEM_GL "")
set(SOURCE_FILES_SYSTEM_GL "")
set(HEADER_FILES_SYSTEM_INPUT "")
set(SOURCE_FILES_SYSTEM_INPUT "")
set(HEADER_FILES_SYSTEM_MEMORY "")
set(SOURCE_FILES_SYSTEM_MEMORY "")
set(HEADER_FILES_SYSTEM_NAVIGATION "")
set(SOURCE_FILES_SYSTEM_NAVIGATION "")
set(HEADER_FILES_SYSTEM_SCENE "")
set(SOURCE_FILES_SYSTEM_SCENE "")
set(HEADER_FILES_SYSTEM_SCRIPT "")
set(SOURCE_FILES_SYSTEM_SCRIPT "")
set(HEADER_FILES_SYSTEM_SOUND "")
set(SOURCE_FILES_SYSTEM_SOUND "")
set(HEADER_FILES_SYSTEM_TEXT "")
set(SOURCE_FILES_SYSTEM_TEXT "")
set(HEADER_FILES_SYSTEM_TIME "")
set(SOURCE_FILES_SYSTEM_TIME "")
set(HEADER_FILES_SYSTEM_WINDOW "")
set(SOURCE_FILES_SYSTEM_WINDOW "")

add_subdirectory("Base Components")
add_subdirectory(Behaviour)
add_subdirectory(Controller)
add_subdirectory("Game Object")
add_subdirectory("Game State Manager")
add_subdirectory("Math")
add_subdirectory(Structures)
add_subdirectory("Systems\\AI")
add_subdirectory("Systems\\Collision System")
add_subdirectory("Systems\\Core")
add_subdirectory("Systems\\Debug")
add_subdirectory("Systems\\Graphics System")
add_subdirectory("Systems\\Graphics System\\DirectX 11")
add_subdirectory("Systems\\Graphics System\\OpenGL")
add_subdirectory("Systems\\Input")
add_subdirectory("Systems\\Memory System")
add_subdirectory("Systems\\Navigation")
add_subdirectory("Systems\\Scene Management")
add_subdirectory("Systems\\Scripting")
#add_subdirectory("Systems\\Sound System")
add_subdirectory("Systems\\Text System")
add_subdirectory("Systems\\Time")
add_subdirectory("Systems\\Window")

if(BUILD_TEST)
add_executable(RavelEngine_API ${HEADER_FILES_COMPONENT} ${HEADER_FILES_BEHAVIOUR} ${HEADER_FILES_CONTROLLER} ${HEADER_FILES_GAMEOBJECT} ${HEADER_FILES_GAMESTATEMANAGER}
									${HEADER_FILES_MATH} ${HEADER_FILES_STRUCTURE} 
									${HEADER_FILES_SYSTEM_AI} 		${HEADER_FILES_SYSTEM_COLLISION} 	${HEADER_FILES_SYSTEM_CORE}
									${HEADER_FILES_SYSTEM_DEBUG} 	${HEADER_FILES_SYSTEM_GRAPHICS} 	${HEADER_FILES_SYSTEM_DX}
									${HEADER_FILES_SYSTEM_GL}		${HEADER_FILES_SYSTEM_INPUT}		${HEADER_FILES_SYSTEM_AI_TASK}
									${HEADER_FILES_SYSTEM_MEMORY} 	${HEADER_FILES_SYSTEM_NAVIGATION} 	${HEADER_FILES_SYSTEM_SCENE}
									${HEADER_FILES_SYSTEM_SCRIPT} 	${HEADER_FILES_SYSTEM_SOUND} 		${HEADER_FILES_SYSTEM_TEXT}
									${HEADER_FILES_SYSTEM_TIME} 	${HEADER_FILES_SYSTEM_WINDOW}
									${SOURCE_FILES_COMPONENT} ${SOURCE_FILES_BEHAVIOUR} ${SOURCE_FILES_CONTROLLER} ${SOURCE_FILES_GAMEOBJECT} ${SOURCE_FILES_GAMESTATEMANAGER} 
									${SOURCE_FILES_MATH} ${SOURCE_FILES_STRUCTURE}
									${SOURCE_FILES_SYSTEM_AI} 		${SOURCE_FILES_SYSTEM_COLLISION} 	${SOURCE_FILES_SYSTEM_CORE}
									${SOURCE_FILES_SYSTEM_DEBUG} 	${SOURCE_FILES_SYSTEM_GRAPHICS} 	${SOURCE_FILES_SYSTEM_DX}
									${SOURCE_FILES_SYSTEM_GL}		${SOURCE_FILES_SYSTEM_INPUT}		${SOURCE_FILES_SYSTEM_AI_TASK}
									${SOURCE_FILES_SYSTEM_MEMORY} 	${SOURCE_FILES_SYSTEM_NAVIGATION} 	${SOURCE_FILES_SYSTEM_SCENE}
									${SOURCE_FILES_SYSTEM_SCRIPT} 	${SOURCE_FILES_SYSTEM_SOUND} 		${SOURCE_FILES_SYSTEM_TEXT}
									${SOURCE_FILES_SYSTEM_TIME} 	${SOURCE_FILES_SYSTEM_WINDOW}
									DataType.h 
									"${CMAKE_CURRENT_LIST_DIR}/Systems/Factory.h" "${CMAKE_CURRENT_LIST_DIR}/Systems/Factory.cpp" "${CMAKE_CURRENT_LIST_DIR}/Systems/System.h" main.h main.cpp)
else()
add_library(RavelEngine_API STATIC ${HEADER_FILES_COMPONENT} ${HEADER_FILES_BEHAVIOUR} ${HEADER_FILES_CONTROLLER} ${HEADER_FILES_GAMEOBJECT} ${HEADER_FILES_GAMESTATEMANAGER}
									${HEADER_FILES_MATH} ${HEADER_FILES_STRUCTURE} 
									${HEADER_FILES_SYSTEM_AI} 		${HEADER_FILES_SYSTEM_COLLISION} 	${HEADER_FILES_SYSTEM_CORE}
									${HEADER_FILES_SYSTEM_DEBUG} 	${HEADER_FILES_SYSTEM_GRAPHICS} 	${HEADER_FILES_SYSTEM_DX}
									${HEADER_FILES_SYSTEM_GL}		${HEADER_FILES_SYSTEM_INPUT}		${HEADER_FILES_SYSTEM_AI_TASK}
									${HEADER_FILES_SYSTEM_MEMORY} 	${HEADER_FILES_SYSTEM_NAVIGATION} 	${HEADER_FILES_SYSTEM_SCENE}
									${HEADER_FILES_SYSTEM_SCRIPT} 	${HEADER_FILES_SYSTEM_SOUND} 		${HEADER_FILES_SYSTEM_TEXT}
									${HEADER_FILES_SYSTEM_TIME} 	${HEADER_FILES_SYSTEM_WINDOW}
									${SOURCE_FILES_COMPONENT} ${SOURCE_FILES_BEHAVIOUR} ${SOURCE_FILES_CONTROLLER} ${SOURCE_FILES_GAMEOBJECT} ${SOURCE_FILES_GAMESTATEMANAGER} 
									${SOURCE_FILES_MATH} ${SOURCE_FILES_STRUCTURE}
									${SOURCE_FILES_SYSTEM_AI} 		${SOURCE_FILES_SYSTEM_COLLISION} 	${SOURCE_FILES_SYSTEM_CORE}
									${SOURCE_FILES_SYSTEM_DEBUG} 	${SOURCE_FILES_SYSTEM_GRAPHICS} 	${SOURCE_FILES_SYSTEM_DX}
									${SOURCE_FILES_SYSTEM_GL}		${SOURCE_FILES_SYSTEM_INPUT}		${SOURCE_FILES_SYSTEM_AI_TASK}
									${SOURCE_FILES_SYSTEM_MEMORY} 	${SOURCE_FILES_SYSTEM_NAVIGATION} 	${SOURCE_FILES_SYSTEM_SCENE}
									${SOURCE_FILES_SYSTEM_SCRIPT} 	${SOURCE_FILES_SYSTEM_SOUND} 		${SOURCE_FILES_SYSTEM_TEXT}
									${SOURCE_FILES_SYSTEM_TIME} 	${SOURCE_FILES_SYSTEM_WINDOW}
									DataType.h 
									"${CMAKE_CURRENT_LIST_DIR}/Systems/Factory.h" "${CMAKE_CURRENT_LIST_DIR}/Systems/Factory.cpp" "${CMAKE_CURRENT_LIST_DIR}/Systems/System.h")
endif()

source_group("Base Components\\Header Files" FILES ${HEADER_FILES_COMPONENT})
source_group("Base Components\\Source Files" FILES ${SOURCE_FILES_COMPONENT})
source_group("Behaviour\\Header Files" FILES ${HEADER_FILES_BEHAVIOUR})
source_group("Behaviour\\Source Files" FILES ${SOURCE_FILES_BEHAVIOUR})
source_group("Controller\\Header Files" FILES ${HEADER_FILES_CONTROLLER})
source_group("Controller\\Source Files" FILES ${SOURCE_FILES_CONTROLLER})
source_group("Game Object\\Header Files" FILES ${HEADER_FILES_GAMEOBJECT})
source_group("Game Object\\Source Files" FILES ${SOURCE_FILES_GAMEOBJECT})
source_group("Game State Manager\\Header Files" FILES ${HEADER_FILES_GAMESTATEMANAGER})
source_group("Game State Manager\\Source Files" FILES ${SOURCE_FILES_GAMESTATEMANAGER})
source_group("Math\\Header Files" FILES ${HEADER_FILES_MATH})
source_group("Math\\Source Files" FILES ${SOURCE_FILES_MATH})
source_group("Structures\\Header Files" FILES ${HEADER_FILES_STRUCTURE})
source_group("Structures\\Source Files" FILES ${SOURCE_FILES_STRUCTURE})

source_group("Systems\\AI\\Header Files" FILES ${HEADER_FILES_SYSTEM_AI})
source_group("Systems\\AI\\Source Files" FILES ${SOURCE_FILES_SYSTEM_AI})
source_group("Systems\\AI\\Task\\Header Files" FILES ${HEADER_FILES_SYSTEM_AI_TASK})
source_group("Systems\\AI\\Task\\Source Files" FILES ${SOURCE_FILES_SYSTEM_AI_TASK})
source_group("Systems\\Collision System\\Header Files" FILES ${HEADER_FILES_SYSTEM_COLLISION})
source_group("Systems\\Collision System\\Source Files" FILES ${SOURCE_FILES_SYSTEM_COLLISION})
source_group("Systems\\Core\\Header Files" FILES ${HEADER_FILES_SYSTEM_CORE})
source_group("Systems\\Core\\Source Files" FILES ${SOURCE_FILES_SYSTEM_CORE})
source_group("Systems\\Debug\\Header Files" FILES ${HEADER_FILES_SYSTEM_DEBUG})
source_group("Systems\\Debug\\Source Files" FILES ${SOURCE_FILES_SYSTEM_DEBUG})
source_group("Systems\\Graphics System\\Header Files" FILES ${HEADER_FILES_SYSTEM_GRAPHICS})
source_group("Systems\\Graphics System\\Source Files" FILES ${SOURCE_FILES_SYSTEM_GRAPHICS})
source_group("Systems\\Graphics System\\DirectX 11\\Header Files" FILES ${HEADER_FILES_SYSTEM_DX})
source_group("Systems\\Graphics System\\DirectX 11\\Source Files" FILES ${SOURCE_FILES_SYSTEM_DX})
source_group("Systems\\Graphics System\\OpenGL\\Header Files" FILES ${HEADER_FILES_SYSTEM_GL})
source_group("Systems\\Graphics System\\OpenGL\\Source Files" FILES ${SOURCE_FILES_SYSTEM_GL})
source_group("Systems\\Input\\Header Files" FILES ${HEADER_FILES_SYSTEM_INPUT})
source_group("Systems\\Input\\Source Files" FILES ${SOURCE_FILES_SYSTEM_INPUT})
source_group("Systems\\Memory System\\Header Files" FILES ${HEADER_FILES_SYSTEM_MEMORY})
source_group("Systems\\Memory System\\Source Files" FILES ${SOURCE_FILES_SYSTEM_MEMORY})
source_group("Systems\\Navigation\\Header Files" FILES ${HEADER_FILES_SYSTEM_NAVIGATION})
source_group("Systems\\Navigation\\Source Files" FILES ${SOURCE_FILES_SYSTEM_NAVIGATION})
source_group("Systems\\Scene Management\\Header Files" FILES ${HEADER_FILES_SYSTEM_SCENE})
source_group("Systems\\Scene Management\\Source Files" FILES ${SOURCE_FILES_SYSTEM_SCENE})
source_group("Systems\\Scripting\\Header Files" FILES ${HEADER_FILES_SYSTEM_SCRIPT})
source_group("Systems\\Scripting\\Source Files" FILES ${SOURCE_FILES_SYSTEM_SCRIPT})
source_group("Systems\\Sound System\\Header Files" FILES ${HEADER_FILES_SYSTEM_SOUND})
#source_group("Systems\\Sound System\\Source Files" FILES ${SOURCE_FILES_SYSTEM_SOUND})
#source_group("Systems\\Text System\\Header Files" FILES ${HEADER_FILES_SYSTEM_TEXT})
source_group("Systems\\Text System\\Source Files" FILES ${SOURCE_FILES_SYSTEM_TEXT})
source_group("Systems\\Time\\Header Files" FILES ${HEADER_FILES_SYSTEM_TIME})
source_group("Systems\\Time\\Source Files" FILES ${SOURCE_FILES_SYSTEM_TIME})
source_group("Systems\\Window\\Header Files" FILES ${HEADER_FILES_SYSTEM_WINDOW})
source_group("Systems\\Window\\Source Files" FILES ${SOURCE_FILES_SYSTEM_WINDOW})
source_group("Systems" FILES "${CMAKE_CURRENT_LIST_DIR}/Systems/Factory.h" "${CMAKE_CURRENT_LIST_DIR}/Systems/Factory.cpp" "${CMAKE_CURRENT_LIST_DIR}/Systems/System.h")

target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../../rapidjson/include")
#target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../../fmod/include")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../../opengl/glew-2.0.0/include")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../../opengl/glm")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../../opengl/glfw-3.4.bin.WIN64/include")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../../../lua-5.4.7/src")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../../../DirectXTK-oct2024/Inc")
target_include_directories(RavelEngine_API PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Base Components")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Base Components/header")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Behaviour")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Behaviour/header")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Controller")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Controller/header")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Game Object")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Game Object/header")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Game State Manager")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Game State Manager/header")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Math")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Math/header")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Structures")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Structures/header")

target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/AI")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/AI/header")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/AI/Task")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/AI/Task/header")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Collision System")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Collision System/header")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Core")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Core/header")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Debug")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Debug/header")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Graphics System")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Graphics System/DirectX 11/header")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Graphics System/OpenGL/header")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Graphics System/header")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Input")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Input/header")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Memory System")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Memory System/header")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Navigation")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Navigation/header")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Scene Management")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Scene Management/header")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Scripting")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Scripting/header")
#target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Sound System")
#target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Sound System/header")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Text System")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Text System/header")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Time")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Time/header")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Window")
target_include_directories(RavelEngine_API PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Systems/Window/header")


add_custom_command(TARGET RavelEngine_API POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"$(SolutionDir)Build\\$<CONFIG>\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\lib\"
					COMMAND ${CMAKE_COMMAND} -E copy \"${CMAKE_CURRENT_LIST_DIR}\\DataType.h\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\DataType.h\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Base Components\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Base Components\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Behaviour\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Behaviour\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Controller\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Controller\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Game Object\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Game Object\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Game State Manager\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Game State Manager\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Math\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Math\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Structures\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Structures\"
					COMMAND ${CMAKE_COMMAND} -E copy \"${CMAKE_CURRENT_LIST_DIR}\\Systems\\Factory.h\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Systems\\Factory.h\"
					COMMAND ${CMAKE_COMMAND} -E copy \"${CMAKE_CURRENT_LIST_DIR}\\Systems\\System.h\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Systems\\System.h\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Systems\\AI\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Systems\\AI\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Systems\\AI\\Task\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Systems\\AI\\Task\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Systems\\Collision System\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Systems\\Collision System\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Systems\\Core\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Systems\\Core\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Systems\\Debug\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Systems\\Debug\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Systems\\Graphics System\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Systems\\Graphics System\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Systems\\Graphics System\\DirectX 11\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Systems\\Graphics System\\DirectX 11\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Systems\\Graphics System\\OpenGL\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Systems\\Graphics System\\OpenGL\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Systems\\Input\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Systems\\Input\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Systems\\Memory System\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Systems\\Memory System\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Systems\\Navigation\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Systems\\Navigation\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Systems\\Scene Management\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Systems\\Scene Management\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Systems\\Scripting\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Systems\\Scripting\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Systems\\Sound System\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Systems\\Sound System\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Systems\\Text System\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Systems\\Text System\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Systems\\Time\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Systems\\Time\"
					COMMAND ${CMAKE_COMMAND} -E copy_directory \"${CMAKE_CURRENT_LIST_DIR}\\Systems\\Window\\header\"
					\"$(SolutionDir)RavelEngine_API\\$<CONFIG>\\include\\Systems\\Window\"
					)