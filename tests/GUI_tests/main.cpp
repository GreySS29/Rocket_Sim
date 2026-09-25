#include <cstdio>

#include <GLFW/glfw3.h>

#include "../../external/imgui/imgui.h"
#include "../../external/imgui/backends/imgui_impl_glfw.h"
#include "../../external/imgui/backends/imgui_impl_opengl3.h"

int main()
{
    if (!glfwInit()) {
        std::fprintf(stderr, "GLFW initialization failed\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(
        1280,
        720,
        "Rocket Simulator",
        nullptr,
        nullptr
    );

    if (!window) {
        std::fprintf(stderr, "Window creation failed\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool simulation_running = false;
    float simulation_time = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        if (simulation_running) {
            simulation_time += 0.016f;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Simulation control");

        ImGui::Text("Rocket simulator");

        ImGui::Checkbox(
            "Run simulation",
            &simulation_running
        );

        ImGui::Text(
            "Time: %.2f s",
            simulation_time
        );

        if (ImGui::Button("Reset")) {
            simulation_time = 0.0f;
            simulation_running = false;
        }

        ImGui::End();

        ImGui::Render();

        int framebuffer_width = 0;
        int framebuffer_height = 0;

        glfwGetFramebufferSize(
            window,
            &framebuffer_width,
            &framebuffer_height
        );

        glViewport(
            0,
            0,
            framebuffer_width,
            framebuffer_height
        );

        glClearColor(
            0.08f,
            0.08f,
            0.10f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(
            ImGui::GetDrawData()
        );

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}