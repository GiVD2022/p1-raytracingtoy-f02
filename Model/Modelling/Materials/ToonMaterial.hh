#pragma once

#include <vector>
#include "Material.hh"

class ToonMaterial : public Material
{

public:
    ToonMaterial();
    ToonMaterial(vec3 d);
    ToonMaterial(vec3 a, vec3 d, vec3 s, float shininess);
    ToonMaterial(vec3 a, vec3 d, vec3 s, float shininess, float opacity);
    virtual ~ToonMaterial();

    virtual void read (const QJsonObject &json);
    virtual void write(QJsonObject &json) const;
    virtual void print(int indentation) const;
    std::vector<vec3> getGradient(){return colorGradient;}

private:
    std::vector<vec3> colorGradient;

};
