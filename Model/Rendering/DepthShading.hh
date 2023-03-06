#pragma once

#include "ShadingStrategy.hh"

class DepthShading: public ShadingStrategy
{
public:
    DepthShading() {};
    vec3 shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom) override;
    ~DepthShading(){};
};

