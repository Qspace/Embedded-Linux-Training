C=gcc
CCFLAGS=-Wall
LDFLAGS=
LDLIBS = -lwiringPi
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
TARGET=ledcontrol

all:    $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

%.o: %.c %.h
	$(CC) $(CCFLAGS) -c $<

%.o: %.c
	$(CC) $(CCFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)
install:
	sudo cp $(TARGET) /usr/lib/cgi-bin

