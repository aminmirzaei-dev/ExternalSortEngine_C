#ifndef KWAY_MERGE_H
#define KWAY_MERGE_H

/*
 * Merges sorted run files into a single output file.
 *
 * Returns 0 on success, non-zero on failure.
 */
int kway_merge(char **run_files,
               int run_count,
               const char *output_file);

#endif

