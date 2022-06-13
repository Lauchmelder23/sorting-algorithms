#include "application.h"

void insertionsort(Application* app)
{
    for(int i = 1; i < visualizer_data.array_size; i++)
    {
        int new = visualizer_data.array[i];
        int k = i;

        while(k > 1 && visualizer_data.array[k - 1] > new)
        {
            visualizer_data.array[k] = visualizer_data.array[k - 1];
            k--;

            if(update_screen(app))
                return;
        }

        visualizer_data.array[k] = new;

        if(update_screen(app))
                return;
    }
}