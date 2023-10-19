time: ipc.o time.o main.o # Compiling all object files into an executable file called "time"
	$(CC) -o $@ $?

ipc.o: ipc.c # Compiles ipc.c
	$(CC) -c $?

time.o: time.c # Compiles time.c
	$(CC) -c $?

main.o: main.c # Compiles main.c
	$(CC) -c $?

clean:
	-rm -f *.o
	@echo "All clean!"
