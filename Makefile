build:
	gcc main.c Utils.c Trie_functions.c -o tema3 -std=gnu99 -Wall
run:
	./tema3
clean:
	rm -rf tema3
