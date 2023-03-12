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

    // INTERSECCIO AMB EL CILINDRE

    bool algun_xoc = false;

    vec3 direction = normalize(raig.getDirection());


    float k = (raig.getOrigin().x - center.x) * direction.x + (raig.getOrigin().z - center.z) * direction.z;

    float a = pow(direction.x, 2) +pow(direction.z, 2);
    float b = 2 * k;
    float c = pow((raig.getOrigin().x - center.x), 2) + pow((raig.getOrigin().z - center.z), 2) - pow(radius, 2);

    float discriminant= b*b-4*a*c;

    if( (abs(a) > DBL_EPSILON) && discriminant >= DBL_EPSILON) {// si a zero o discriminant negatiu no podem calcular arrel i no hi ha solució al cilindre
        float t0 = (- b + sqrt(discriminant)) / (2*a);
        float t1 = (- b - sqrt(discriminant)) / (2*a);

        float intersect_t;
        bool intersecta_a_temps = true;
        if (t0 > tmin && t1 > tmin && t1 < tmax && t0 < tmax){
            intersect_t = qMin(t0, t1);
        } else if (t0 > tmin && t0 < tmax){
            intersect_t = t0;
        } else if (t1 > tmin && t1 < tmax){
            intersect_t = t1;
        } else {
            intersecta_a_temps = false;
        }

        if(intersecta_a_temps){

            vec3 intersect_p = raig.pointAtParameter(intersect_t);

            if( ( intersect_p.y < (center.y + height) ) && (intersect_p.y  > center.y) ) { //xoc dins el cilindre
                info.t = intersect_t;
                info.p = intersect_p;
                info.normal = normalize(vec3(intersect_p.x, 0.f, intersect_p.z));
                info.mat_ptr = material.get();
                algun_xoc = true;

            }
        }
    }

    // INTERSECCIO AMB LES TAPES

    // possible xoc amb la tapa superior

    vec3  normal = vec3(0,1,0);
    vec3 point = center + vec3(0,height, 0);

    // 1) Calculem la D = -Ax-By-Cz
    float d = -normal[0]*point[0] - normal[1]*point[1] - normal[2]*point[2];

    // 2) Imposem que la recta p+tv compleixi l'eq del pla
    // A(p1 + tv1) + ... + D = 0
    // Aillem la t
    vec3 rp = raig.getOrigin();
    vec3 vp = raig.getDirection();
    float temp =  -normal[0]*rp[0] - normal[1]*rp[1] - normal[2]*rp[2] - d;

    temp/= normal[0]*vp[0] + normal[1]*vp[1] + normal[2]*vp[2];


    if (temp < tmax && temp > tmin) { //xoc amb el pla
        vec3 punt_xoc = raig.pointAtParameter(temp);
          if ( ( pow( (punt_xoc.x - center.x), 2) + pow(punt_xoc.z - center.z, 2) < pow(radius,2)) && ( !algun_xoc || temp < info.t) ){ // dins el cilindre
              info.t = punt_xoc.t;
              info.p = punt_xoc;
              info.normal = normal;
              info.mat_ptr = material.get();
              algun_xoc = true;

          }
    }

    // possible xoc amb la tapa inferior

    normal = vec3(0,-1,0);
    point = center;

    // 1) Calculem la D = -Ax-By-Cz
    d = -normal[0]*point[0] - normal[1]*point[1] - normal[2]*point[2];

    // 2) Imposem que la recta p+tv compleixi l'eq del pla
    // A(p1 + tv1) + ... + D = 0
    // Aillem la t
    rp = raig.getOrigin();
    vp = raig.getDirection();
    temp =  -normal[0]*rp[0] - normal[1]*rp[1] - normal[2]*rp[2] - d;

    temp/= normal[0]*vp[0] + normal[1]*vp[1] + normal[2]*vp[2];


    if (temp < tmax && temp > tmin) { //xoc amb el pla
        vec3 punt_xoc = raig.pointAtParameter(temp);
          if ( ( pow( (punt_xoc.x - center.x), 2) + pow(punt_xoc.z - center.z, 2) < pow(radius,2)) && ( !algun_xoc || temp < info.t) ){ // dins el cilindre
              info.t = punt_xoc.t;
              info.p = punt_xoc;
              info.normal = normal;
              info.mat_ptr = material.get();
              algun_xoc = true;

          }
    }

    return algun_xoc;


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
