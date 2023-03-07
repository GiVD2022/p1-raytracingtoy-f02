#pragma once

#include "Object.hh"
#include "Model/Modelling/Animation.hh"
#include "Model/Modelling/TG/TranslateTG.hh"
#include "Model/Modelling/TG/ScaleTG.hh"

class Cylinder: public Object
{
public:
    Cylinder();
    Cylinder(float data);
    Cylinder(vec3 c, float h, float r,float data);

    virtual bool hit(Ray& r, float tmin, float tmax, HitInfo& info) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;
    virtual ~Cylinder() {}

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    vec3 getCenter() {return center;};
    float getHeight() {return height;};
    float getRadious() {return radious;};

private:
    vec3 center;
    float height;
    float radious;
};
