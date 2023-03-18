#include "CelShadow.h"

vec3 CelShadow::shading(shared_ptr<Scene> scene, HitInfo& info, vector<shared_ptr<Light>> lights, vec3 lookFrom, vec3 globalLight){
    const float epsilon = 10e-5;
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
    vec3 returnColor = vec3(0.0);
    int n, j;

    // Vector normal de la superfície en aquell punt
    for (const auto& light : lights) {
        // Vector de llum direccional
        vec3 direction = light->vectorL(info.p);

        float alpha = std::max(glm::dot(info.normal, direction), 0.0f);

        ToonMaterial* toonMat = dynamic_cast<ToonMaterial*>(info.mat_ptr);

        if ( toonMat ){ // If successful cast
            // Find interval
            n = toonMat->getGradient().size();
            j = std::min( static_cast<int>(floor(n * alpha)), n-1 );//incloem 1 a l'últim interval

            float shadowFactor = computeShadow(scene, light, info.p);
            returnColor += toonMat->getGradient()[j] * shadowFactor;

        }

    }

    return returnColor;
}
