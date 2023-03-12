#pragma once

#include <vector>
#include <string>
#include <limits>

#include <QString>
#include <QFile>
#include <QRegularExpression>


#include <iostream>
#include <stdlib.h>
#include <cstring>

#include "Object.hh"
#include "Face.hh"
#include "Triangle.hh"
#include "Sphere.hh"
#include "Box.hh"

#include <iostream>

using namespace std;

class Mesh : public Object
{
public:
    Mesh() {std::cout << "fa el constructor sense param" << std::endl;};
    Mesh(const QString &fileName);
    Mesh(const QString &fileName, float data);
    virtual bool hit( Ray& r, float tmin, float tmax, HitInfo& info) const override;


    virtual void aplicaTG(shared_ptr<TG> tg) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    virtual ~Mesh();
private:


    QString nom;
    vector<Face> cares; // faces o cares de l'objecte
    vector<vec4> vertexs; // vertexs de l'objecte sense repetits
    vec3 centre; //centre
    vector<Triangle> triangles;
    //shared_ptr<Sphere> esferaContenidora;
    shared_ptr<Box> capsaContenidora;

    bool hitPlane(Ray &raig, float tmin, float tmax, HitInfo& info, vec3 normal, vec3 point) const;
    bool interior(Ray &raig, float tmin, float tmax, HitInfo& info, vec3 n, vec3 a, vec3 b, vec3 c) const;
    void load(QString filename);
    void makeTriangles();
    //void makeSphere();
    void makeBox();

};

