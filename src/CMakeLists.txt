############################################################
#   The CMake File for CloudMaker.  It provides for
#   the following libraries:  Boost, GLM, GL, GLEW, pthread,
#   stdc++, SDL2
#   Created by Edward C. Eberle <eberdeed@ebedeed.net>
#   March 2020 San Diego California USA
#   Copyright Maureen Ann Quinn March 2020
############################################################
cmake_minimum_required(VERSION 2.6)
project(slickexplosion)
add_executable(slickexplosion shader.cpp slickexplosion.cpp explodeit.cpp 
camera.cpp skybox.cpp asterobject.cpp createimage.cpp)
add_definitions(-g -fPIC -pthread -std=c++17 -pthread)
include_directories(/usr/include/SDL2 /usr/include/GL
/usr/include/glm /usr/include/boost)
link_directories(/usr/lib /usr/local/lib /usr/lib/x86_64-linux-gnu)
target_link_libraries(slickexplosion stdc++ GL GLEW SDL2-2.0 assimpopengl 
pthread boost_filesystem boost_system pthread freeimage freeimageplus)
install(TARGETS slickexplosion DESTINATION /usr/bin)
