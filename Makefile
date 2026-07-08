make:
	gcc -o reverse reverse.c -Wall

clean:
	rm -f reverse
	rm -f output.txt