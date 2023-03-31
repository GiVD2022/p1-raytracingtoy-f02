#pragma once

#include "Plane.hh"

class FittedPlane : public Plane {
public:
    FittedPlane() {};
    FittedPlane(vec3 normal, vec3 point, vec2 pmin, vec2 pmax, float v);

    virtual bool hit(Ray &r, float tmin, float tmax, HitInfo &info) const override;

    virtual void read(const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    vec3 getPMin();
    vec3 getPMax();

    vec2 pmin;
    vec2 pmax;
private:

};
