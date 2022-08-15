LIBNAME = lcthw
TARGET = lib$(LIBNAME)
SOURCES = $(wildcard src/*.c src/lcthw/*.c)
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))
TESTSRC = $(wildcard tests/*.c)
TESTOBJ = $(patsubst %.c,%.o,$(TESTSRC))
OUTPUT = bin
LIBS = 

CC = $(CROSS_COMPILE)gcc
CFLAGS = -std=c99 -Isrc -fpic

all: $(OBJECTS) $(TARGET) $(TESTOBJ)

$(OBJECTS):
	@echo "####### build $@ for $(TARGET)"
	$(CC) $*.c $(CFLAGS) -c -o $@

$(TARGET):
	@echo "####### build $(TARGET)"
	$(CC) $(OBJECTS) -shared -o $(OUTPUT)/$(TARGET).so

$(TESTOBJ):
	@echo "####### build $@"
	$(CC) $*.c $(CFLAGS) -c -o $@
	@echo "############ build test case ($*)"
	$(CC) $@ -o $* -L$(OUTPUT) -l$(LIBNAME)
	mv $* $(OUTPUT)

clean:
	@echo "####### clean binary files"
	rm -rf $(OUTPUT)/* $(OBJECTS) $(TESTOBJ)

install:
	sudo install -t /usr/lib $(OUTPUT)/$(TARGET).so

xxxx:
	@echo "TESTCASE: " $(TESTCASE)
