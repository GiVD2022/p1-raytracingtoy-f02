#pragma once

#include "ToonMaterial.hh"

class Transparent: public ToonMaterial
{
public:
    Transparent() {};
    Transparent(const vec3& color);
    Transparent(const vec3& a, const vec3& d, const vec3& s, const float k);
    Transparent(const vec3& a, const vec3& d, const vec3& s, const float k, const float o);
    Transparent(const vec3& a, const vec3& d, const vec3& s, const vec3& t, const float k, const float o, float mu);
    virtual ~Transparent();

    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const;
};

