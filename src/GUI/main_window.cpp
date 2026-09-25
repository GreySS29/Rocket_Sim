#include "../../include/GUI/MainWindow.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl2.h>

#include <iostream>
#include <cstdlib>

void MainWindow::init()
{
    if (!glfwInit()) {
        std::cerr << "GLFW: init failed\n";
        std::exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    window = glfwCreateWindow(440, 340, "Rocket Sim", nullptr, nullptr);
    if (!window) {
        std::cerr << "GLFW: window creation failed\n";
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();
}

void MainWindow::shutdown()
{
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    window = nullptr;
}

void MainWindow::renderUI(bool& decided, Choice& choice)
{
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    int w = 0, h = 0;
    glfwGetFramebufferSize(window, &w, &h);

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(w), static_cast<float>(h)));

    const ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;

    ImGui::Begin("Rocket Sim Menu", nullptr, flags);

    ImGui::Dummy(ImVec2(0.0f, h * 0.08f));

    const float buttonWidth = 260.0f;

    ImGui::SetCursorPosX((w - buttonWidth) * 0.5f);
    if (ImGui::Button("Start (Auto)", ImVec2(buttonWidth, 45))) {
        decided = true;
        choice = Choice::Auto;
    }

    ImGui::Dummy(ImVec2(0.0f, 10.0f));

    ImGui::SetCursorPosX((w - buttonWidth) * 0.5f);
    if (ImGui::Button("Start (Manual)", ImVec2(buttonWidth, 45))) {
        decided = true;
        choice = Choice::Manual;
    }

    ImGui::Dummy(ImVec2(0.0f, 10.0f));

    ImGui::SetCursorPosX((w - buttonWidth) * 0.5f);
    if (ImGui::Button("Start (Live / Wemos)", ImVec2(buttonWidth, 45))) {
        decided = true;
        choice = Choice::Live;
    }

    ImGui::Dummy(ImVec2(0.0f, 10.0f));

    ImGui::SetCursorPosX((w - buttonWidth) * 0.5f);
    if (ImGui::Button("Exit", ImVec2(buttonWidth, 45))) {
        decided = true;
        choice = Choice::Exit;
    }

    ImGui::Dummy(ImVec2(0.0f, 16.0f));
    ImGui::TextWrapped(
        "Auto - playback with timer. Manual - Space to pause, "
        "Left/Right to step. Live - control via Wemos D1 over network.");

    ImGui::End();

    ImGui::Render();

    glViewport(0, 0, w, h);
    glClearColor(0.15f, 0.15f, 0.18f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

MainWindow::Choice MainWindow::run()
{
    init();

    bool decided = false;
    Choice choice = Choice::Exit; 

    while (!glfwWindowShouldClose(window) && !decided) {
        glfwPollEvents();
        renderUI(decided, choice);
        glfwSwapBuffers(window);
    }

    shutdown();
    return choice;
}