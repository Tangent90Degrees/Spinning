#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "rendering/renderer.h"

ENGINE_HEADER_BEGIN

class application {
public:
    application(/* args */);
    ~application();

private:
    render __render;
};

ENGINE_HEADER_END

#endif