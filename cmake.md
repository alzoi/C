# Сборка cmake

Файл CMakeLists.txt
```
cmake_minimum_required(VERSION 3.22)
project(my_prj)

set(CMAKE_CXX_STANDARD 20)

# Создать исполняемый файл a.out из списка исходников
add_executable(a.out
  main.cpp
  foo.cpp
)
```

Команды сборки
```
mkdir bin
cd ./bin/
cmake ../
cmake --build .
```
