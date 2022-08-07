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
$< - всё, что справа от символа двоеточия.  
$@ - всё, что слева от символа двоеточия.
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