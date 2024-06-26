#include "Lambertian.hh"

Lambertian::Lambertian(const vec3& color): ToonMaterial()
{
    Kd = color;
}

Lambertian::Lambertian(const vec3& a, const vec3& d, const vec3& s, const float k):
    ToonMaterial(a, d, s, k) {
}

Lambertian::Lambertian(const vec3& a, const vec3& d, const vec3& s, const float k, const float o):
    ToonMaterial(a, d, s, k, o) {
}
Lambertian::~Lambertian()
{
}

bool Lambertian::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const  {
    vec3 target = rec.p + rec.normal + Hitable::RandomInSphere();
    r_out =  Ray(rec.p, target-rec.p);
    color = Kd;
    return true;
}

vec3 Lambertian::getDiffuse(vec2 uv) const {
    return Kd;

}
