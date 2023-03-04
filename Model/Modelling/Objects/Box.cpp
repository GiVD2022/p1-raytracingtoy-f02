#include "Box.hh"
#include "Plane.hh"
#include <math.h>
#include <iostream>


Box::Box()
{
    pmin = vec3(0,0,0);
    pmax = vec3(1,1,1);
}

Box::Box(vec3 p1, vec3 p2,float data) :Object(data) {
    pmin = p1;
    pmax = p2;
}

Box::Box(float data): Object(data){
    pmin = vec3(0,0,0);
    pmax = vec3(1,1,1);
}


bool Box::hit(Ray &raig, float tmin, float tmax, HitInfo& info) const {
    float tnear = -tmax;
    float tfar = tmax;
    float t1;
    float t2;
    vec3 normal = vec3(0,0,0);

    for (int i=0;i<3;i++){
        if(fabs(raig.getDirection()[i]) < DBL_EPSILON){
            if(raig.getOrigin()[i] < pmin[i] || raig.getOrigin()[i] > pmax[i] ){
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
        pmax[2] = auxVec[2].toDouble();
    }

}


//! [1]
void Box::write(QJsonObject &json) const
{
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

}
//! [1]

void Box::print(int indentation) const
{
    Object::print(indentation);
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "pmin:\t" << pmin[0] << ", "<< pmin[1] << ", "<< pmin[2] << "\n";
    QTextStream(stdout) << indent << "pmax:\t" << pmax[0] << ", "<< pmax[1] << ", "<< pmax[2] << "\n";
}
