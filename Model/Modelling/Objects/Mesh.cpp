#include <QVector>
#include <QVector3D>
#include <iostream>

#include "Mesh.hh"

Mesh::Mesh(const QString &fileName): Object()
{
    nom = fileName;
    load(fileName);
}

Mesh::Mesh(const QString &fileName, float data): Object(data)
{
    nom = fileName;
    load(fileName);
}

Mesh::~Mesh() {
    if (cares.size() > 0) cares.clear();
    if (vertexs.size() > 0) vertexs.clear();

}

void Mesh::makeTriangles() {
    for (Face f : cares) {
        triangles.push_back(Triangle(vec3(vertexs[f.idxVertices[0]]), vec3(vertexs[f.idxVertices[1]]), vec3(vertexs[f.idxVertices[2]]), -1.0));
    }
    std::cout << "s'han creat " << triangles.size() << " triangles" << std::endl;
}


bool Mesh::hit(Ray &raig, float tmin, float tmax, HitInfo& info) const {
    bool hit_anything = false;
    float closest_t = tmax;

    for (const auto& triangle : triangles){
        // el warning del for no he entès què és
        HitInfo triang_hit_info;
        if (triangle.hit(raig, tmin, closest_t, triang_hit_info)) {
            hit_anything = true;
            closest_t = triang_hit_info.t;
            info = triang_hit_info;
            info.mat_ptr = material.get();
        }
    }
    //std::cout << "ha acabat el for de triangles " << hit_anything << std::endl;
    return hit_anything;

}


void Mesh::aplicaTG(shared_ptr<TG> t) {
    // TO DO: Fase 1
}

void Mesh::load (QString fileName) {
    std::cout << "fa servir el load de mesh" << std::endl;
    QFile file(fileName);
    if(file.exists()) {
        if(file.open(QFile::ReadOnly | QFile::Text)) {
            while(!file.atEnd()) {
                QString line = file.readLine().trimmed();
                QStringList lineParts = line.split(QRegularExpression("\\s+"));
                if(lineParts.count() > 0) {
                    // if it’s a comment
                    if(lineParts.at(0).compare("#", Qt::CaseInsensitive) == 0)
                    {
                        // qDebug() << line.remove(0, 1).trimmed();
                    }

                    // if it’s a vertex position (v)
                    else if(lineParts.at(0).compare("v", Qt::CaseInsensitive) == 0)
                    {
                        vertexs.push_back(vec4(lineParts.at(1).toFloat(),
                                               lineParts.at(2).toFloat(),
                                               lineParts.at(3).toFloat(), 1.0f));
                    }

                    // if it’s a normal (vn)
                    else if(lineParts.at(0).compare("vn", Qt::CaseInsensitive) == 0)
                    {

                    }
                    // if it’s a texture (vt)
                    else if(lineParts.at(0).compare("vt", Qt::CaseInsensitive) == 0)
                    {

                    }

                    // if it’s face data (f)
                    // there’s an assumption here that faces are all triangles
                    else if(lineParts.at(0).compare("f", Qt::CaseInsensitive) == 0)
                    {
                        Face *face = new Face();

                        // get points from v array
                        face->idxVertices.push_back(lineParts.at(1).split("/").at(0).toInt() - 1);
                        face->idxVertices.push_back(lineParts.at(2).split("/").at(0).toInt() - 1);
                        face->idxVertices.push_back(lineParts.at(3).split("/").at(0).toInt() - 1);

                        cares.push_back(*face);
                    }
                }
            }
            file.close();
            makeTriangles();
        } else {
            qWarning("Boundary object file can not be opened.");
        }
    } else  qWarning("Boundary object file not found.");
}

void Mesh::read (const QJsonObject &json)
{
    std::cout << "fa servir el read de mesh" << std::endl;
    Object::read(json);
    if (json.contains("objFileName") && json["objFileName"].isString()) {
        nom = json["objFileName"].toString();
        load(nom);
    }
}


//! [1]
void Mesh::write(QJsonObject &json) const
{
    Object::write(json);
    json["objFileName"] = nom;
}
//! [1]

void Mesh::print(int indentation) const
{
    Object::print(indentation);
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "objFileName:\t" << nom << "\n";
}



