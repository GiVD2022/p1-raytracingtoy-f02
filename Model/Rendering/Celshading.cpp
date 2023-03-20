#include "Celshading.hh"
#include "Model/Modelling/Materials/ToonMaterial.hh"
#include <iostream>

vec3 CelShading::shading(shared_ptr<Scene> scene, HitInfo& info, vector<shared_ptr<Light>> lights, vec3 lookFrom, vec3 globalLight){
    /*
     * Producte escalar del vector llum direccional amb la normal al punt
    */
    /*
     * Depenent del gradient de cada material, tindrem n intervals, on n el nombre de tonalitats
     * [v0, v1), [v1, v2), ..., [v(n-1), vn)
     * Donat alpha \in [0, 1], per saber en quin interval es troba fem:
     * j = floor(n * alpha), llavors alpha \in I_j ( si els intervals són I_0, ... I_{n-1} )
     * Per tant el color corresponent en aquell punt és colorGradient[j]
    */
    vec3 lightAmbient = vec3(0.0);
    vec3 returnColor = globalLight * info.mat_ptr->Ka;
    vec3 lightSpecular = vec3(0.0);
    vec3 rimComponent = vec3(0.0);
    int n, j;
    float rimDot;

    // Vector normal de la superfície en aquell punt
    for (const auto& light : lights) {
        // Calculate the ambient component
        lightAmbient += light->getIa() * info.mat_ptr->Ka;

        // Vector de llum
        vec3 direction = light->vectorL(info.p); //normalized

        float alpha = std::max(glm::dot(info.normal, direction), 0.0f);

        ToonMaterial* toonMat = dynamic_cast<ToonMaterial*>(info.mat_ptr);

        if ( toonMat ){ // If successful cast
            // Find interval
            n = toonMat->getGradient().size();
            j = std::min( static_cast<int>(floor(n * alpha)), n-1 );//incloem 1 a l'últim interval
            returnColor += toonMat->getGradient()[j];

            // Calculate the specular component
            vec3 L = light->vectorL(info.p); //normalized
            vec3 N = info.normal;
            vec3 V = normalize(lookFrom - info.p);
            vec3 H = normalize(L + V);
            vec3 kd0 = toonMat->getGradient()[n-1];
            float dotNH = dot(N, H);
            lightSpecular += (kd0 * light->getIs() * pow(std::max(dotNH, 0.0f), info.mat_ptr->beta));

            //Siluetes
            rimDot = (1-dot(V, N)) > 0.75 ? 1.0 : 0.0;
            rimComponent += kd0 * toonMat->Ks * rimDot;

        }



    }

    return returnColor + lightAmbient + rimComponent;
}
