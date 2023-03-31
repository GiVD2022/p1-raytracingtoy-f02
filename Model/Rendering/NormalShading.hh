#pragma once

#include "ShadingStrategy.hh"

class NormalShading: public ShadingStrategy
{
public:
    NormalShading() {};
    vec3 shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom) override;
    ~NormalShading(){};
};

