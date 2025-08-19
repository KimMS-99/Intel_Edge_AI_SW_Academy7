CC=gcc

OBJECT = input.o output.o hi.o
TARGET = hi
$(TARGET):$(OBJECT)
	$(CC) -o $@ $(OBJECT)

$.o:$.c
	$(CC) -c -o $@ $<
clean:
	rm -f *.o $(TARGET)
