#pragma once
#include "Texture.hh"
#include "ToonMaterial.hh"

class MaterialTextura: public ToonMaterial
{
public:
    MaterialTextura() {};
    MaterialTextura(const vec3& color);
    MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k);
    MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k, const float o);
    virtual ~MaterialTextura();

    vec3 getDiffuse(vec2 point) const;
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const;
    void read(const QJsonObject &json);

private:
    shared_ptr<Texture> textura;
};

