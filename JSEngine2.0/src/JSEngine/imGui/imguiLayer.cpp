#include "imguiLayer.h"
#include "JSEngine/Platform/WindowsWindow.h"
#include "JSEngine/Platform/Opengl/OpenglRenderer.h"
#include "JSEngine/Application.h"


//#include ""



namespace JSEngine
{
#define BIND_EVENT(x) std::bind(&imguiLayer::x, this, std::placeholders::_1)
    void imguiLayer::OnAttach()
    {
        ImGui::CreateContext();
        // Setup Platform/Renderer bindings
        //ImGui_ImplGlfw_InitForOpenGL(g_Application->GetWindow() , true);
        //ImGui_ImplGlfw_InitForOpenGL()
        ImGui_ImplOpenGL3_Init("#version 410");

        // Setup back-end capabilities flags
        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          // We can honor io.WantSetMousePos requests (optional, rarely used)
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;         // Enable Keyboard Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
    }

    void imguiLayer::OnDetach()
    {
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        //ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
    void imguiLayer::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        //Dispatch
        dispatcher.Dispatch<MouseButtonPressEvent>(BIND_EVENT(MousePressEventHandler));
    }

    bool imguiLayer::MousePressEventHandler(MouseButtonPressEvent& e)
    {
        int mouseButtonPressed = e.GetMouseButton();
        ImGuiIO& io = ImGui::GetIO();
        JS_CORE_TRACE("mouse pressed: {0} ", mouseButtonPressed);
        io.MouseDown[mouseButtonPressed] = true;
        e.m_MouseButtonJustPressed[mouseButtonPressed] = false;
        
        
        return true;
    }

    void imguiLayer::OnUpdate()
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(static_cast<float>(g_Application->GetWindow()->GetWidth()),
                                static_cast<float>(g_Application->GetWindow()->GetHeight()));
        //io.DisplayFramebufferScale = ImVec2(static_cast<float>(g_Window.GetFrameBufferWidth()) / g_Window.GetWidth(),
        //                                    static_cast<float>(g_Window.GetFrameBufferHeight()) / g_Window.GetHeight());


        float currentTime = static_cast<float>(g_Application->GetWindow()->GetSystemCurrentTime());
        io.DeltaTime = m_imguiLayerTime > 0.0 ? (currentTime - m_imguiLayerTime) : (1.0f / 60.0f);
        m_imguiLayerTime = currentTime;

        //JS_CORE_TRACE("{0}, {1}", g_Window.GetFrameBufferWidth(), g_Window.GetFrameBufferHeight());
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        //ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static bool showWindow = true;
        static bool show_another_window = false;
        ImGui::ShowDemoWindow(&showWindow);

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &showWindow);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //JS_CORE_TRACE("Update");

    }

}