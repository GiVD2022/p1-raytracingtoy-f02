#include "FittedPlane.hh"


FittedPlane::FittedPlane(vec3 normal, vec3 point, vec2 pmin, vec2 pmax, float v)
    : Plane(normal, point, v), pmin(pmin), pmax(pmax) {}

bool FittedPlane::hit(Ray &r, float tmin, float tmax, HitInfo &info) const {

    // comprovem intersecció entre el pla i el raig
    if (abs(dot(r.getDirection(), normal)) < DBL_EPSILON) {
        return false;
    }

    float d = -normal[0]*point[0] - normal[1]*point[1] - normal[2]*point[2];
    // calculem el valor de t
    float t = -(normal[0] * r.getOrigin()[0] + normal[1] * r.getOrigin()[1] + normal[2] * r.getOrigin()[2] + d) /
              (normal[0] * r.getDirection()[0] + normal[1] * r.getDirection()[1] + normal[2] * r.getDirection()[2]);

    // si t està fora del rang especificat, no hi ha intersecció
    if (t < tmin || t > tmax) {
        return false;
    }

    // calculem el punt d'intersecció
    vec3 p = r.pointAtParameter(t);

    // comprovem si el punt d'intersecció està dins del rectangle definit per pmin i pmax
    if (p[0] < pmin[0] || p[0] > pmax[0] || p[2] < pmin[1] || p[2] > pmax[1]) {
        return false;
    }

    // omplim el camp de info
    info.t = t;
    info.p = p;
    info.normal = normal;
    info.mat_ptr = material.get();

    //Moure perque el (0,0) sigui a baix esquerra i pregngui valors entre 0 i 1
    info.uv = vec2((p[0] - pmin[0])/(pmax[0] - pmin[0]), (p[2] - pmin[1])/(pmax[1] - pmin[1])) ;

    return true;
}

void FittedPlane::read(const QJsonObject &json) {   
    Plane::read(json);
    if (json.contains("pmin") && json["pmin"].isArray()) {
        QJsonArray auxVec = json["pmin"].toArray();
        pmin[0] = auxVec[0].toDouble();
        pmin[1] = auxVec[1].toDouble();
    }
    if (json.contains("pmax") && json["pmax"].isArray()) {
        QJsonArray auxVec = json["pmax"].toArray();
        pmax[0] = auxVec[0].toDouble();
        pmax[1] = auxVec[1].toDouble();
    }
}

void FittedPlane::write(QJsonObject &json) const {
    Plane::write(json);
    json["pmin"] = QJsonArray({ pmin.x, pmin.y });
    json["pmax"] = QJsonArray({ pmax.x, pmax.y });
}

void FittedPlane::print(int indentation) const {
    Plane::print(indentation);
    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "pmin:\t" << pmin.x << ", "<< pmin.y << "\n";
    QTextStream(stdout) << indent << "pmax:\t" << pmax.x << ", "<< pmax.y << "\n";
}

vec3 FittedPlane::getPMin() {
  return glm::vec3(pmin[0], 0.0, pmin[1]);
}

vec3 FittedPlane::getPMax() {
   return glm::vec3(pmax[0], 0.0, pmax[1]);
}

