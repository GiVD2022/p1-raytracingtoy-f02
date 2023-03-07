#include "Cylinder.hh"
#include "Plane.hh"
#include <math.h>
#include <iostream>


Cylinder::Cylinder()
{
    center = vec3(0.0,-0.5,0.0); //base del cilindre
    radious = 1;
    height = 1;
}

Cylinder::Cylinder(vec3 c, float h, float r,float data) :Object(data) {
    center = c;
    radious = r;
    height = h;
}

Cylinder::Cylinder(float data): Object(data){
    center = vec3(0.0,-0.5,0.0);
    radious = 1;
    height = 1;
}

// https://inmensia.com/articulos/raytracing/cilindroycono.html
bool Cylinder::hit(Ray &raig, float tmin, float tmax, HitInfo& info) const {
    float tnear = -tmax;
    float tfar = tmax;
    vec3 direction = normalize(raig.getDirection());
    //QTextStream(stdout) << "Cridant al hit \nOrigen: " << raig.getOrigin().x << " " << raig.getOrigin().y << " " << raig.getOrigin().z << " Direccio: " << direction.x << " " << direction.y << " " << direction.z << "\n";


    float k = (raig.getOrigin().x - center.x) * direction.x + (raig.getOrigin().z - center.z) * direction.z;

    float a = pow(direction.x, 2) +pow(direction.z, 2);
    float b = 2 * k;
    float c = pow((raig.getOrigin().x - center.x), 2) + pow((raig.getOrigin().z - center.z), 2) - pow(radious, 2);

    float discriminant= b*b-4*a*c;

    if( (a < DBL_EPSILON) || discriminant < 0) {// si a zero o discriminant negatiu no podem calcular arrel i no hi ha solució
        return false;
    }


    float t0 = (- b + sqrt(discriminant)) / (2*a);
    float t1 = (- b - sqrt(discriminant)) / (2*a);

    float intersect_t = qMin(t0, t1);

    vec3 intersect_p = raig.pointAtParameter(intersect_t);

    if( ( intersect_p.y < (center.y + height) ) && (intersect_p.y  > center.y) ) { //xoc dins el cilindre
        info.t = intersect_t;
        info.p = intersect_p;

        info.mat_ptr = material.get();
        info.normal = vec3(intersect_p.x, 0.f, intersect_p.z);
        return true;

    } else if ( intersect_p.y > (center.y + height) ) { // possible xoc amb la tapa superior
        HitInfo temp_info;
        vec3  normal = vec3(0,1,0);
        vec3 point = center + vec3(0,height, 0);
        Plane p = Plane(normal, point, 1);

        if (p.hit(raig, tmin, tmax, temp_info)) { //xoc amb el pla
              if( pow( (temp_info.p.x - center.x), 2) + pow(temp_info.p.z - center.z, 2) < radious){ // dins el cilindre
                  info = temp_info;
                  info.mat_ptr = material.get();
                  return true;
              }

         }
        return false;
    } else if ( intersect_p.y < (center.y)) { // possible xoc amb la tapa inferior
        HitInfo temp_info;
        vec3  normal = vec3(0,-1,0);
        Plane p = Plane(normal, center, 1);

        if (p.hit(raig, tmin, tmax, temp_info)) { //xoc amb el pla
              if( pow( (temp_info.p.x - center.x), 2) + pow(temp_info.p.z - center.z, 2) < radious){ // dins el cilindre
                  info = temp_info;
                  info.mat_ptr = material.get();
                  return true;
              }

         }
        return false;
    }
    return false;

}

void Cylinder::aplicaTG(shared_ptr<TG> t) {

}


void Cylinder::read (const QJsonObject &json)
{   /*
    Object::read(json);
    if(json.contains("punt_min") && json["punt_min"].isArray()){
        QJsonArray auxVec = json["punt_min"].toArray();
        pmin[0] = auxVec[0].toDouble();
        pmin[1] = auxVec[1].toDouble();
        pmin[2] = auxVec[2].toDouble();
    }
    if(json.contains("punt_max") && json["punt_max"].isArray()){
        QJsonArray auxVec = json["punt_max"].toArray();
        pmax[0] = auxVec[0].toDouble();
        pmax[1] = auxVec[1].toDouble();
        pmax[2] = auxVec[2].toDouble();
    }*/

}


//! [1]
void Cylinder::write(QJsonObject &json) const
{
    /*
    Object::write(json);
    QJsonArray pminArray;
    pminArray.append(pmin[0]);
    pminArray.append(pmin[1]);
    pminArray.append(pmin[2]);
    json["punt_min"] = pminArray;


    QJsonArray pmaxArray;
    pmaxArray.append(pmax[0]);
    pmaxArray.append(pmax[1]);
    pmaxArray.append(pmax[2]);
    json["punt_max"] = pmaxArray;
    */

}
//! [1]

void Cylinder::print(int indentation) const
{
    /*
    Object::print(indentation);
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "pmin:\t" << pmin[0] << ", "<< pmin[1] << ", "<< pmin[2] << "\n";
    QTextStream(stdout) << indent << "pmax:\t" << pmax[0] << ", "<< pmax[1] << ", "<< pmax[2] << "\n";
    */
}
