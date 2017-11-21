project(raytracer_test)

add_executable(raytracer_test WIN32
	main.cpp
	TestApp.h
	TestApp.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/src/raytracer)
include_directories(${CMAKE_SOURCE_DIR}/thirdparty)

target_link_libraries(raytracer_test raytracer)