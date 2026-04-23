a.out: main.o scan_input.o jobs.o get_command.o execute_command.o
	gcc -o a.out main.o scan_input.o jobs.o get_command.o execute_command.o
main.o: main.c
	gcc -c main.c
scan_input.o: scan_input.c
	gcc -c scan_input.c
jobs.o: jobs.c
	gcc -c jobs.c
get_command.o: get_command.c
	gcc -c get_command.c
execute_command.o: execute_command.c
	gcc -c execute_command.c
clean:
	rm *.out *.o