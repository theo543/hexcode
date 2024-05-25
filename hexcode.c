#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

extern const uint32_t codes[];
extern const char* names[];
extern const int data_len;

void check_input_errors(const char *arg, const char *end) {
	if(arg == end || *end != '\0' || errno == ERANGE) {
		if(errno != ERANGE) {
			fprintf(stderr, "failed to parse argument\n");
		} else {
			fprintf(stderr, "argument is out of range\n");
		}
		exit(1);
	}
}

int main(int args, char**argv) {
	if(args < 2) {
		fprintf(stderr, "Usage: hexcode <number>\n");
		return 1;
	}

    const char *arg = argv[1];
	int32_t input;
    uint32_t data;

	errno = 0;
	char *end;
	if(arg[0] != '\0' && arg[0] == '0' && (arg[1] == 'x' || arg[1] == 'X')) {
		data = strtoul(arg, &end, 16);
		check_input_errors(arg, end);
	} else if(arg[0] != '\0' && arg[0] == '-') {
		input = strtol(arg, &end, 10);
		check_input_errors(arg, end);
		memcpy(&data, &input, sizeof(input));
	} else {
		data = strtoul(arg, &end, 10);
		check_input_errors(arg, end);
	}

    printf("0x%08X", data);

	for(int i = 0; i < data_len; i++) {
		if(codes[i] == data) {
			printf(" (%s)\n", names[i]);
		}
	}

	return 0;
}

