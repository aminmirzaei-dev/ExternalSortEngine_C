#include "external_sort.h"
#include "run_generator.h"
#include "kway_merge.h"
#include <stdlib.h>

int external_sort(const char *input_file,
                  const char *output_file,
                  size_t memory_limit)
{
    char **run_files;
    int run_count;

    run_count = generate_runs(input_file, memory_limit, &run_files);
    if (run_count <= 0) {
        return -1;
    }

    if (kway_merge(run_files, run_count, output_file) != 0) {
        return -1;
    }

    free(run_files);
    return 0;
}

