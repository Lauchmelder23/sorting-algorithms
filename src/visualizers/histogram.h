#ifndef _HISTOGRAM_H
#define _HISTOGRAM_H

#include "visualizer.h"

int histogram_init();
void histogram_render(void);
void histogram_exit(void);

static Visualizer histogram_visualizer = {
    .name = "Histogram",
    .init = histogram_init,
    .render = histogram_render,
    .exit = histogram_exit
};

#endif