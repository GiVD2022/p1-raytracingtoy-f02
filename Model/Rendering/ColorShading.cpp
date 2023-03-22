#include "ColorShading.hh"


vec3 ColorShading::shading(shared_ptr<Scene> scene, HitInfo& info, vector<shared_ptr<Light>> lights, vec3 lookFrom, vec3 globalLight) {
    //Retorna kd si no es texture
    return (info.mat_ptr->getDiffuse(info.uv));
}
