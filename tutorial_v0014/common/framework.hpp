//
// Created by Oleg Baskakov on 4/27/15.
//

#ifndef ALMATY3D_FRAMEWORK_HPP
#define ALMATY3D_FRAMEWORK_HPP

// Include standard headers
#include <cstdio>
#include <cstdlib>
#include <vector>

// Include GLFW
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
using namespace glm;

#include "../common/shader.hpp"
#include "../common/texture.hpp"
#include "../common/controls.hpp"
#include "../common/objloader.hpp"
#include "../common/vboindexer.hpp"
#include "../common/text2D.hpp"
#include "../common/tangentspace.hpp"
#include "../common/quaternion_utils.hpp"


GLFWwindow* initWindow(const char *windowTitle) {

    GLFWwindow *window;

    // Initialise GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

// Open a window and create its OpenGL context
    window = glfwCreateWindow(1024, 768, windowTitle, NULL, NULL);
    if (window == NULL) {
        fprintf(stderr,
                "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);

// Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetCursorPos(window, 1024 / 2, 768 / 2);

    return window;
}

#endif //ALMATY3D_FRAMEWORK_HPP
