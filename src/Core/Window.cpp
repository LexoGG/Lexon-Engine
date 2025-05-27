// Window.cpp
#include "Window.h"
#include <stdexcept>

void Window::init() {

    // Se inicializa la libreria de renderizado de ventanas GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    /* Esta funci�n establece sugerencias para la siguiente llamada a glfwCreateWindow .
        Una vez establecidas, las sugerencias conservan sus valores hasta que se modifiquen
        mediante una llamada a esta funci�n o a glfwDefaultWindowHints , o hasta que se cierre la biblioteca.*/ 
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // Creacion de la ventana como objeto GLFWwindow*, definicion de tama�o y nombre
    window = glfwCreateWindow(WIDTH, HEIGHT, "Lexon Engine", nullptr, nullptr);

    // Si la variable window esta vacia, cierra la ventana y lanza un error
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    /*Se asocia el objeto window con la direccion de memoria de la clase window. El this es un puntero 
    que se refiere a la direccion de memoria en la clase que estamos en este caso, Window.
    esa direccion de memoria se puede obtener usando glfwGetWindowUserPointer(window)*/
    glfwSetWindowUserPointer(window, this);

    // Se establece una funci�n de callback que se ejecutar� autom�ticamente cuando cambie el tama�o del framebuffer de la ventana
    // Esta funci�n indica a GLFW que, cuando cambie el tama�o del framebuffer de window, debe llamar a la funci�n framebufferResizeCallback.
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

    /*El framebuffer es el �rea de memoria que contiene los p�xeles que se van a mostrar en pantalla. En GLFW, su tama�o puede 
        ser distinto del tama�o de la ventana, especialmente en pantallas con DPI alto (HiDPI), como las pantallas Retina de Apple.*/
}

// Limpieza de datos relacionados a la ventana
void Window::cleanup() {

    // Se destruye la ventana
    glfwDestroyWindow(window);

    //Se cierra la biblioteca GLFW
    glfwTerminate();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void Window::pollEvents() const {
    glfwPollEvents();
}

// Funcion para obtener la ventana desde fuera ya que es privada
GLFWwindow* Window::getGLFWwindow() const {
    return window;
}

bool Window::wasResized() const {
    return framebufferResized;
}

void Window::resetResizedFlag() {
    framebufferResized = false;
}

void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto appWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    appWindow->framebufferResized = true;
}
