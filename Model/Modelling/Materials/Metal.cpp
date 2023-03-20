#include "Metal.h"

Metal::Metal(const vec3& color): ToonMaterial()
{
    Kd = color;
}

Metal::Metal(const vec3& a, const vec3& d, const vec3& s, const float k):
    ToonMaterial(a, d, s, k) {
}

Metal::Metal(const vec3& a, const vec3& d, const vec3& s, const float k, const float o):
    ToonMaterial(a, d, s, k, o) {
}
Metal::~Metal()
{
}

bool Metal::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const  {
    vec3 vec_out = glm::reflect(r_in.getDirection(), rec.normal);
    r_out = Ray(rec.p, vec_out);
    color = Ks;
    return true;
}
