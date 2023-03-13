#pragma once

#include "Model/Modelling/Scene.hh"
#include "Model/Modelling/Lights/LightFactory.hh"

#define EPSILON 0.01f

class ShadingStrategy {
 public:
    // TODO: Fase 2: Canviar el mètode per passar les llums per calcular el shading
    virtual vec3 shading(shared_ptr<Scene> scene,  HitInfo& info, vector<shared_ptr<Light>> lights, vec3 lookFrom, vec3 globalLight) {
        return vec3(0.0, 0.0, 0.0);
    };


    // FASE 2: Calcula si el punt "point" és a l'ombra segons si el flag està activat o no
    float computeShadow(shared_ptr<Scene> scene, shared_ptr<Light> light, vec3 point){
        vec3 L = light->vectorL(point);
        Ray shadowRay(point, L);
        HitInfo shadowInfo;
        float maxDist = length(L);
        if (scene->hit(shadowRay, EPSILON, maxDist, shadowInfo)) {
            // Point is in shadow
            return 0.0f;
        } else {
            // Point is not in shadow
            computeAttenuation(light, point);
        }
    }

    virtual ~ShadingStrategy() {};

private:

    float computeAttenuation(shared_ptr<Light> light, vec3 point){
        float attenuation = 1.0f / light->attenuation(point);
        return attenuation;
    }
};
