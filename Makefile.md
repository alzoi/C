# Makefile
Посмотреть базу знаний программы make
```
make -p
```
## Ссылки
https://habr.com/ru/post/155201/  
[Makefile. Компиляция нескольких файлов с исходным кодом](https://www.youtube.com/watch?v=9PeEYcYHHkM)  
https://www.youtube.com/watch?v=P18_wphhrQ4  
https://www.youtube.com/watch?v=2uGo7-M34M8  

## Примеры сборки
### Пример 1
```make
CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp hello.cpp factorial.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=hello

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
```
### Пример 2
```make
TARGET = MyProject
CC = gcc

PREF_SRC = ./src/
PREF_OBJ = ./obj/

SRC = $(wildcard $(PREF_SRC)*.c)
OBJ = $(patsubst $(PREF_SRC)%.c, $(PREF_OBJ)%.o, $(SRC))

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

$(PREF_OBJ)%.o : $(PREF_SRC)%.c
	$(CC) -c $< -o $@

clean:
	rm $(TARGET) *.o
```
Расшифровка:
```
.cpp.o - это суфиксное правило сообщает make информацию, что файлы .o создаются из файлов .cpp.  
%.o: %.cpp - это эквивалентное шаблонное правило из .cpp сделать .o.  
$@ - имя цели обрабатываемого правила (всё, что слева от символа двоеточия).
$< - имя первой зависимости обрабатываемого правила.  
$^ - cписок всех зависимостей обрабатываемого правила (всё, что справа от символа двоеточия).
SRC = $(wildcard $(PREF_SRC)*.c) - получить все файлы в указанной папке, заканчивающиеся на .c  
OBJ = $(patsubst $(PREF_SRC)%.c, $(PREF_OBJ)%.o, $(SRC)) - взять из переменной SRC все строки,
заканчивающиеся на .c и поменять это окончание на .o, результат сохранить в переменную OBJ
```

Сокращённый вариант:
```make
CFLAGS = -Wall -pthread

# Указываем абстрактые цели, которые не должны быть связаны с файлами.
.PHONY: clean

main: main.o foo.o bar.o

clean:
	rm -f *.o main
```
Пояснения:  
**main: main.o foo.o bar.o** - указываем сборщику, что наша цель под именем main зависит от указанного перечня объектных файлов. Далее make найдёт в текущей папке соответствующие файлы с исходными кодами. По расширению файла с исходным кодом выполнит компиляцию нужным компилятором.
Первая строка в Makefile является целью по умолчанию.
