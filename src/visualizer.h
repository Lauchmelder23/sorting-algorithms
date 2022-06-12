#ifndef _VISUALIZER_H
#define _VISUALIZER_H

#include <stdint.h>

typedef struct 
{
    const char* name;

    int(*init)();
    void(*render)(void);
    void(*exit)(void);
} Visualizer;

struct VisualizerData {
    int* array;
    size_t array_size;
} visualizer_data;

#endif