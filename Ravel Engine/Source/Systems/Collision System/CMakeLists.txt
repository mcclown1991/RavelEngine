set(HEADER_FILES_SYSTEM_COLLISION "${CMAKE_CURRENT_LIST_DIR}/header/CollisionManager.h"
							"${CMAKE_CURRENT_LIST_DIR}/header/RavelRect.h"
							"${CMAKE_CURRENT_LIST_DIR}/header/SpatialHash.h"
							PARENT_SCOPE)
				
set(SOURCE_FILES_SYSTEM_COLLISION "${CMAKE_CURRENT_LIST_DIR}/CollisionManager.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/RavelRect.cpp"
						"${CMAKE_CURRENT_LIST_DIR}/SpatialHash.cpp"
						PARENT_SCOPE)
