#CC:=arm-linux-gcc
CC:=g++

TARGET=TestMyImage
OBJECT=$(TARGET).o 

$(TARGET):$(OBJECT)
	$(CC) -o $@ $(OBJECT)
%.o:%.c
	$(CC) -c -o $@ $<
clean:
	rm -f *.o $(TARGET)
