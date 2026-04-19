
#include "ImguiHUD.h"

void InitImgui() {

    ImGuiVulkan::BeginFrame();

    // Ancla la demo al borde izquierdo del viewport (misma ventana GLFW).
    // SetNext* afecta solo a la siguiente ventana -> ShowDemoWindow().
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
        if (ImGui::Begin("Hola Mundo", &ventanaSaludoAbierta)) {
            ImGui::Button("Boton");


        }
        ImGui::End();
    }

    ImGuiVulkan::EndFrame();
};

