#include "application.h"

void shellsort(Application* app)
{
    int step_size = 1;
    while (3 * step_size + 1 < visualizer_data.array_size)
    {
        step_size = 3 * step_size + 1;
        while (step_size > 0)
        {
            for(int i = step_size; i < visualizer_data.array_size; i++)
            {
                int new = visualizer_data.array[i];
                int k = i;

                while(k > step_size && visualizer_data.array[k - step_size] > new)
                {
                    visualizer_data.array[k] = visualizer_data.array[k - step_size];
                    k -= step_size;

                    if(update_screen(app))
                        return;
                }

                visualizer_data.array[k] = new;

                if(update_screen(app))
                        return;
            }

            step_size /= 3;
        }
    }
}