TARGET=main
# all .cpp files in this directory are my sources
SOURCES=$(wildcard *.cpp)
OBJS=$(SOURCES:.cpp=.o)

CC=g++
LDFLAGS=-g #for using the gdb
INC_FLAGS=-I../include
CFLAGS= -c -pedantic -Wall -Werror -Wconversion -ansi -g $(INC_FLAGS)# -g flag for using gdb
CXXFLAGS=$(CFLAGS)

.PHONY: clean run gdb leak

$(TARGET): $(OBJS)


include .depends

.depends:
	$(CC) -MM -I$(INC_DIR) $(SOURCES) > .depends
clean:
	rm -f $(OBJS) $(TARGET) .depends
leak:
	valgrind --leak-check=full ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

# Do not forget to add '-g' to CFLAGS
gdb: $(TARGET)
	gdb -q ./$(TARGET)






