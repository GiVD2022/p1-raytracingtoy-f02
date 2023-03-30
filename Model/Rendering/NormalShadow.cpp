#include "NormalShadow.hh"

vec3 NormalShadow::shading(shared_ptr<Scene> scene, HitInfo& info, vector<shared_ptr<Light>> lights, vec3 lookFrom, vec3 globalLight) {
    vec3 N = normalize(info.normal);
    vec3 color = 0.5f *vec3(N.x+ 1.0f, N.y+ 1.0f, N.z+ 1.0f);
    for (const auto& light : lights) {
        float shadowFactor = computeShadow(scene, light, info.p);
        color*=shadowFactor;

    }
    return color;
}
