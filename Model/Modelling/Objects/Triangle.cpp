#include "Triangle.hh"
#include <iostream>

Triangle::Triangle()
{
    vertexs[0] = vec3(0.0, 0.0, 0.0);
    vertexs[1] = vec3(1.0, 0.0, 0.0);
    vertexs[2] = vec3(0.0, 1.0, 0.0);
    normal = glm::cross(vertexs[1]-vertexs[0], vertexs[2]-vertexs[0]);
    plane = Plane(normal, vertexs[0], -1.0);
}

Triangle::Triangle(vec3 v1, vec3 v2, vec3 v3, float data):Object(data) {
    vertexs[0] = v1;
    vertexs[1] = v2;
    vertexs[2] = v3;
    normal = glm::cross(vertexs[1]-vertexs[0], vertexs[2]-vertexs[0]);
    //normal = vec3(0.0, 0.0, 1.0);
    plane = Plane(normal, vertexs[0], data);
}

bool Triangle::hit(Ray &raig, float tmin, float tmax, HitInfo& info) const {
    // Intersecció amb el pla
    if (plane.hit(raig, tmin, tmax, info))
    {
        // Comprovació si el punt és interior al triangle
        vec3 p = info.p;
        vec3 a = vertexs[0];
        vec3 b = vertexs[1];
        vec3 c = vertexs[2];
        vec3 n = normal;

        vec3 u = b - a;
        vec3 v = p - a;

        vec3 uv = glm::cross(u, v);

        if(glm::dot(uv, n) <= 0){
            return false;
        }

        u = c - b;
        v = p - b;

        uv = glm::cross(u, v);

        if(glm::dot(uv, n) <= 0){
            return false;
        }

        u = a - c;
        v = p - c;

        uv = glm::cross(u, v);

        if(glm::dot(uv, n) <= 0){
            return false;
        }

        // La t de info la canvia el plane hit
        info.p = raig.pointAtParameter(info.t);
        info.mat_ptr = material.get();
        info.normal = normal;
        return true;
    }
    else
    {
        return false;
    }
}


void Triangle::aplicaTG(shared_ptr<TG> t) {
    if (dynamic_pointer_cast<TranslateTG>(t)) {
        // Per ara només es fan les translacions

    }
    //TODO: Cal ampliar-lo per a acceptar Escalats

}

void Triangle::read (const QJsonObject &json)
{
    Object::read(json);

    if (json.contains("v1") && json["v1"].isArray()) {
        QJsonArray auxVec = json["v1"].toArray();
        vertexs[0][0] = auxVec[0].toDouble();
        vertexs[0][1] = auxVec[1].toDouble();
        vertexs[0][2] = auxVec[2].toDouble();
    }

    if (json.contains("v2") && json["v2"].isArray()) {
        QJsonArray auxVec = json["v2"].toArray();
        vertexs[1][0] = auxVec[0].toDouble();
        vertexs[1][1] = auxVec[1].toDouble();
        vertexs[1][2] = auxVec[2].toDouble();
    }

    if (json.contains("v3") && json["v3"].isArray()) {
        QJsonArray auxVec = json["v3"].toArray();
        vertexs[2][0] = auxVec[0].toDouble();
        vertexs[2][1] = auxVec[1].toDouble();
        vertexs[2][2] = auxVec[2].toDouble();
    }
}


//! [1]
void Triangle::write(QJsonObject &json) const
{

    Object::write(json);

    QJsonArray auxArray;
    auxArray.append(vertexs[0][0]);auxArray.append(vertexs[0][1]);auxArray.append(vertexs[0][2]);
    json["v1"] = auxArray;

    auxArray.append(vertexs[1][0]);auxArray.append(vertexs[1][1]);auxArray.append(vertexs[1][2]);
    json["v2"] = auxArray;

    auxArray.append(vertexs[2][0]);auxArray.append(vertexs[2][1]);auxArray.append(vertexs[2][2]);
    json["v3"] = auxArray;


}
//! [1]

void Triangle::print(int indentation) const
{
    Object::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "v1:\t" << vertexs[0][0] << ", "<< vertexs[0][0] << ", "<< vertexs[0][0] << "\n";
    QTextStream(stdout) << indent << "v2:\t" << vertexs[1][0] << ", "<< vertexs[1][0] << ", "<< vertexs[1][0] << "\n";
    QTextStream(stdout) << indent << "v3:\t" << vertexs[2][0] << ", "<< vertexs[2][0] << ", "<< vertexs[2][0] << "\n";
    QTextStream(stdout) << indent << "Normal:\t" << normal[0] << ", "<< normal[0] << ", "<< normal[0] << "\n";

}
