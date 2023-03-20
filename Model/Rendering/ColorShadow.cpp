#include "ColorShadow.hh"

vec3 ColorShadow::shading(shared_ptr<Scene> scene, HitInfo& info, vector<shared_ptr<Light>> lights, vec3 lookFrom, vec3 globalLight) {
    vec3 lightDiffuse = vec3(0.0);
    for (const auto& light : lights) {
        // Calculate the diffuse component
        vec3 L = light->vectorL(info.p); //normalized
        vec3 N = info.normal;
        float dotLN = dot(L, N);

        // Check if the point is in shadow
        float shadowFactor = computeShadow(scene, light, info.p);
        lightDiffuse += (info.mat_ptr->Kd * light->getId() * std::max(dotLN, 0.0f) * shadowFactor);

    }
    vec3 color = lightDiffuse;
    return color;

}
