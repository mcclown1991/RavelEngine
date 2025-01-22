set(HEADER_FILES_SYSTEM_AI "${CMAKE_CURRENT_LIST_DIR}/header/BehaviourTree.h"
				"${CMAKE_CURRENT_LIST_DIR}/header/Blackboard.h"
				"${CMAKE_CURRENT_LIST_DIR}/header/BTNode.h"
				PARENT_SCOPE)
				
set(SOURCE_FILES_SYSTEM_AI "${CMAKE_CURRENT_LIST_DIR}/BehaviourTree.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/Blackboard.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/BTNode.cpp"
						PARENT_SCOPE)

set(HEADER_FILES_SYSTEM_AI_TASK "${CMAKE_CURRENT_LIST_DIR}/Task/header/PrintTask.h"
				"${CMAKE_CURRENT_LIST_DIR}/Task/header/Tasks.h"
				PARENT_SCOPE)
				
set(SOURCE_FILES_SYSTEM_AI_TASK "${CMAKE_CURRENT_LIST_DIR}/Task/PrintTask.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/Task/Tasks.cpp"
						PARENT_SCOPE)