add_executable(sortalgs
    "main.c"
    "application.c"
    "visualizer.c"
    "visualizers/histogram.c"
    "algorithms/bubblesort.c"
    "algorithms/mergesort.c"
    "algorithms/insertionsort.c"
    "algorithms/shellsort.c"
)

set(CIMGUI_SOURCE_DIR ${CMAKE_SOURCE_DIR}/vendor/cimgui)

if (WIN32)
    add_definitions("-DIMGUI_IMPL_API=extern \"C\" __declspec\(dllexport\)")
else()
    add_definitions("-DIMGUI_IMPL_API=extern \"C\" ")
endif()

add_library(cimgui STATIC
    ${CIMGUI_SOURCE_DIR}/cimgui.cpp
    ${CIMGUI_SOURCE_DIR}/imgui/imgui.cpp
    ${CIMGUI_SOURCE_DIR}/imgui/imgui_demo.cpp
    ${CIMGUI_SOURCE_DIR}/imgui/imgui_draw.cpp
    ${CIMGUI_SOURCE_DIR}/imgui/imgui_tables.cpp
    ${CIMGUI_SOURCE_DIR}/imgui/imgui_widgets.cpp

    ${CIMGUI_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
    ${CIMGUI_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
)

target_include_directories(cimgui PUBLIC
    ${CIMGUI_SOURCE_DIR}
    ${CIMGUI_SOURCE_DIR}/imgui
    ${CIMGUI_SOURCE_DIR}/imgui/backends
)

target_link_libraries(cimgui PRIVATE
    glfw
    glad
)

target_include_directories(sortalgs PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_SOURCE_DIR}/vendor/cimgui/generator/output
)

target_link_libraries(sortalgs PRIVATE
    glfw
    glad
    cglm
    cimgui
)