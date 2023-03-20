#include "Transparent.hh"

Transparent::Transparent(const vec3& color): ToonMaterial()
{
    Kd = color;
}

Transparent::Transparent(const vec3& a, const vec3& d, const vec3& s, const float k):
    ToonMaterial(a, d, s, k) {
}

Transparent::Transparent(const vec3& a, const vec3& d, const vec3& s, const float k, const float o):
    ToonMaterial(a, d, s, k, o) {
}

Transparent::Transparent(const vec3& a, const vec3& d, const vec3& s, const vec3& t,const float k, const float o, const float mu):
    ToonMaterial(a, d, s, t, k, o, mu) {
}
Transparent::~Transparent()
{
}

bool Transparent::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const  {
    float mu_i = 1.0f; //Assumim que el medi es el buit
    float mu_it = mu_i / mu_t;

    vec3 incident = normalize(r_in.getDirection());
    vec3 normal = normalize(rec.normal);

    // Si va de dins a fora, canviem la normal i el quocient
    if(glm::dot(r_in.getDirection(), normal) > 0){
        normal = -normal;
        mu_it = 1.f/mu_it;
    }

    // Si reflexio interna: ks; si no, k
    // Calcular un unic raig transmes
    vec3 t = glm::refract(incident, normal, mu_it);

    // Reflexio interna
    if ( glm::length(t) < FLT_EPSILON) {
        // Calcular un unic raig transmes
        vec3 vec_out = glm::reflect(r_in.getDirection(), rec.normal);
        r_out = Ray(rec.p, vec_out);
        color = Ks;
    // Reflexio no interna
    } else {
        r_out = Ray(rec.p, t);
        color = kt;
    }
    return true;
}
