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

using namespace std;

class Mesh : public Object
{
public:
    Mesh() {};
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
    vector<Face> cares; // facees o cares de l'objecte
    vector<vec4> vertexs; // vertexs de l'objecte sense repetits

    void load(QString filename);
    void makeTriangles();
};

