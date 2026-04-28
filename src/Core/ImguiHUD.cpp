#include "../Renderer/SceneMaster.h"
#include "ImguiHUD.h"
#include "../../thirdparty/ImGuizmo-master/ImGuizmo.h"


void InitImgui() {


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

    // Menú superior 
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Load Model")) {

                //LoaderModels::loadModel("cubo", MODEL_PATHC);

            }
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

            ImGui::Text("Delta Time: (%g)", Application::deltaTime);
            ImGui::Text("FPS: (%g)", 1.0f/Application::deltaTime);


            if (ImGui::Button("Boton")) {
                // Acción a realizar cuando se presiona el botón
                std::cout<<"Boton presionado\n";
            }


        }
        ImGui::End();
    }

    //ImGui::Separator();
    // ── Tus ventanas dockeables (puedes moverlas y pegarlas a los bordes) ──
    static int selectedMeshIndex = -0;   // ← selección global

    ImGui::Begin("Scene Hierarchy");
    for (size_t i = 0; i < SceneMaster::SceneMesheslist.size(); ++i) {
        bool isSelected = (i == selectedMeshIndex);
        if (ImGui::Selectable(SceneMaster::SceneMesheslist[i].name.c_str(), isSelected)) {
            selectedMeshIndex = (int)i;
            SceneMaster::selectedIndex.push_back(i);
        }
    }
    ImGui::End();


    ImGui::Begin("Inspector");
    if (!SceneMaster::SceneMesheslist.empty() && selectedMeshIndex < SceneMaster::SceneMesheslist.size()) {
        auto& mesh = SceneMaster::SceneMesheslist[selectedMeshIndex];

        ImGui::SeparatorText(mesh.name.c_str());


        ImGui::DragFloat3("Posicion", mesh.position, 0.1f);
        ImGui::DragFloat3("Camara", SceneMaster::CameraPositionInit, 0.1f);

        ImGui::DragFloat3("Giro", mesh.rotation, 1.0f);
        ImGui::DragFloat3("Escala", mesh.scale, 0.1f);


        ImGui::Text("Objeto seleccionado: %s", mesh.name.c_str());
    }
    else {
        ImGui::Text("No hay objetos en la escena");
    }
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

    const ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
};

