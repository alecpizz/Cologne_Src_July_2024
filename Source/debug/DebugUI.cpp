#include "DebugUI.h"

#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

DebugUI::DebugUI(GLFWwindow *window)
{
     IMGUI_CHECKVERSION();
     ImGui::CreateContext();
     ImGuiIO &io = ImGui::GetIO();
     io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

     ImGui::StyleColorsDark();

     ImGui_ImplGlfw_InitForOpenGL(window, true);
     ImGui_ImplOpenGL3_Init();
     sample_color[0] = 0.0f;
     sample_color[1] = 0.0f;
     sample_color[2] = 0.0f;
     sample_color[3] = 1.0f;
     CG_CORE_INFO("Debug UI Initialized.");
}

DebugUI::~DebugUI()
{
     ImGui_ImplOpenGL3_Shutdown();
     ImGui_ImplGlfw_Shutdown();
     ImGui::DestroyContext();
     CG_CORE_INFO("Cleaned up DebugUI");
}

void DebugUI::preRender()
{
     ImGui_ImplOpenGL3_NewFrame();
     ImGui_ImplGlfw_NewFrame();
     ImGui::NewFrame();
     buildUI();
}

void DebugUI::render()
{
     ImGui::End();
     ImGui::Render();
}

void DebugUI::postRender()
{
     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool DebugUI::isKeyboardAvaliable()
{
     return ImGui::GetIO().WantCaptureKeyboard == false;
}

bool DebugUI::isMouseAvaliable()
{
     return ImGui::GetIO().WantCaptureKeyboard == true;
}

void DebugUI::buildUI()
{
     ImGui::Begin("Cologne Debug", &ui_active, ImGuiWindowFlags_MenuBar);
     if (ImGui::BeginMenuBar())
     {
          if (ImGui::BeginMenu("File"))
          {
               ImGui::EndMenu();
          }
          ImGui::EndMenuBar();
     }

     ImGui::Text("FPS %.3f", ImGui::GetIO().Framerate);
     ImGui::ColorEdit4("Color", sample_color);
     float samples[100];
     for (int n = 0; n < 100; n++)
          samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
     ImGui::PlotLines("Samples", samples, 100);

     // Display contents in a scrolling region
     ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
}
