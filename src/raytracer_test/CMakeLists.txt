project(raytracer_test)

add_executable(raytracer_test WIN32
	main.cpp
	DepthApp.h
	DepthApp.cpp
    SimpleMaterial.h
    PhongMaterial.h
)

include_directories(${CMAKE_SOURCE_DIR}/src/raytracer)
include_directories(${CMAKE_SOURCE_DIR}/thirdparty)

target_link_libraries(raytracer_test raytracer)