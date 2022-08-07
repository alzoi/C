# Makefile

## Ссылки
https://habr.com/ru/post/155201/  
[Makefile. Компиляция нескольких файлов с исходным кодом](https://www.youtube.com/watch?v=9PeEYcYHHkM)  
https://www.youtube.com/watch?v=P18_wphhrQ4  

## Примеры сборки
### Пример 1
```
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
```
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

clean :
	rm $(TARGET) *.o
```
Расшифровка:
```
$< - всё, что справа от символа двоеточия.  
$@ - всё, что слева от символа двоеточия.
SRC = $(wildcard $(PREF_SRC)*.c) - получить все файлы в указанной папке, заканчивающиеся на .c  
OBJ = $(patsubst $(PREF_SRC)%.c, $(PREF_OBJ)%.o, $(SRC)) - взять из переменной SRC все строки,
заканчивающиеся на .c и поменять это окончание на .o, результат сохранить в переменную OBJ
```

Сокращённый вариант:
```
CFLAGS = -Wall -pthread

main: main.o foo.o bar.o

clean:
	rm -f *.o main
```
