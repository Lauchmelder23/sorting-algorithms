#include "algorithms.h"
#include "application.h"

#include <stdlib.h>

static void merge(Application* app, size_t left, size_t middle, size_t right);
static void mergesort_rec(Application* app, size_t left, size_t right);

static int* tmp = NULL;

void mergesort(Application* app)
{
    tmp = (int*)malloc(visualizer_data.array_size * sizeof(int));
    mergesort_rec(app, 0, visualizer_data.array_size - 1);
    free(tmp);
}

static void mergesort_rec(Application* app, size_t left, size_t right)
{
    if(right > left)
    {
        size_t middle = (left + right) / 2;
        mergesort_rec(app, left, middle);
        mergesort_rec(app, middle + 1, right);

        merge(app, left, middle, right);
    }
}

static void merge(Application* app, size_t left, size_t middle, size_t right)
{
    for(size_t k = left; k <= middle; k++)
    {
        tmp[k] = visualizer_data.array[k];
    }

    for(size_t k = middle + 1; k <= right; k++)
    {
        tmp[right + middle + 1 - k] = visualizer_data.array[k];
    }

    size_t i = left;
    size_t j = right;
    size_t k = left;

    while(i < j)
    {
        if(tmp[i] <= tmp[j])
        {
            visualizer_data.array[k] = tmp[i];
            i++;
        }
        else
        {
            visualizer_data.array[k] = tmp[j];
            j--;
        }

        k++;

        if(update_screen(app))
            return;
    }

    visualizer_data.array[right] = tmp[i];
    update_screen(app);
}