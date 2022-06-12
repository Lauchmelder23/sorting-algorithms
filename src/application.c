#include "application.h"

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "visualizers/histogram.h"
#include "algorithms.h"

void shuffle(int* array, size_t n);

void framebuffer_changed(GLFWwindow* window, int width, int height);

int init_application(Application* app, int width, int height, const char* title)
{
    const char* err;
    GLFWwindow* window;

    glfwInit();

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(window == NULL)
    {
        glfwGetError(&err);

        fprintf(stderr, "Failed to create window: %s\n", err);
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_changed);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    app->window = window;

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "Failed to load OpenGL loader\n");
        glfwSetWindowShouldClose(window, GL_TRUE);
        return -1;
    }

    glViewport(0, 0, width, height);

    app->active_visualizer = &histogram_visualizer;

    visualizer_data.array_size = 1500;
    visualizer_data.array = (int*)malloc(visualizer_data.array_size * sizeof(int));
    // TODO: Check if NULL

    for(int i = 0; i < visualizer_data.array_size; i++)
    {
        visualizer_data.array[i] = i;
    }
    shuffle(visualizer_data.array, visualizer_data.array_size);

    if(!app->active_visualizer->init())
    {
        fprintf(stderr, "Failed to initialize visualizer \"%s\"", app->active_visualizer->name);
        glfwSetWindowShouldClose(window, GL_TRUE);
        return -1;
    }

    return 0;
}

void destroy_application(Application* app)
{
    app->active_visualizer->exit();

    if(app->window)
        glfwDestroyWindow(app->window);
}

void run_application(Application* app)
{
    GLFWwindow* window = app->window;

    // bubblesort(app);
    mergesort(app, 0, visualizer_data.array_size - 1);

    while(!glfwWindowShouldClose(window))
    {
        update_screen(app);
    }
}

int update_screen(Application* app)
{
    glfwPollEvents();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    app->active_visualizer->render();

    glfwSwapBuffers(app->window);
    return glfwWindowShouldClose(app->window);
}

void framebuffer_changed(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void shuffle(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}