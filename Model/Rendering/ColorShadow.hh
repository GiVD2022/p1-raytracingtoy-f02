#pragma once


#include <stdlib.h>
#include "ShadingStrategy.hh"

using namespace std;


class ColorShadow : public ShadingStrategy
{
public:
    ColorShadow(){};
    vec3 shading(shared_ptr<Scene> scene, HitInfo& info, vector<shared_ptr<Light>> lights, vec3 lookFrom, vec3 globalLight) override;
    //float computeShadow(shared_ptr<Scene> scene, shared_ptr<Light> light, vec3 point); // override the computeShadow method
    ~ColorShadow() {};
};

