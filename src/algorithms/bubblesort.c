#include "application.h"

void bubblesort(Application* app)
{
    for(size_t n = visualizer_data.array_size; n > 1; n--)
    {
        for(int i = 0; i < n - 1; i++)
        {
            if(visualizer_data.array[i] > visualizer_data.array[i + 1])
            {
                int tmp = visualizer_data.array[i];
                visualizer_data.array[i] = visualizer_data.array[i + 1];
                visualizer_data.array[i + 1] = tmp;
            }

            if(update_screen(app))
                return;
        }
    }
}