#include "application.h"

int main(int argc, char** argv)
{
    Application app = { 0 };
    init_application(&app, 800, 800, "Sorting Algorithms");

    run_application(&app);

    destroy_application(&app);
    return 0;
}