#ifndef UTILS_H
#define UTILS_H

#include <GLFW/glfw3.h>
#include <math.h>

class Utils {
  public:
    static GLfloat degToRad(GLfloat degree){
      return (degree * M_PI) / 180.0f;
    }
};

#endif // UTILS_H