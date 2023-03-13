#include "BlinnPhongShadow.hh"

vec3 BlinnPhongShadow::shading(shared_ptr<Scene> scene, HitInfo& info, vector<shared_ptr<Light>> lights, vec3 lookFrom, vec3 globalLight) {
    vec3 lightAmbient = vec3(0.0);
    vec3 lightDiffuse = vec3(0.0);
    vec3 lightSpecular = vec3(0.0);
    vec3 globalAmbient = globalLight * info.mat_ptr->Ka;

    for (const auto& light : lights) {
        // Calculate depth attenuation
        float depthAttenuation = light->attenuation(info.p);

        // Calculate the ambient component
        lightAmbient += light->getIa() * info.mat_ptr->Ka;

        // Calculate the diffuse component
        vec3 L = light->vectorL(info.p); //normalized
        vec3 N = info.normal;
        float dotLN = dot(L, N);

        // Check if the point is in shadow
        float shadowFactor = computeShadow(scene, light, info.p);

        lightDiffuse += (info.mat_ptr->Kd * light->getId() * std::max(dotLN, 0.0f) * shadowFactor) * depthAttenuation;

        // Calculate the specular component
        vec3 V = normalize(lookFrom - info.p);
        vec3 H = normalize(L + V);
        float dotNH = dot(N, H);
        lightSpecular += (info.mat_ptr->Ks * light->getIs() * pow(std::max(dotNH, 0.0f), info.mat_ptr->shininess) * shadowFactor) * depthAttenuation;
    }
    vec3 color = globalAmbient + lightAmbient + lightDiffuse + lightSpecular;
    return color;
}



float BlinnPhongShadow::computeShadow(shared_ptr<Scene> scene, shared_ptr<Light> light, vec3 point)
{
    vec3 L = light->vectorL(point);
    Ray shadowRay(point, L);
    HitInfo shadowInfo;
    float maxDist = length(L);
    if (scene->hit(shadowRay, 0.001f, maxDist, shadowInfo)) {
        // Point is in shadow
        return 0.0f;
    } else {
        // Point is not in shadow
        float attenuation = 1.0f / light->attenuation(point);
        return attenuation;
    }
}
