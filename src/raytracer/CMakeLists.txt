project(raytracer)

add_library(raytracer
	Ray.h
    Ray.cpp
    App.h
    App.cpp
    RayTracer.h
    RayTracer.cpp
    Camera.h
    Camera.cpp
    Sphere.h
    Sphere.cpp
    Node.h
    Plane.h
    common.h
	Context.cpp
	Context.h
    Material.h
    Light.h
    Light.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/thirdparty)