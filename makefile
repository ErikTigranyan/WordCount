all: main_target

main_target:
	gcc WordCount.c -o WordCount

clean: 
	rm WordCount

