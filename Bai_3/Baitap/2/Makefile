CC=gcc
CCFLAGS=-Wall
LDFLAGS=
LDLIBS = 
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
TARGET=FileUnix

all:    $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

%.o: %.c %.h
	$(CC) $(CCFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)
install:
	sudo cp $(TARGET) /usr/bin

