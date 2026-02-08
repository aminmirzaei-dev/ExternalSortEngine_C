#ifndef RUN_GENERATOR_H
#define RUN_GENERATOR_H

#include <stddef.h>

/*
 * Generates sorted runs from the input file.
 *
 * Returns the number of runs created, or -1 on failure.
 */
int generate_runs(const char *input_file,
                  size_t memory_limit,
                  char ***run_files);

#endif 

