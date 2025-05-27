#include "Core/Application.h"
#include <iostream>
#include <cstdlib>  // Para system()

int main() {
    Application app;

    // Ejecuta el script para compilar shaders (ajusta la ruta si es necesario)
    system("shaders\\compileshaders.bat");

    try {
        //Se lanza el inicio de la aplicacion
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
