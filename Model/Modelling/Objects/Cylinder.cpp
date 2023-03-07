#include "Cylinder.hh"
#include "Plane.hh"
#include <math.h>
#include <iostream>


Cylinder::Cylinder()
{
    center = vec3(0.0,-0.5,0.0); //base del cilindre
    radius = 1;
    height = 1;
    axis = vec3(0.0,1.0,0.0);
}

Cylinder::Cylinder(vec3 c, vec3 a, float h, float r,float data) :Object(data) {
    center = c;
    radius = r;
    height = h;
    axis = a;
}

Cylinder::Cylinder(float data): Object(data){
    center = vec3(0.0,-0.5,0.0);
    radius = 1;
    height = 1;
    axis = vec3(0.0,1.0,0.0);
}

// https://inmensia.com/articulos/raytracing/cilindroycono.html
bool Cylinder::hit(Ray &raig, float tmin, float tmax, HitInfo& info) const {

    //ASSUMIM QUE AXIS = [0,1,0] SEMPRE

    vec3 direction = normalize(raig.getDirection());
    //QTextStream(stdout) << "Cridant al hit \nOrigen: " << raig.getOrigin().x << " " << raig.getOrigin().y << " " << raig.getOrigin().z << " Direccio: " << direction.x << " " << direction.y << " " << direction.z << "\n";


    float k = (raig.getOrigin().x - center.x) * direction.x + (raig.getOrigin().z - center.z) * direction.z;

    float a = pow(direction.x, 2) +pow(direction.z, 2);
    float b = 2 * k;
    float c = pow((raig.getOrigin().x - center.x), 2) + pow((raig.getOrigin().z - center.z), 2) - pow(radius, 2);

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
              if( pow( (temp_info.p.x - center.x), 2) + pow(temp_info.p.z - center.z, 2) < radius){ // dins el cilindre
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
              if( pow( (temp_info.p.x - center.x), 2) + pow(temp_info.p.z - center.z, 2) < radius){ // dins el cilindre
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
    if (auto translateTG = dynamic_pointer_cast<TranslateTG>(t)) {
        QTextStream(stdout)<<"Translating cylinder \n";
        vec4 c(center, 1.0);
        c = translateTG->getTG() * c;
        center.x = c.x; center.y = c.y; center.z = c.z;
    } else if (auto scaleTG = dynamic_pointer_cast<ScaleTG>(t)) {
        QTextStream(stdout)<<"Scaling cylinder \n";
        glm::vec3 scale = scaleTG->scale;
        radius *= std::sqrt(scale.x * scale.y * scale.z); // Apply scaling to radius
        height *= scale.y;
    } else {
        QTextStream(stdout) << "This print should never be displayed; Sphere::aplicaTG \n";
    }
}


void Cylinder::read (const QJsonObject &json)
{
    Object::read(json);
    if(json.contains("radious") && json["punt_min"].isDouble()){
        radius = json["radious"].toDouble();
    }
    if(json.contains("h") && json["h"].isDouble()){
        height = json["h"].toDouble();
    }
    if (json.contains("center") && json["center"].isArray()) {
        QJsonArray auxVec = json["center"].toArray();
        center[0] = auxVec[0].toDouble();
        center[1] = auxVec[1].toDouble();
        center[2] = auxVec[2].toDouble();
    }
    if (json.contains("axis") && json["axis"].isArray()) {
        QJsonArray auxVec = json["axis"].toArray();
        axis[0] = auxVec[0].toDouble();
        axis[1] = auxVec[1].toDouble();
        axis[2] = auxVec[2].toDouble();
    }
}


//! [1]
void Cylinder::write(QJsonObject &json) const
{

    Object::write(json);

    QJsonArray centerArray;
    centerArray.append(center[0]);centerArray.append(center[1]);centerArray.append(center[2]);
    json["center"] = centerArray;

    QJsonArray axisArray;
    axisArray.append(axis[0]);axisArray.append(axis[1]);axisArray.append(axis[2]);
    json["axis"] = axisArray;

    json["radious"] = radius;

    json["h"] = height;

}
//! [1]

void Cylinder::print(int indentation) const
{

    Object::print(indentation);
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "center:\t" << center[0] << ", "<< center[1] << ", "<< center[2] << "\n";
    QTextStream(stdout) << indent << "axis:\t" << axis[0] << ", "<< axis[1] << ", "<< axis[2] << "\n";
    QTextStream(stdout) << indent << "radius:\t" << radius<< "\n";
     QTextStream(stdout) << indent << "height:\t" << height<< "\n";

}
