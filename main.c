#include <stdio.h>
// #include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define RF_BUFFSIZE 1024

void exit_fail(char *msg);

struct file {
	int len;
	char *filename;
	char *buffer;
};


struct file read_file(char *filename);
void print_file(struct file f);
void write_file(struct file out_file);

int main(int argc, char *argv[])
{
	/* char my_string[17] = "Have a nice day!"; */
	/* char my_key[17] = "ABCDEFGHIJ123456"; */
	/* int i = 0; */
	struct file file_in;
	char prev_c;
	char swap;
	int flag = 0;

	/* for (i = 1; i < argc; i++) { */
	/* 	printf("script arg %d: %s\n", i, argv[i]); */
	/* } */

	/* for (i = 0; i < 16; i++) { */
	/* 	my_string[i] = my_string[i] ^ my_key[i]; */
	/* 	printf("%c", my_string[i]); */
	/* } */

	/* printf("\n"); */

	/* for (i = 0; i < 16; i++) { */
	/* 	my_string[i] = my_string[i] ^ my_key[i]; */
	/* 	printf("%c", my_string[i]); */
	/* } */

	/* printf("\n"); */


	file_in = read_file(argv[1]);

	
	printf("file in memory:\n");
	print_file(file_in);	
	
	// encrypt the file in memory
	int i = 0;
	for (i = 0; i < file_in.len; i++) {
		if (i == 0) {
			prev_c = file_in.buffer[i];
			continue;
		}
		swap = file_in.buffer[i];
		file_in.buffer[i] = file_in.buffer[i] ^ prev_c;
		prev_c = swap;
	}

	printf("encrypted in memory:\n");
	print_file(file_in);	

	return 0;
}


void exit_fail(char *msg) 
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

struct file read_file(char *filename) 
{

	FILE *fp;
	char ch;
	int i = 0;
	int buffsize = RF_BUFFSIZE;
	struct file new_file;
	new_file.len = 0;
	new_file.buffer = malloc(sizeof(char) * buffsize); 
	new_file.filename = filename;

	fp = fopen (new_file.filename, "r");
	if (!new_file.filename) {
		fclose(fp);
		exit_fail("allocation error.");
	}

	if (!fp) {
		printf("file: %s not found.\n", filename);
		fclose(fp);
		exit(EXIT_FAILURE);
	}
	// loop while not at the end of file
	while ((ch = fgetc(fp)) != EOF) {
		/* printf("%c", ch); */
		new_file.buffer[i] = ch;
		i++;
		new_file.len++;
		if (i >= buffsize) {
			buffsize += RF_BUFFSIZE;
			new_file.buffer = realloc(new_file.buffer, buffsize);
			if (!new_file.buffer) {
				fclose(fp);
				exit_fail("reallocation error.\n");
			}
		}
	}
	// important to close the file
	fclose(fp);

	new_file.buffer[i] = '\0';
	
	return new_file;
}

void print_file(struct file f)
{
	int i = 0;
	for (i = 0; i < f.len; i++) {
		printf("%c", f.buffer[i]);
	}
	return;
}

void write_file(struct file out_file) 
{
	FILE *fp = fopen(out_file.filename, "w+");


	if (!fp) {
		printf("file: %s not found.\n", out_file.filename);
		fclose(fp);
		exit(EXIT_FAILURE);
	}

	fputs(out_file.buffer, fp);

	fclose(fp);
	return;
}
