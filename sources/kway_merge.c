#include "kway_merge.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int value;
    int file_index;
} heap_node_t;

static void swap(heap_node_t *a, heap_node_t *b)
{
    heap_node_t temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify(heap_node_t *heap, int size, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left].value < heap[smallest].value) {
        smallest = left;
    }
    if (right < size && heap[right].value < heap[smallest].value) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapify(heap, size, smallest);
    }
}

int kway_merge(char **run_files,
               int run_count,
               const char *output_file)
{
    FILE **files;
    FILE *out;
    heap_node_t *heap;
    int heap_size = 0;

    files = malloc(run_count * sizeof(FILE *));
    heap = malloc(run_count * sizeof(heap_node_t));

    for (int i = 0; i < run_count; i++) {
        files[i] = fopen(run_files[i], "r");
        if (fscanf(files[i], "%d", &heap[heap_size].value) == 1) {
            heap[heap_size].file_index = i;
            heap_size++;
        }
    }

    for (int i = heap_size / 2 - 1; i >= 0; i--) {
        heapify(heap, heap_size, i);
    }

    out = fopen(output_file, "w");

    while (heap_size > 0) {
        heap_node_t root = heap[0];
        fprintf(out, "%d\n", root.value);

        if (fscanf(files[root.file_index], "%d", &heap[0].value) != 1) {
            heap[0] = heap[heap_size - 1];
            heap_size--;
        }

        heapify(heap, heap_size, 0);
    }

    for (int i = 0; i < run_count; i++) {
        fclose(files[i]);
        remove(run_files[i]);
        free(run_files[i]);
    }

    free(files);
    free(heap);
    fclose(out);

    return 0;
}

