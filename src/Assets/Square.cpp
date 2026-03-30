
#include "Square.h"



std::vector<uint32_t> Cuadrado::GetIndex() {
    std::vector<uint32_t> indices = { 0, 1, 2, 2, 3, 0 }; // cuadrado con dos triángulos 0-1-2, 2-3-0
    return indices;
}


 std::vector<Vertex> Cuadrado::createsquare(float lado) {

     std::vector<Vertex> vertices = {
    //Posicion en -1,1 de la pantalla y color en RGB
        {{-lado / 2, -lado / 2}, {1.0f, 0.0f, 0.0f}},
        {{ lado / 2, -lado / 2}, {0.0f, 1.0f, 0.0f}},
        {{ lado / 2,  lado / 2}, {0.0f, 0.0f, 1.0f}},
        {{-lado / 2,  lado / 2}, {1.0f, 1.0f, 1.0f}},
     };

    return vertices;
};