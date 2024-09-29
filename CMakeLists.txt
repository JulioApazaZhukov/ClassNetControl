cmake_minimum_required(VERSION 3.5)
project(ClassNetControl LANGUAGES C CXX)

# Especifica el estándar de C++
set(CMAKE_CXX_STANDARD 11)

# Añadir el directorio de inclusión
include_directories(E:/ClassNetControl/lib)

# Agregar el ejecutable
add_executable(ClassNetControl src/main.cpp)

# Enlazar las librerías necesarias
target_link_libraries(ClassNetControl ws2_32 E:/ClassNetControl/lib/WinDivert.lib)