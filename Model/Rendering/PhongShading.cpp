#include "PhongShading.hh"

vec3 PhongShading::shading(shared_ptr<Scene> scene, HitInfo& info, vector<shared_ptr<Light>> lights, vec3 lookFrom, vec3 globalLight){
    vec3 lightAmbient = vec3(0.0);
    vec3 lightDiffuse = vec3(0.0);
    vec3 lightSpecular = vec3(0.0);
    for (const auto& light : lights) {

        // Calculate depth atenuation
        float depthAttenuation = light->attenuation(info.p);

        // Calculate the ambient component
        lightAmbient += light->getIa() * info.mat_ptr->Ka;

        // Calculate the diffuse component
        vec3 L = normalize(light->vectorL(info.p)); //normalized
        vec3 N = normalize(info.normal);
        lightDiffuse += (info.mat_ptr->Kd * light->getId() * std::max(dot(L, N), 0.0f))* depthAttenuation;


        // Calculate the specular component
        vec3 R = normalize( 2.f * (dot(N, L) * N) - L);
        vec3 V = normalize(lookFrom - info.p);
        lightSpecular += (info.mat_ptr->Ks * light->getIs() * pow(std::max(dot(R,V), 0.0f), info.mat_ptr->shininess)) * depthAttenuation;

    }
    vec3 color = lightAmbient + lightDiffuse + lightSpecular;
    return color;
}
