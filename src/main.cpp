#include "Core/Application.h"
#include <iostream>
#include <cstdlib>  // Para system()


int main() {
    Application app;

	std::cout << "[!] Compilando shaders:" << std::endl;
    system(shadersdir);
    std::cout << std::endl << "Completado." << std::endl << std::endl;

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
