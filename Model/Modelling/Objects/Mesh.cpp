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
    for (const auto& f : cares) {
        triangles.push_back(Triangle(vec3(vertexs[f.idxVertices[0]]), vec3(vertexs[f.idxVertices[1]]), vec3(vertexs[f.idxVertices[2]]), -1.0));
    }
}
/*
void Mesh::makeSphere() {
    float maxDist = 0.0;
    vec3 extrem1;
    vec3 extrem2;
    float auxDist;
    for (const auto& v1 : vertexs){
        for (const auto& v2 : vertexs){
            auxDist = glm::distance(v1, v2);
            if (auxDist > maxDist){
                maxDist = auxDist;
                extrem1 = vec3(v1);
                extrem2 = vec3(v2);
            }
        }
    }

    // Construim l'esfera centrada al punt mig del segment i de radi maxDist / 2
    vec3 centre = extrem1 + 0.5f * (extrem2 - extrem1);
    std::cout << centre.x << " " << centre.y << " " << centre.z << std::endl;
    std::cout << maxDist << std::endl;
    esferaContenidora = make_shared<Sphere>(centre, maxDist / 2.0f, -1.0);
}
*/

void Mesh::makeBox(){
    // aprofitem el loop per calcular el centre
    centre = vec3(0.f);
    vec3 minim = vec3(FLT_MAX,FLT_MAX,FLT_MAX);
    vec3 maxim = vec3(-FLT_MAX,-FLT_MAX,-FLT_MAX);

    for (const auto& v1 : vertexs){
        centre += vec3(v1);
        if(v1[0] < minim[0]){
            minim[0] = v1[0];
        }
        if(v1[1] < minim[1]){
            minim[1] = v1[1];
        }
        if(v1[2] < minim[2]){
            minim[2] = v1[2];
        }
        if(v1[0] > maxim[0]){
            maxim[0] = v1[0];
        }
        if(v1[1] > maxim[1]){
            maxim[1] = v1[1];
        }
        if(v1[2] > maxim[2]){
            maxim[2] = v1[2];
        }

    }
    centre = centre / (float) vertexs.size();
    std::cout << minim.x << " " << minim.y << " " << minim.z << std::endl;
    std::cout << maxim.x << " " << maxim.y << " " << maxim.z << std::endl;
    capsaContenidora = make_shared<Box>(minim,maxim,-1.0);

}

bool Mesh::hit(Ray &raig, float tmin, float tmax, HitInfo& info) const {
    bool hit_anything = false;
    float closest_t = tmax;

    if ( capsaContenidora->hit(raig, tmin, tmax, info)){
        //Si toca l'esfera, mirem si realment toca l'objecte.
            // Hit per cara
            for (const auto& face : cares)
            {
                // Guardem els 3 vertexs i la normal:
                vec3 v1 = vec3(vertexs[face.idxVertices[0]]);
                vec3 v2 = vec3(vertexs[face.idxVertices[1]]);
                vec3 v3 = vec3(vertexs[face.idxVertices[2]]);
                vec3 n = glm::cross(v2-v1, v3-v1);
                HitInfo triang_hit_info;
                if (hitPlane(raig, tmin, closest_t, triang_hit_info, n, v1)){
                    if (interior(raig, tmin, closest_t, triang_hit_info, n, v1, v2, v3)){
                        hit_anything = true;
                        closest_t = triang_hit_info.t;
                        info = triang_hit_info;
                        info.mat_ptr = material.get();
                    }
                }
            }

        //std::cout << "ha acabat el for de triangles " << hit_anything << std::endl;
        return hit_anything;
    }
    // Si no ha tocat l'esfera, retorna false.
    return false;
}

bool Mesh::interior(Ray &raig, float tmin, float tmax, HitInfo& info, vec3 n, vec3 a, vec3 b, vec3 c) const{
    // Comprovació si el punt és interior al triangle
    vec3 p = info.p;

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

    return true;
}

bool Mesh::hitPlane(Ray &raig, float tmin, float tmax, HitInfo& info, vec3 normal, vec3 point) const{
    if(abs(dot(raig.getDirection(), normal))<DBL_EPSILON){
        return false;
    }

    // 1) Calculem la D = -Ax-By-Cz
    float d = -normal[0]*point[0] - normal[1]*point[1] - normal[2]*point[2];

    // 2) Imposem que la recta p+tv compleixi l'eq del pla
    vec3 rp = raig.getOrigin();
    vec3 vp = raig.getDirection();
    float temp =  -normal[0]*rp[0] - normal[1]*rp[1] - normal[2]*rp[2] - d;

    temp/= normal[0]*vp[0] + normal[1]*vp[1] + normal[2]*vp[2];

    if (temp > tmax || temp < tmin) {
            return false;
    }

    // Omplim el camp de info:
    info.t = temp;
    info.p = raig.pointAtParameter(info.t);

    // La normal a un pla es la mateixa per tots els punts
    info.normal = normal;
    return true;
}


void Mesh::aplicaTG(shared_ptr<TG> t) {
    // TO DO: Fase 1
    if (auto translateTG = dynamic_pointer_cast<TranslateTG>(t)) {
        for (int i = 0; i < vertexs.size(); i++){ //v1 es un vec3 i un 1.0f, com es veu al load
            vertexs[i] = translateTG->getTG() * vertexs[i];

        }
    } else if (auto scaleTG = dynamic_pointer_cast<ScaleTG>(t)) {
        vec3 scale = scaleTG->scale;
        for (int i = 0; i < vertexs.size(); i++){ //v1 es un vec3 i un 1.0f, com es veu al load
            vec3 v1 = centre + scale * (vec3(vertexs[i]) - centre);
            vertexs[i] = vec4(v1, 1.f);
        }
    }
}

void Mesh::load (QString fileName) {
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
            //makeTriangles();
            //makeSphere();
            makeBox();
        } else {
            qWarning("Boundary object file can not be opened.");
        }
    } else  qWarning("Boundary object file not found.");
}

void Mesh::read (const QJsonObject &json)
{
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



