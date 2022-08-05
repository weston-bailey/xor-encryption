#include <stdio.h>
// #include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define RF_BUFFSIZE 1024
#define RL_BUFFSIZE 1024

void exit_fail(char *msg);
char *read_line(void);
void help(void);

struct file {
	int len;
	char *filename;
	char *buffer;
};

struct file read_file(char *filename);
struct file xor_enc(struct file f, char *key, int key_len);
struct file xor_enc_prev(struct file f);
void print_file(struct file f);
void write_file(struct file out_file);
void write_stdout(struct file f);

int main(int argc, char *argv[])
{
	struct file file_in = read_file(argv[1]);
	char *key = argv[2];
	int key_len = strlen(key);
	char *input_line;

	if (argc != 3) {
		printf("app needs two args.\n");
		return 0;
	}

	/* printf("file in memory:\n"); */
	/* print_file(file_in); */	

	/* file_in = xor_enc(file_in, key, key_len); */
	puts("first enc:\n");
	file_in = xor_enc_prev(file_in);
	write_stdout(file_in);
	
	puts("\nsecond enc:\n");
	file_in = xor_enc_prev(file_in);
	write_stdout(file_in);
	puts("\n");
	/* printf("encrypted data in memory:\n"); */
	/* print_file(file_in); */	

	/* printf("\n"); */
	/* printf("Would you like proceed with writing the file? (yes/no)\n"); */
	
	/* input_line = read_line(); */

	/* if (strcmp(input_line, "yes") == 0 || strcmp(input_line, "y") == 0) { */
	/* 	write_file(file_in); */
	/* } else { */
	/* 	printf("File not written. Exiting...\n"); */
	/* } */

	return 0;
}


void exit_fail(char *msg) 
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}


char *read_line(void)
{
	int buffsize = RL_BUFFSIZE;
	int i = 0;
	char c = 0;
	char *buffer = malloc(sizeof(char) * buffsize);

	if (!buffer) {
		exit_fail("allocation error\n");
	}

	// read input until EOF or newline
	while (1) {
		c = getchar();
		
		if (c == EOF || c == '\n') {
			buffer[i] = '\0';
			return buffer;
		} else {
			buffer[i] = c;
		}

		i++;

		if (i >= buffsize) {
			buffsize += RL_BUFFSIZE;
			buffer = realloc(buffer, buffsize);
			if (!buffer) {
				exit_fail("allocation error\n");
			}
		}
	}
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

struct file xor_enc(struct file f, char *key, int key_len)
{
	int i = 0;
	// encrypt the file in memory
	for (i = 0; i < f.len; i++) {
		f.buffer[i] = f.buffer[i] ^ key[i % key_len];	
	}

	return f;
}

struct file xor_enc_prev(struct file f) 
{
	// starting at the second char, hold char in a swap vairable and use prev char to enc current char
	int i = 1;
	char swap = f.buffer[0];
	while (i <= f.len) {
		f.buffer[i] = f.buffer[i] ^ swap;
		swap = f.buffer[i];
		i++;
	}

	return f;
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
			exit_fail("Failed to write a character! I am pretty sure the file is ruined.\n");
		}
		i++;
	}

	fclose(fp);
	return;
}

void write_stdout(struct file f) 
{
	fwrite(f.buffer, 1, f.len, stdout);
	return;
}
