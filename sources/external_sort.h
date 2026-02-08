#ifndef EXTERNAL_SORT_H
#define EXTERNAL_SORT_H

#include <stddef.h>

/*
 * Sorts a large input file using external merge sort.
 *
 * input_file   : Path to input file containing integers (one per line)
 * output_file  : Path to output file (sorted)
 * memory_limit : Maximum number of integers to keep in memory
 *
 * Returns 0 on success, non-zero on failure.
 */
int external_sort(const char *input_file,
                  const char *output_file,
                  size_t memory_limit);

#endif 
