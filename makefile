CC = gcc
CFLAGS = -Wall -g -Wno-unused-value
LDFLAGS = -pthread
TARGET = matMultp
VPATH = SRC INCLUDE 

HEADERS = $(shell find . -name "*.h")
SOURCES = $(shell find . -name "*.c")
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $@

clean:
	-rm -f $(shell find . -name "*.o")
	-rm -f $(shell find . -name "*.out")
	-rm -f $(TARGET)
