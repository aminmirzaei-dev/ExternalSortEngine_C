#include "run_generator.h"
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int generate_runs(const char *input_file,
                  size_t memory_limit,
                  char ***run_files)
{
    FILE *in;
    int *buffer;
    size_t count;
    int run_count = 0;
    char **files = NULL;

    in = fopen(input_file, "r");
    if (!in) {
        return -1;
    }

    buffer = malloc(memory_limit * sizeof(int));
    if (!buffer) {
        fclose(in);
        return -1;
    }

    while (!feof(in)) {
        count = 0;
        while (count < memory_limit &&
               fscanf(in, "%d", &buffer[count]) == 1) {
            count++;
        }

        if (count == 0) {
            break;
        }

        qsort(buffer, count, sizeof(int), compare_ints);

        files = realloc(files, (run_count + 1) * sizeof(char *));
        files[run_count] = malloc(32);

        sprintf(files[run_count], "run_%d.tmp", run_count);

        FILE *out = fopen(files[run_count], "w");
        if (!out) {
            fclose(in);
            free(buffer);
            return -1;
        }

        for (size_t i = 0; i < count; i++) {
            fprintf(out, "%d\n", buffer[i]);
        }

        fclose(out);
        run_count++;
    }

    fclose(in);
    free(buffer);

    *run_files = files;
    return run_count;
}

