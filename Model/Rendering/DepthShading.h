#pragma once

#include "ShadingStrategy.hh"


class DepthShading: public ShadingStrategy
{
public:
    DepthShading() {};
    vec3 shading(shared_ptr<Scene> scene, HitInfo& info, vector<shared_ptr<Light>> lights, vec3 lookFrom, vec3 globalLight) override;
    ~DepthShading(){};
};
