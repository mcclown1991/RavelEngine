set(HEADER_FILES_MATH "${CMAKE_CURRENT_LIST_DIR}/header/Matrix3x3.h"
				"${CMAKE_CURRENT_LIST_DIR}/header/Matrix4x4.h"
				"${CMAKE_CURRENT_LIST_DIR}/header/RavelMath.h"
				"${CMAKE_CURRENT_LIST_DIR}/header/Vector2.h"
				"${CMAKE_CURRENT_LIST_DIR}/header/Vector3.h"
				PARENT_SCOPE)
				
set(SOURCE_FILES_MATH "${CMAKE_CURRENT_LIST_DIR}/Matrix3x3.cpp"
				"${CMAKE_CURRENT_LIST_DIR}/Matrix4x4.cpp"
				"${CMAKE_CURRENT_LIST_DIR}/Vector2.cpp"
				"${CMAKE_CURRENT_LIST_DIR}/Vector3.cpp"
				PARENT_SCOPE)
