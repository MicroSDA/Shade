#include "stdafx.h"
#include "ImGuiLayer.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "Vendors/glad/glad.h"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl.h>

namespace se
{
    ImGuiLayer::ImGuiLayer(const std::string& name, se::Scene* scene) : se::Layer(name, scene)
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::OnCreate()
    {


        se::EventManager::RegLayerEventCallback(se::EventType::SDL_KEYDOWN, GetScene(), this,
            [&](se::Event const& event) {

                ImGuiIO& io = ImGui::GetIO();

                io.MouseDown[0] = false;
                io.MouseDown[1] = false;
                io.MouseDown[2] = false;

                switch (event.type)
                {
                case SDL_MOUSEWHEEL:
                {
                    if (event.wheel.x > 0) io.MouseWheelH += 1;
                    if (event.wheel.x < 0) io.MouseWheelH -= 1;
                    if (event.wheel.y > 0) io.MouseWheel += 1;
                    if (event.wheel.y < 0) io.MouseWheel -= 1;

                    break;
                }
                case SDL_MOUSEBUTTONDOWN:
                {
                    if (event.button.button == SDL_BUTTON_LEFT) io.MouseDown[0] = true;
                    if (event.button.button == SDL_BUTTON_RIGHT) io.MouseDown[1] = true;
                    if (event.button.button == SDL_BUTTON_MIDDLE) io.MouseDown[2] = true;
                    break;
                }
                case SDL_TEXTINPUT:
                {
                    io.AddInputCharactersUTF8(event.text.text);
                    break;
                }
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                {
                    int key = event.key.keysym.scancode;
                    IM_ASSERT(key >= 0 && key < IM_ARRAYSIZE(io.KeysDown));
                    io.KeysDown[key] = (event.type == SDL_KEYDOWN);
                    io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
                    io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
                    io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
#ifdef _WIN32
                    io.KeySuper = false;
#else
                    io.KeySuper = ((SDL_GetModState() & KMOD_GUI) != 0);
#endif
                    break;
                }
                }

                return false;
            });


     
    }
    void ImGuiLayer::OnInit()
    {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplSDL2_InitForOpenGL(se::WindowManager::GetWindow().Handler, se::WindowManager::GetContext());
        ImGui_ImplOpenGL3_Init("#version 440");

    }
    void ImGuiLayer::OnUpdate(const se::Timer& deltaTime)
    {

    }
    void ImGuiLayer::OnRender()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(se::WindowManager::GetWindow().Handler);
        ImGui::NewFrame();

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Shade Editor");                          // Create a window called "Hello, world!" and append into it.

          
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        ImGui::Render();
      
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  
    }
    void ImGuiLayer::OnDelete()
    {
        ImGui::DestroyContext();
    }
}