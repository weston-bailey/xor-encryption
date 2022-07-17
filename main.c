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
	if (argc != 3) {
		printf("app needs two args.\n");
		return 0;
	}

	struct file file_in = read_file(argv[1]);
	char *key = argv[2];
	int key_len = strlen(key);
	int i = 0;	
	
	printf("file in memory:\n");
	print_file(file_in);	
	
	// encrypt the file in memory
	for (i = 0; i < file_in.len; i++) {
		file_in.buffer[i] = file_in.buffer[i] ^ key[i % key_len];	
	}

	printf("encrypted in memory:\n");
	print_file(file_in);	
	
	write_file(file_in);

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
	int i = 0;

	if (!fp) {
		printf("file: %s not found.\n", out_file.filename);
		fclose(fp);
		exit(EXIT_FAILURE);
	}
	
	while (i < out_file.len) {
		int result = fputc(out_file.buffer[i], fp);
		if (result == EOF) {
			fclose(fp);
			exit_fail("Failed to write a character! I am pretty sure the file is fucked.\n");
		}
		i++;
	}

	fclose(fp);
	return;
}
