#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "visualizer.h"

typedef struct GLFWwindow GLFWwindow;

typedef struct Application
{
    GLFWwindow* window;
    Visualizer* active_visualizer;
} Application;

int init_application(Application* app, int width, int height, const char* title);
void destroy_application(Application* app);

void run_application(Application* app);
int update_screen(Application* app);

#endif