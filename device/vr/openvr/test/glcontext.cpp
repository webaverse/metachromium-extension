#include "device/vr/openvr/test/glcontext.h"
#include "device/vr/openvr/test/out.h"

GLFWwindow *initGl() {
  // if (!*ppWindow) {
    getOut() << "init gl 1" << std::endl;
    auto result = glfwInit();
    getOut() << "init gl 2" << std::endl;
    if (result) {
      // nothing
    } else {
      getOut() << "failed to initialize glew: " << (void *)result << std::endl;
      abort();
    }
    getOut() << "init gl 3" << std::endl;

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_NONE);
    auto window = glfwCreateWindow(
      1,
      1,
      "openvroffscreen",
      nullptr,
      nullptr
    );
    getOut() << "init gl 4" << std::endl;
    glfwMakeContextCurrent(window);
    getOut() << "init gl 5" << std::endl;

    glewExperimental = true;
    auto result2 = glewInit();
    if (result2 == GLEW_OK) {
      // nothing
    } else {
      getOut() << "failed to initialize glew: " << (void *)result << std::endl;
      abort();
    }
    getOut() << "init gl 6 " << (void *)window << std::endl;
    return window;
  // }
}
GLFWwindow *initGlSub() {
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_NONE);
  auto subWindow = glfwCreateWindow(
    1,
    1,
    "openvroffscreen2",
    nullptr,
    // nullptr
    *ppWindow
  );
  getOut() << "share gl context " << subWindow << " " << (void *)(*ppWindow) << std::endl;
  glfwMakeContextCurrent(subWindow);
  return subWindow;
}