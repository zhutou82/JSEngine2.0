#include "imguiLayer.h"
#include "JSEngine/Platform/WindowsWindow.h"
#include "JSEngine/Platform/Opengl/OpenglRenderer.h"
#include "JSEngine/Application.h"
#include "glad/glad.h"


//#include ""



namespace JSEngine
{

    void imguiLayer::OnAttach()
    {
       
        ImGui::CreateContext();
        // Setup Platform/Renderer bindings
        ImGui_ImplOpenGL3_Init(JS_GL_VERSION);

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



        //io.DisplayFramebufferScale = ImVec2((float)(g_AppWindow->GetFrameBufferWidth())  / g_AppWindow->GetWidth(),
        //                                    (float)(g_AppWindow->GetFrameBufferHeight()) / g_AppWindow->GetHeight());

    }

    void imguiLayer::OnDetach()
    {
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
    }
    void imguiLayer::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        //Dispatch
        dispatcher.Dispatch<MouseButtonPressEvent>(JS_BIND_EVENT(MousePressedEvent));
        dispatcher.Dispatch<MouseButtonReleaseEvent>(JS_BIND_EVENT(MouseReleasedEvent));
        dispatcher.Dispatch<MouseScrollEvent>(JS_BIND_EVENT(MouseScrolledEvent));
        dispatcher.Dispatch<MouseMoveEvent>(JS_BIND_EVENT(MouseMovedEvent));
        dispatcher.Dispatch<KeyPressEvent>(JS_BIND_EVENT(KeyPressedEvent));
        dispatcher.Dispatch<KeyReleseEvent>(JS_BIND_EVENT(KeyReleasedEvent));
        dispatcher.Dispatch<KeyCharEvent>(JS_BIND_EVENT(KeyTypedEvent));
        dispatcher.Dispatch<WindowReSizeEvent>(JS_BIND_EVENT(WindowReziedEvent));
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
        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
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

    void imguiLayer::OnUpdate()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        ImGuiIO& io = ImGui::GetIO();

        //set up window size
        io.DisplaySize = ImVec2((float)(g_AppWindow->GetWidth()),
                                (float)(g_AppWindow->GetHeight()));

        float currentTime = (g_Application->GetWindow()->GetSystemCurrentTime());
        io.DeltaTime = m_imguiLayerTime > 0.0 ? (currentTime - m_imguiLayerTime) : (1.0f / 60.0f);
        m_imguiLayerTime = currentTime;

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool showWindow = true;
        static bool show_another_window = false;
        ImGui::ShowDemoWindow(&showWindow);

        //ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


        //// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        //{
        //    static float f = 0.0f;
        //    static int counter = 0;

        //    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        //    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        //    ImGui::Checkbox("Demo Window", &showWindow);      // Edit bools storing our window open/close state
        //    ImGui::Checkbox("Another Window", &show_another_window);

        //    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        //    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        //    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        //        counter++;
        //    ImGui::SameLine();
        //    ImGui::Text("counter = %d", counter);

        //    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        //    ImGui::End();
        //}

        //if (show_another_window)
        //{
        //    ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        //    ImGui::Text("Hello from another window!");
        //    if (ImGui::Button("Close Me"))
        //        show_another_window = false;
        //    ImGui::End();
        //}


        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        
    }

}