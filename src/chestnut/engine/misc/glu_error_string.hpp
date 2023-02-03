// gluErrorString is the only function used from glu.h in this lib.
// Since this project uses GLAD and not GLEW it is not automatically included. 
// There is no point in including entire glu.h, especially if it can produce errors due to include order.

#pragma once

#include "glad/glad.h"

const char *gluErrorString(const GLenum err) noexcept;