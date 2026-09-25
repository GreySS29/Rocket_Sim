#include "../../include/GUI/MainWindow.h"
#include "../../include/GUI/Display.h"
 
#include "../../external/imgui/imgui.h"
#include "../../external/imgui/backends/imgui_impl_glfw.h"
#include "../../external/imgui/backends/imgui_impl_opengl2.h"
 
#include <iostream>
#include <cstdlib>
 
MainWindow::MainWindow(Display& d) : display(d) {}
 
void MainWindow::init()
{
    if (!glfwInit()) {
        std::cerr << "GLFW: init failed\n";
        std::exit(EXIT_FAILURE);
    }
 
    // ImGui с opengl2-бэкендом не требует core-контекста,
    // ставим то же окружение, что и для остального рендера.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
 
    window = glfwCreateWindow(420, 260, "Rocket Sim", nullptr, nullptr);
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
 
void MainWindow::renderUI(bool& startPressed)
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
 
    ImGui::Dummy(ImVec2(0.0f, h * 0.25f));
 
    const float buttonWidth = 140.0f;
 
    ImGui::SetCursorPosX((w - buttonWidth) * 0.5f);
    if (ImGui::Button("Start", ImVec2(buttonWidth, 45))) {
        startPressed = true;
    }
 
    ImGui::Dummy(ImVec2(0.0f, 15.0f));
 
    ImGui::SetCursorPosX((w - buttonWidth) * 0.5f);
    if (ImGui::Button("Exit", ImVec2(buttonWidth, 45))) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
 
    ImGui::End();
 
    ImGui::Render();
 
    glViewport(0, 0, w, h);
    glClearColor(0.15f, 0.15f, 0.18f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}
 
void MainWindow::run()
{
    init();
 
    bool startPressed = false;
 
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        renderUI(startPressed);
        glfwSwapBuffers(window);
 
        if (startPressed) {
            break;
        }
    }
 
    // Закрываем окно меню и его GL-контекст ДО того как Display
    // создаст свой собственный (свой контекст и свой цикл событий).
    shutdown();
 
    if (startPressed) {
        display.run(0, nullptr);
    }
}