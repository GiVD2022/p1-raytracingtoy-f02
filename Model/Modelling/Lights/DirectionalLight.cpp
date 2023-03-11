#include "DirectionalLight.hh"

DirectionalLight::DirectionalLight(vec3 direction, vec3 Ia, vec3 Id, vec3 Is, float intensity): Light(Ia, Id, Is)
{
    this->direction = direction;
    this->intensity = intensity;
}

vec3 DirectionalLight::getDirection()
{
    return this->direction;
}

/* no l'implementa perquè la llum no està en un punt (?)
vec3 DirectionalLight::vectorL(vec3 point) {}
*/

/* no l'implementa perquè la llum està a l'infinit (seria atenuacio inf (?)
float DirectionalLight::attenuation(vec3 point) {
    if (abs(a)<DBL_EPSILON && abs(b)<DBL_EPSILON  && abs(c)<DBL_EPSILON) {
        //Si tots els coeficients son 0 considerem que no hi ha atenuacio
        return 1.0f;
    }
    //Calculem la distancia entre el punt i la posicio de la llum
    float d = distance(point, pos);
    return 1.0f/(c*d*d + b*d + a);
}
*/

float DirectionalLight::distanceToLight(vec3 point) {
    return FLT_MAX; //està a infty
}

void DirectionalLight::read (const QJsonObject &json)
{
    Light::read(json);

    if (json.contains("direction") && json["direction"].isArray()) {
        QJsonArray auxVec = json["direction"].toArray();
        direction[0] = auxVec[0].toDouble();
        direction[1] = auxVec[1].toDouble();
        direction[2] = auxVec[2].toDouble();
    }
    if (json.contains("intensity") && json["intensity"].isDouble())
        intensity = json["intensity"].toDouble();
}

//! [1]
void DirectionalLight::write(QJsonObject &json) const
{
    Light::write(json);
    QJsonArray auxArray;
    auxArray.append(direction[0]);auxArray.append(direction[1]);auxArray.append(direction[2]);
    json["direction"] = auxArray;

    json["intensity"] = intensity;

}
//! [1]

void DirectionalLight::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << "Directional Light" << "\n";
    QTextStream(stdout) << indent + 2 << "direction:\t" << direction[0] << ", "<< direction[1] << ", "<< direction[2] << "\n";
    QTextStream(stdout) << indent + 2 << "intensity:\t" << intensity << "\n";


}
