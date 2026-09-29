#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

extern int sum_array(const int *values, int count);

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <data-file>\n", argv[0]);
		return 1;
	}

	FILE *input = fopen(argv[1], "r");
	if (input == NULL) {
		perror(argv[1]);
		return 1;
	}

	int count;
	if (fscanf(input, "%d", &count) != 1 || count < 0 ||
		(size_t)count > SIZE_MAX / sizeof(int)) {
		fprintf(stderr, "Invalid number of data points in %s\n", argv[1]);
		fclose(input);
		return 1;
	}

	int *values = NULL;
	if (count > 0) {
		values = malloc((size_t)count * sizeof(*values));
		if (values == NULL) {
			perror("malloc");
			fclose(input);
			return 1;
		}
	}

	for (int i = 0; i < count; ++i) {
		if (fscanf(input, "%d", &values[i]) != 1) {
			fprintf(stderr, "Expected %d integer values in %s\n", count, argv[1]);
			free(values);
			fclose(input);
			return 1;
		}
	}

	fclose(input);
	printf("Sum: %d\n", sum_array(values, count));
	free(values);
	return 0;
}
