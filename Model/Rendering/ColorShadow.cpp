#include "ColorShadow.hh"

vec3 ColorShadow::shading(shared_ptr<Scene> scene, HitInfo& info, vector<shared_ptr<Light>> lights, vec3 lookFrom, vec3 globalLight) {
    // TODO: Fase 2: Canviar per a considerar les ombres en aquest shading
    // (info.mat_ptr->getDiffuse(info.uv)) retorna kd si no es texture
    return vec3(1.0)-(info.mat_ptr->getDiffuse(info.uv));
}
