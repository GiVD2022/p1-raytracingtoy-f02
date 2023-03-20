#include "ColorShading.hh"
#include <iostream>


vec3 ColorShading::shading(shared_ptr<Scene> scene, HitInfo& info, vector<shared_ptr<Light>> lights, vec3 lookFrom, vec3 globalLight) {
    return info.mat_ptr->Kd;
}
