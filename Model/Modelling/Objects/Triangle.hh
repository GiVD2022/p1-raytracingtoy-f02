#pragma once

#include "Object.hh"
#include "Model/Modelling/Animation.hh"
#include "Model/Modelling/TG/TranslateTG.hh"
#include "Model/Modelling/TG/ScaleTG.hh"
#include "Model/Modelling/TG/RotateTG.hh"
#include "Plane.hh"

class Triangle: public Object
{
public:
    Triangle();

    Triangle(vec3 v1, vec3 v2, vec3 v3, float data);

    virtual ~Triangle() {}
    virtual bool hit(Ray& r, float tmin, float tmax, HitInfo& info) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;


    vec3* getVertexs(){return vertexs;}

private:
    // Vertexs del triangle
    vec3 vertexs[3];
    // Pla contenedor dels punts
    Plane plane;
    // Normal
    vec3 normal;
};
