default:
	gcc -g -c ./src/**/*.c ./src/*.c
	gcc -o main *.o
