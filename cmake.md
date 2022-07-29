# Сборка cmake

Файл CMakeLists.txt
```
cmake_minimum_required(VERSION 3.18)

# Имя исполняемого файла и проекта.
set(OUT_NAME "a.out")
set(PRJ_NAME my_prj)

# Стандарт c++
set(CMAKE_CXX_STANDARD 20)

project(${PRJ_NAME})

# Создать исполняемый файл a.out из списка исходников
add_executable(${OUT_NAME}
    main.cpp
)

# Линковать исполняемый файл приложения со следующими библиотеками
target_link_libraries(${OUT_NAME}
    -pthread
)

#find_package(Threads REQUIRED)
#target_link_libraries(${OUT_NAME} PRIVATE Threads::Threads)

# Печать списка переменных cmake
get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()
```

Команды сборки
```
mkdir bin
cd ./bin/
cmake ../
cmake --build .
```
или
```
mkdir bin
cd ./bin/
cmake ../
make
```

