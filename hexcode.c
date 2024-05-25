#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

extern const uint32_t codes[];
extern const char* names[];
extern const int data_len;

static void check_input_errors(const char *arg, const char *end, const char *interpreted_as) {
	if(arg == end || *end != '\0' || errno == ERANGE) {
		if(errno != ERANGE) {
			fprintf(stderr, "Failed to parse argument,");
		} else {
			fprintf(stderr, "Argument is out of range");
		}

		fprintf(stderr, " interpreted as %s, use --help for more information.\n", interpreted_as);
		fprintf(stderr, "The bad argument was \"%s\".\n", arg);
		exit(1);
	}
}

static bool contains_help_flag(int argc, char **argv) {
	// simple O(n*m) search, no need for anything fancy
	const char *flags[] = {"-?", "-h", "-help", "--?", "--h", "--help", "/?", "/h", "/help", "\\?", "\\h", "\\help"};
	const int flag_count = sizeof(flags) / sizeof(flags[0]);
	char tmp_buffer[10]; // for converting arguments to lowercase
	memset(tmp_buffer, 0, sizeof(tmp_buffer));
	for(int x = 0;x < argc;x++) {
		for(int y = 0;y < flag_count;y++) {
			strncpy(tmp_buffer, argv[x], 9);
			for(int i = 0;tmp_buffer[i] != '\0';i++) {
				tmp_buffer[i] = (char)tolower(tmp_buffer[i]);
			}
			if(strcmp(tmp_buffer, flags[y]) == 0) {
				return true;
			}
		}
	}
	return false;
}

int main(int argc, char **argv) {
	bool help_requested = contains_help_flag(argc, argv);
	if(argc != 2 || help_requested) {
		fprintf(stderr, "Usage: hexcode <number>\n\n");
		fprintf(stderr, "This program prints the hexadecimal representation of signed 32-bit numbers, unsigned 32-bit numbers, and 32-bit hexadecimal numbers.\n");
		fprintf(stderr, "Signed numbers will be re-interpreted as unsigned numbers (which use two's complement on all major platforms).\n");
		fprintf(stderr, "If it matches a known Windows error code, the code's name will be shown.\n");
		return help_requested ? 0 : 1;
	}

    const char *arg = argv[1];
	int32_t input;
    uint32_t data;

	errno = 0;
	char *end;
	if(arg[0] != '\0' && arg[0] == '0' && (arg[1] == 'x' || arg[1] == 'X')) {
		data = strtoul(arg, &end, 16);
		check_input_errors(arg, end, "hexadecimal number (because of 0x or 0X prefix)");
	} else if(arg[0] != '\0' && arg[0] == '-') {
		input = strtol(arg, &end, 10);
		check_input_errors(arg, end, "signed decimal number (because it has a minus sign)");
		memcpy(&data, &input, sizeof(input));
	} else {
		data = strtoul(arg, &end, 10);
		check_input_errors(arg, end, "unsigned decimal number (because it doesn't have a minus sign)");
	}

    printf("0x%08X", data);

	for(int i = 0; i < data_len; i++) {
		if(codes[i] == data) {
			printf(" (%s)", names[i]);
		}
	}

	printf("\n");

	return 0;
}

