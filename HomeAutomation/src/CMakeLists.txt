add_library(production_src
	app/LightScheduler.cpp
	app/globals.cpp
)

target_include_directories(production_src
	PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/app
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/devices
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/util
	${CMAKE_CURRENT_SOURCE_DIR}/../os/inc
	# PRIVATE ... for local header file
)
