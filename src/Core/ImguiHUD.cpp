
#include "ImguiHUD.h"

void InitImgui() {

    //ImGuiVulkan::BeginFrame();
    ImGui::NewFrame();


    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGuiWindowFlags dockspace_flags = ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoBringToFrontOnFocus
        | ImGuiWindowFlags_NoNavFocus
        | ImGuiWindowFlags_MenuBar
        | ImGuiWindowFlags_NoBackground;

    ImGui::Begin("MainDockSpace", nullptr, dockspace_flags);
    ImGui::PopStyleVar(3);

    ImGuiID dockspace_id = ImGui::GetID("MainDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f),
        ImGuiDockNodeFlags_PassthruCentralNode);  // permite ver el 3D detrás

    // Menú superior (opcional pero útil)
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Load Model")) { /* TODO: cargar modelo */ }
            if (ImGui::MenuItem("Exit")) { /* glfwSetWindowShouldClose */ }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Asset"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Window"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Tools"))
        {
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    ImGui::End();


    static bool demoAbierta = true;
    {
        const ImGuiIO& io = ImGui::GetIO();
        const float anchoPanel = 520.f;
        ImGui::SetNextWindowPos(ImVec2(0.f, 0.f), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(anchoPanel, io.DisplaySize.y), ImGuiCond_Always);

    }
    ImGui::ShowDemoWindow(&demoAbierta);
    
    
    static bool ventanaSaludoAbierta = true;
    if (ventanaSaludoAbierta) {
        if (ImGui::Begin("Hola Mundo", &ventanaSaludoAbierta), ImGuiWindowFlags_NoTitleBar) {

            if (ImGui::Button("Boton")) {
                // Acción a realizar cuando se presiona el botón
                Window window2;
                window2.init();
                std::cout<<"Boton presionado\n";
            }


        }
        ImGui::End();
    }

    // ── Tus ventanas dockeables (puedes moverlas y pegarlas a los bordes) ──
    ImGui::Begin("Scene Hierarchy");
    ImGui::Text("Objetos en la escena");
    ImGui::Separator();
    // Aquí irán los GameObjects más adelante
    ImGui::End();


    ImGui::Begin("Inspector");
    //float rotation[3] = { UniformBuffer::CameraPositionInit.x, UniformBuffer::CameraPositionInit.x, UniformBuffer::CameraPositionInit.x };
    ImGui::DragFloat3("Posicion",UniformBuffer::CameraPositionInit);


    ImGui::DragFloat3("Giro",UniformBuffer::rotation);

    ImGui::Text("Propiedades del objeto seleccionado");
    ImGui::Separator();
    // Transform, material, etc.
    ImGui::End();

    ImGui::Begin("Console");
    ImGui::TextWrapped("Logs y mensajes aquí...");
    ImGui::End();


 // Transparent background
    ImGui::Begin("Viewport");

    ImVec2 viewportSize = ImGui::GetContentRegionAvail();

    if (viewportSize.x > 1.0f && viewportSize.y > 1.0f)
    {
        Application::GetOffscreenRenderer().Resize(
            static_cast<uint32_t>(viewportSize.x),
            static_cast<uint32_t>(viewportSize.y));

        ImGui::Image(
            Application::GetOffscreenRenderer().GetImGuiTexture(),
            viewportSize);
    }
    else
    {
        ImGui::Text("Viewport demasiado pequeño");
    }

    ImGui::End();

    // Ventana de demo (para probar todo)
    // ImGui::ShowDemoWindow();

    ImGuiVulkan::EndFrame();

    ImGui::UpdatePlatformWindows();
};

