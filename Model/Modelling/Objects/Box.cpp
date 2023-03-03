#include "Box.hh"
#include "Plane.hh"
#include <math.h>
#include <iostream>


Box::Box()
{
    pmax = vec3(1,1,1);
    pmin = vec3(0,0,0);
}

Box::Box(vec3 p1, vec3 p2,float data) :Object(data) {
    std::cout << "CREO BOX" << std::endl;
    pmax = p1;
    pmin = p2;
}

Box::Box(vec3 p1, vec3 p2) {
    std::cout << "CREO BOX 1" << std::endl;
    pmax = p1;
    pmin = p2;
}


bool Box::hit(Ray &raig, float tmin, float tmax, HitInfo& info) const {
    float tnear = -tmax;
    float tfar = tmax;
    float t1;
    float t2;
    vec3 normal = vec3(0,0,0);

    for (int i=0;i<3;i++){
        if(raig.getDirection()[i] == 0){
            if(raig.getOrigin()[i] < pmin[i] || raig.getOrigin()[i] < pmax[i] ){
                return false;
            }
        }
        else{
            t1 = (pmin[i] - raig.getOrigin()[i])/raig.getDirection()[i];
            t2 = (pmax[i] - raig.getOrigin()[i])/raig.getDirection()[i];

            if(t1 > t2){
                float aux = t2;
                t2 = t1;
                t1 = aux;
            }

            if(t1 > tnear){
                tnear = t1;
                normal = vec3(0,0,0);
                normal[i] = 1;
            }
            if(t2 < tfar){
                tfar = t2;
            }
        }
        if(tnear > tfar){
            return false;
        }
        if(tfar < 0){
            return false;
        }

    }
    info.t = tnear;
    info.p = raig.pointAtParameter(info.t);
    info.mat_ptr = material.get();
    info.normal = normal;
    return true;

}

void Box::aplicaTG(shared_ptr<TG> t) {

    //TODO: Cal ampliar-lo per a acceptar Escalats

}

void Box::read (const QJsonObject &json)
{
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
        pmax[0] = auxVec[0].toDouble();
    }

}


//! [1]
void Box::write(QJsonObject &json) const
{

}
//! [1]

void Box::print(int indentation) const
{

}
