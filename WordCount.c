#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>

int wordCounter(const char* text)
{
	int count = 0;
	if (text[0] != '\n' && text[0] != ' ' && text[0] != '\0')
	{
		++count;
	}
	for(int i = 0; text[i] != '\0'; ++i)
	{
		if(text[i] == ' ' || text[i] == '\n')
		{
			if(text[i + 1] == '\0')
			{
				break;
			} 
			else if(text[i + 1] != ' ' && text[i + 1] != '\n')
			{
				++count;
			}
		}
	}
	return count;
}

int main(int argc, char** argv)
{
	//from file or using flags
	if(argc == 2)
	{
		int c;
		if((c = getopt(argc, argv, "+vh")) != -1)
		{
			switch (c) 
			{ 
				case 'v': 
					printf("Version - 2. 3. 0.\n"); 
					exit(EXIT_SUCCESS); 
					break; 
				case 'h': 
					printf("run ./a.out [FILE] [vh]\n"); 
					exit(EXIT_SUCCESS); 
					break; 
				case '?': 
					printf("Invalid flag\n"); 
					exit(EXIT_FAILURE);	
					break;
			} 
		}
	
		FILE *file = fopen(argv[1], "r");
        if (file == NULL)
		{
            fprintf(stderr, "Не удается открыть файл '%s'\n", argv[1]);
            return 1;
        }

        char *line = NULL;
        size_t len = 0;
		int fuse = 0;
        while(getline(&line, &len, file) != -1)
		{	
            fuse += wordCounter(line);
        }
		printf("Количество слов: %d\n", fuse);

        free(line);
        fclose(file);		
	}
	//from stdin
	else if(argc == 1)
	{
        char *input = NULL;
        size_t bufferSize = 0;
        ssize_t charsRead;

        printf("Введите текст. Для завершения ввода используйте Ctrl+D)\n");
		
		
        while ((charsRead = getline(&input, &bufferSize, stdin)) != -1)
		{
            int wordCount = wordCounter(input);
            printf("Количество слов: %d\n", wordCount);
        }

        free(input);				
	}
	else
	{
		fprintf(stderr, "Too many arguments!\n");
		return -1;
	}
	return 0;
}

