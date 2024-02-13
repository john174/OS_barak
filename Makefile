TARGET = MyProject
CC = gcc

PREF_SRC = ./src/
PREF_OBJ = ./obj/

SRC = $(PREF_SRC)main.c
OBJ = $(PREF_OBJ)main.o

$(TARGET): $(SRC) $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

$(PREF_OBJ)main.o: $(PREF_SRC)main.c
	$(CC) -c $< -o $@

clean:
	rm -f $(TARGET) $(PREF_OBJ)*.o
