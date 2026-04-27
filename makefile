CC = gcc

run:
	$(CC) -o pillow main.c value.c chunk.c debug.c memory.c vm.c scanner.c compiler.c 