# Makefile

## Ссылки
https://habr.com/ru/post/155201/  
[Makefile. Компиляция нескольких файлов с исходным кодом](https://www.youtube.com/watch?v=9PeEYcYHHkM)  
https://www.youtube.com/watch?v=P18_wphhrQ4  

## Примеры сборки
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
