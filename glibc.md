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
Должен появиться файл ./include/all_hed.h.gch  
Компилируем программу, указывая в качестве предварительно скомпилированного заголовка имя файл all_hed.h и папку, в которой был размещён скомпилированный заголовок
```
g++ -Winvalid-pch -H -x c++-header -std=c++17 -pthread -I ./include -include all_hed.h main.cpp
```
Если скомпилированный заголовок изпользован, должно быть выведена строка с восклицательным знаком
```
! ./include/all_hed.h.gch
```

# Опции GCC
## -stdlib
Для компилятора g++ можно зававать опцию -stdlib, предусмотрены значения:  
| Опция              | Описание
| ----------------------- | -------------
| stdlib=libstdc++         | по умолчанию собственная среда выполнения С++ для g++
| -stdlib=libc++     | представляет среду выполнения С++, установленную в некоторых операционных системах (например, в версиях Darwin, начиная с Darwin11 и выше)
