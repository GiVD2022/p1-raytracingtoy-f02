#include "ColorShadow.hh"

vec3 ColorShadow::shading(shared_ptr<Scene> scene, HitInfo& info, vector<shared_ptr<Light>> lights, vec3 lookFrom, vec3 globalLight) {
    vec3 color = info.mat_ptr->Kd;
    for (const auto& light : lights) {
        float shadowFactor = computeShadow(scene, light, info.p);
        color *= shadowFactor;
    }
    return color;
}
