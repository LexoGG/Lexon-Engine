// Window.cpp
#include "Window.h"


void Window::init() {

    

    // Se inicializa la libreria de renderizado de ventanas GLFW
    glfwInit();
    
    //glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    /* Esta función establece sugerencias para la siguiente llamada a glfwCreateWindow .
        Una vez establecidas, las sugerencias conservan sus valores hasta que se modifiquen
        mediante una llamada a esta función o a glfwDefaultWindowHints , o hasta que se cierre la biblioteca.*/ //glfwGetPrimaryMonitor()
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);


    // Creacion de la ventana como objeto GLFWwindow*, definicion de tamaño y nombre
    window = glfwCreateWindow(WIDTH, HEIGHT, "Lexon Engine", nullptr, nullptr); //para pantalla completa  glfwGetPrimaryMonitor()

    // Si la variable window esta vacia, cierra la ventana y lanza un error
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    else {
        std::cout << "\t Ventana creada correctamente." << std::endl;
        std::cout << "\t Ventana almacenada en: "<< window << std::endl;
    };

    /*Se asocia el objeto window con la direccion de memoria de la clase window. El this es un puntero 
    que se refiere a la direccion de memoria en la clase que estamos en este caso, Window.
    esa direccion de memoria se puede obtener usando glfwGetWindowUserPointer(window)*/
    glfwSetWindowUserPointer(window, this);

    // Se establece una función de callback que se ejecutará automáticamente cuando cambie el tamaño del framebuffer de la ventana
    // Esta función indica a GLFW que, cuando cambie el tamaño del framebuffer de window, debe llamar a la función framebufferResizeCallback.
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

}

// Limpieza de datos relacionados a la ventana
void Window::cleanup() {

    // Se destruye la ventana
    glfwDestroyWindow(window);

    //Se cierra la biblioteca GLFW
    glfwTerminate();
}


void Window::pollEvents() {
    glfwPollEvents();
}

// Funcion para obtener la ventana desde fuera ya que es privada
bool Window::shouldClose() const { return glfwWindowShouldClose(window); }

GLFWwindow* Window::getGLFWwindow() { return window; }

bool Window::wasResized() {
    return framebufferResized;
}

void Window::resetResizedFlag() {
    framebufferResized = false;
}

void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    app->framebufferResized = true;
}

bool Window::getFramebufferResized() {
	return framebufferResized;
}

GLFWwindow* Window::window = nullptr;  
bool Window::framebufferResized = false;