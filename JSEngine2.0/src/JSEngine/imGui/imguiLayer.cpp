#include "PCH.h"
#include "imguiLayer.h"
#include "JSEngine/Platform/WindowsWindow.h"
#include "JSEngine/Application.h"
#include "glad/glad.h"

#include "imgui.h"
#include "imconfig.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"


namespace JSEngine
{

    void imguiLayer::OnAttach() 
    {
        ImGui::CreateContext();

        // Setup back-end capabilities flags
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(g_AppWindowHandle, false);
        ImGui_ImplOpenGL3_Init(JS_GL_VERSION);
    }

    void imguiLayer::OnDetach()
    {
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void imguiLayer::OnEvent(Event& e)
    {
        //EventDispatcher dispatcher(e);
        ////Dispatch
        //dispatcher.Dispatch<MouseButtonPressEvent  >(JS_BIND_EVENT(MousePressedEvent));
        //dispatcher.Dispatch<MouseButtonReleaseEvent>(JS_BIND_EVENT(MouseReleasedEvent));
        //dispatcher.Dispatch<MouseScrollEvent       >(JS_BIND_EVENT(MouseScrolledEvent));
        //dispatcher.Dispatch<MouseMoveEvent         >(JS_BIND_EVENT(MouseMovedEvent));
        //dispatcher.Dispatch<KeyPressEvent          >(JS_BIND_EVENT(KeyPressedEvent));
        //dispatcher.Dispatch<KeyReleseEvent         >(JS_BIND_EVENT(KeyReleasedEvent));
        //dispatcher.Dispatch<KeyCharEvent           >(JS_BIND_EVENT(KeyTypedEvent));
        //dispatcher.Dispatch<WindowReSizeEvent      >(JS_BIND_EVENT(WindowReziedEvent));
    }

    void imguiLayer::Begin()
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void imguiLayer::OnRenderUpdate()
    {
        static bool showWindow = true;
        ImGui::ShowDemoWindow(&showWindow);
    }

    void imguiLayer::End()
    {
        // Rendering
        ImGui::Render();
        
        //glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO();
        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    bool imguiLayer::MousePressedEvent(MouseButtonPressEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = true;
        return false;
    }

    bool imguiLayer::MouseReleasedEvent(MouseButtonReleaseEvent & e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = false;
        return false;
    }

    bool imguiLayer::MouseScrolledEvent(MouseScrollEvent & e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheel += e.GetMouseYOffSet();
        io.MouseWheelH += e.GetMouseXOffSet();
        return false;
    }

    bool imguiLayer::MouseMovedEvent(MouseMoveEvent & e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(e.GetMouseXCoordinate(), e.GetMouseYCoordinate());
        return false;
    }

    bool imguiLayer::KeyPressedEvent(KeyPressEvent & e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = true;

        // Modifiers are not reliable across systems
        io.KeyCtrl  = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT]   || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt   = io.KeysDown[GLFW_KEY_LEFT_ALT]     || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        return false;
    }

    bool imguiLayer::KeyReleasedEvent(KeyReleseEvent & e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = false;

        return false;
    }

    bool imguiLayer::KeyTypedEvent(KeyCharEvent & e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddInputCharacter(e.GetKeyCode());
        return false;
    }

    bool imguiLayer::WindowReziedEvent(WindowReSizeEvent & e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)e.GetWidth(),(float)e.GetHeight()); 
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, 1, 1);

        return false;
    }

    void imguiLayer::OnUpdate(TimeStep delta)
    {
        
    }

}