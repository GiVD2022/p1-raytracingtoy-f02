#pragma once

#include "Object.hh"
#include "Model/Modelling/Animation.hh"
#include "Model/Modelling/TG/TranslateTG.hh"
#include "Model/Modelling/TG/ScaleTG.hh"
#include "Model/Modelling/TG/RotateTG.hh"

class Cylinder: public Object
{
public:
    Cylinder();
    Cylinder(float data);
    Cylinder(vec3 c, vec3 a, float h, float r,float data);
    virtual ~Cylinder() {}

    virtual bool hit(Ray& r, float tmin, float tmax, HitInfo& info) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    vec3 getCenter() {return center;};
    vec3 getAxis() {return axis;};
    float getHeight() {return height;};
    float getRadius() {return radius;};

private:
    vec3 center;
    vec3 axis;
    float height;
    float radius;
};
