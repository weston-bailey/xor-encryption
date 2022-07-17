#include <stdio.h>
// #include <stddef.h>
#include <stdlib.h>

#define RF_BUFFSIZE 1024

void exit_fail(char *msg) {
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

char *read_file(char *filename) {

	FILE *fp;
	char ch;
	int i = 0;
	int buffsize = RF_BUFFSIZE;
	char *read_buffer = malloc(sizeof(char) * buffsize); 
	fp = fopen (filename, "r");

	if (!read_buffer) {
		fclose(fp);
		exit_fail("allocation error.");
	}

	if (!fp) {
		printf("file: %s not found.\n", filename);
		fclose(fp);
		exit(EXIT_FAILURE);
	}
	// loop while not at the end of file
	while ((ch = fgetc (fp)) != EOF) {
		/* printf("%c", ch); */
		read_buffer[i] = ch;
		i++;
		if (i >= buffsize) {
			buffsize += RF_BUFFSIZE;
			read_buffer = realloc(read_buffer, buffsize);
			if (!read_buffer) {
				fclose(fp);
				exit_fail("reallocation error.\n");
			}
		}
	}
	// important to close the file
	fclose(fp);

	read_buffer[i] = '\0';
	
	return read_buffer;
}

int main(int argc, char *argv[])
{
	char my_string[17] = "Have a nice day!";
	char my_key[17] = "ABCDEFGHIJ123456";
	int i = 0;
	char *file_in;

	for (i = 1; i < argc; i++) {
		printf("script arg %d: %s\n", i, argv[i]);
	}

	for (i = 0; i < 16; i++) {
		my_string[i] = my_string[i] ^ my_key[i];
		printf("%c", my_string[i]);
	}

	printf("\n");

	for (i = 0; i < 16; i++) {
		my_string[i] = my_string[i] ^ my_key[i];
		printf("%c", my_string[i]);
	}

	printf("\n");


	file_in = read_file(argv[1]);

	/* // file pointer */
	/* FILE *fp; */
	/* // charactor for looping the file */
	/* char ch; */
	/* // read the file with fopen */
	/* // fopen ("file-name.extention", "read/write") */
	/* // "r" = read "w" = write */
	/* fp = fopen ("list.txt", "r"); */
	/* if (fp == NULL) printf("file not found"); */
	/* // loop while not at the end of file */
	/* while ((ch = fgetc (fp)) != EOF) { */
	/*   printf ("%c", ch); */
	/* } */

	/* // important to close the file */
	/* fclose (fp); */

	return 0;
}
