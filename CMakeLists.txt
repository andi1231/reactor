
# Проверка версии CMake.
# Если версия установленой программы
# старее указаной, произайдёт аварийный выход.

cmake_minimum_required(VERSION 3.12) 

project(reactor)
                
set(SOURCE_APP main.cpp)

# Создает исполняемый файл с именем main
# из исходника main.cpp
add_executable(reactor ${SOURCE_APP})		




