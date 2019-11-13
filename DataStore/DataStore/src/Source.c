#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif


#define MAXLEN 100

typedef struct {
	char buffer[MAXLEN];
	size_t buffer_length;
	ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer() {
	InputBuffer *input_buffer = malloc(sizeof(InputBuffer));
	//input_buffer->buffer = NULL;
	input_buffer->buffer_length = MAXLEN;
	input_buffer->input_length = 0;
	return input_buffer;
}

void print_prompt() { printf("db > "); }

void read_input(InputBuffer* input_buffer) {
	char* bytes_read = fgets(input_buffer->buffer, input_buffer->buffer_length, stdin);


	if (bytes_read == NULL) {
		printf("Error reading input\n");
		exit(EXIT_FAILURE);
	}
	// Ignore trailing newline
	// no casting should be applied here
	printf("%d",sizeof(bytes_read));
	input_buffer->input_length = strlen(bytes_read) - 1;
	//printf("%s", input_buffer->buffer);
}

void close_input_buffer(InputBuffer* input_buffer) {
	free(input_buffer);
}

int main(int argc, char* argv[]) {
	InputBuffer* input_buffer = new_input_buffer();
	while (true) {
		print_prompt();
		read_input(input_buffer);

		if (strcmp(input_buffer->buffer, ".exit\n") == 0) {
			close_input_buffer(input_buffer);
			exit(EXIT_SUCCESS);
		}
		else {
			printf("Unrecognized command '%s'.\n", input_buffer->buffer);
		}
	}
}
