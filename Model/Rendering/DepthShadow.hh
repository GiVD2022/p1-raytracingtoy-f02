#pragma once


#include "ShadingStrategy.hh"


class DepthShadow :public ShadingStrategy
{
public:
    DepthShadow(){};
    vec3 shading(shared_ptr<Scene> scene, HitInfo& info, vector<shared_ptr<Light>> lights, vec3 lookFrom, vec3 globalLight) override;
    ~DepthShadow() {};
};

