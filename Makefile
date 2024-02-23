CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=file_search.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=search_file

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o $(EXECUTABLE)
