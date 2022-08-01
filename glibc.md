# GNU LibC

## Документация
https://www.gnu.org/software/libc/manual/html_node/index.html  

# Компилятор GCC
https://gcc.gnu.org/onlinedocs/gcc/Invoking-GCC.html  

## Предварительно скомпилированные заголовки
https://gcc.gnu.org/onlinedocs/gcc-4.9.4/libstdc++/manual/manual/using_headers.html  

В файл ./include/all_hed.h вставляем все заголовки проекта.  
Из файла ./include/all_hed.h получаем предварительно скомпилированный заголовок, необходимо добавить все опции, что и при компиляции основной программы
```
g++ -Winvalid-pch -x c++-header -std=c++17 -pthread ./include/all_hed.h
```
