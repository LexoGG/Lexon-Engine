# Minimo de version de cmake compatible
cmake_minimum_required(VERSION 3.22)

project(Lexon-Engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(LEXON_ENABLE_VALIDATION "Enable Vulkan Validation Layers" ON)

find_package(Vulkan REQUIRED)

include(FetchContent)

FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.4)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git GIT_TAG 11.1.1)
FetchContent_MakeAvailable(fmt)

# ==================== Fuentes ====================
file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp" "src/*.h")

file(GLOB IMGUI_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui/backends/imgui_impl_glfw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui/backends/imgui_impl_vulkan.cpp"
)

add_library(LexonEngine STATIC ${ENGINE_SOURCES} ${IMGUI_SOURCES})

target_include_directories(LexonEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui/backends
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/tinyloader
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/stb
)

target_link_libraries(LexonEngine PUBLIC Vulkan::Vulkan glfw fmt::fmt)

# ==================== Shaders ====================
find_program(GLSLANG_VALIDATOR glslangValidator REQUIRED)

file(GLOB SHADERS "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.vert" "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.frag")

foreach(SHADER ${SHADERS})
    get_filename_component(SHADER_NAME ${SHADER} NAME)
    set(SPV_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/shaders/${SHADER_NAME}.spv")
    add_custom_command(
        OUTPUT ${SPV_OUTPUT}
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/shaders"
        COMMAND ${GLSLANG_VALIDATOR} -V ${SHADER} -o ${SPV_OUTPUT}
        DEPENDS ${SHADER}
        COMMENT "Compiling shader ${SHADER_NAME}"
    )
    list(APPEND SPIRV_SHADERS ${SPV_OUTPUT})
endforeach()

add_custom_target(CompileShaders ALL DEPENDS ${SPIRV_SHADERS})
add_dependencies(LexonEngine CompileShaders)

# ==================== Ejecutable ====================
add_executable(LexonEditor src/main.cpp)
target_link_libraries(LexonEditor PRIVATE LexonEngine)

# Copiar shaders
add_custom_command(TARGET LexonEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_BINARY_DIR}/shaders"
        "$<TARGET_FILE_DIR:LexonEditor>/shaders"
)

# ==================== Assets (Objects y Textures) - Versión robusta ====================
add_custom_command(TARGET LexonEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:LexonEditor>/Objects"
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:LexonEditor>/Textures"

    # Copia segura (no falla si la carpeta no existe)
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/Objects" "$<TARGET_FILE_DIR:LexonEditor>/Objects" || echo "WARNING: Objects folder not found"
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/Textures" "$<TARGET_FILE_DIR:LexonEditor>/Textures" || echo "WARNING: Textures folder not found"

    COMMENT "Copiando assets al directorio del ejecutable"
)

if(LEXON_ENABLE_VALIDATION)
    target_compile_definitions(LexonEngine PUBLIC LEXON_ENABLE_VALIDATION)
endif()

message(STATUS "Lexon-Engine configured successfully!")