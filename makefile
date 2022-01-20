CC = gcc
OBJ = ./objects/URL.o ./objects/searcher.o
HEADERS = URL.h
LIBS = -lcurl
DIRS = Searches


./bin/searcher: $(OBJ) 
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LIBS) 

./objects/%.o: ./src/%.c
	@mkdir -p $(@D)
	$(CC) -c $< -o $@

$(shell mkdir -p $(DIRS))

clean:
	rm -rf objects/ bin/ 

clean-Searches:
	rm -rf Searches/ 

clean-all: clean-Searches clean