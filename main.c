#include <stdio.h>
// #include <stddef.h>
#include <stdlib.h>

typedef struct Char_List char_list;
typedef struct Char_Node char_node;
struct char_list;
struct char_node;

char_list char_list_create();

int main(int argc, char *argv[])
{
	char my_string[17] = "Have a nice day!";
	char my_key[17] = "ABCDEFGHIJ123456";
	int i = 0;
	/* // file pointer */
	/* FILE *fp; */
	/* // charactor for looping the file */
	/* char ch; */
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
