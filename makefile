CC = gcc
OBJ = ./objects/URL.o ./objects/searcher.o
HEADERS = URL.h
LIBS = -lcurl

./bin/searcher: $(OBJ)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LIBS)

./objects/%.o: ./src/%.c
	@mkdir -p $(@D)
	$(CC) -c $< -o $@

clean:
	rm -rf objects/ bin/ 