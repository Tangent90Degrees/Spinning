#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "scene/camera.h"
#include "scene/cube.h"
#include "scene/sphere.h"
#include "scene/octahedron.h"
#include "scene/donut.h"
#include "rendering/renderer.h"
#include <sys/ioctl.h>

ENGINE_HEADER_BEGIN

class Application {
public:
    Application(/* args */);
    ~Application();

private:
    Render __render;
};

ENGINE_HEADER_END

#endif