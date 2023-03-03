#pragma once

#include "Object.hh"
#include "Plane.hh"
#include "Model/Modelling/Animation.hh"
#include "Model/Modelling/TG/TranslateTG.hh"

class Box: public Object
{
public:
    Box();
    Box(vec3 p1, vec3 p2);
    Box(vec3 p1, vec3 p2,float data);

    virtual bool hit(Ray& r, float tmin, float tmax, HitInfo& info) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;
    virtual ~Box() {}

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    vec3 getPMax() {return pmax;};
    vec3 getPMin() {return pmin;};

private:
    vec3 pmin;
    vec3 pmax;
};

