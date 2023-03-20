#include "NormalShadow.hh"

vec3 NormalShadow::shading(shared_ptr<Scene> scene, HitInfo& info, vector<shared_ptr<Light>> lights, vec3 lookFrom, vec3 globalLight) {
    vec3 lightDiffuse = vec3(0.0);
    vec3 N = normalize(info.normal);
    N = 0.5f *vec3(N.x+ 1.0f, N.y+ 1.0f, N.z+ 1.0f);
    for (const auto& light : lights) {

        // Calculate the diffuse component
        vec3 L = light->vectorL(info.p); //normalized
        vec3 N = info.normal;
        float dotLN = dot(L, N);

        // Check if the point is in shadow
        float shadowFactor = computeShadow(scene, light, info.p);

        lightDiffuse += (N * light->getId() * std::max(dotLN, 0.0f) * shadowFactor);

    }
    vec3 color = lightDiffuse;
    return color;
}
