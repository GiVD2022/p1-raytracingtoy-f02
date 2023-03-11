#include "Celshading.hh"

vec3 CelShading::shading(shared_ptr<Scene> scene, HitInfo& info, vector<shared_ptr<Light>> lights, vec3 lookFrom, vec3 globalLight){
    const float epsilon = 10e-5;
    /*
     * Producte escalar del vector llum direccional amb la normal al punt
    */
    /*
     * Definim els intervals de la forma:
     * [v0, v1), [v1, v2), [v2, v3), [v3, v4)
    */
    float v[] = {0.0, 0.25, 0.5, 0.75, 1};
    vec3 color[] = {vec3(0.0), vec3(0.0), vec3(0.0), vec3(0.0)};

    // Vector normal de la superfície en aquell punt
    vec3 n = info.normal;
    // Vector de llum direccional
    DirectionalLight directionalLight = lights[0]; //no sé com trobar-la
    vec3 direction = directionalLight.getDirection();

    float alpha = glm::dot(n, direction);

    for (int i = 0; i < 5; i++){
        if ( (alpha > v[i] || (alpha - v[i]) < epsilon) && alpha < v[i+1] ){
            return color[i];
        }
    }

}

