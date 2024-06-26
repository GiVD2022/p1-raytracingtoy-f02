#include "Material.hh"

/**
 * Wikipedia: https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model
 * Considering that the angle between the halfway vector and the surface normal
 * is likely to be smaller than the angle between R and V used in Phong's model
 * (unless the surface is viewed from a very steep angle for which it is likely
 * to be larger), and since Phong is using ( R ⋅ V )**α, an exponent can be set
 * α ′ > α such that ( N ⋅ H )**α ′ is closer to the former expression.
 *
 * For front-lit surfaces (specular reflections on surfaces facing the viewer),
 * α ′ = 4 α will result in specular highlights that very closely match the
 * corresponding Phong reflections.
 *
 * */

//Valors arbitraris. Podem decKdir canviar-los
Material::Material(): Ka(1.0f), Kd(1.0f), Ks(1.0f) {
    shininess = 1.0f;
    beta = shininess;
}

Material::~Material()
{}

Material::Material(vec3 d) {
    Kd = d;
    //Valors arbitraris. Podem decidir canviar-los.
    Ka = vec3(1.0f, 1.0f, 1.0f);
    Ks = vec3(1.0f, 1.0f, 1.0f);
    kt = vec3(1.0f) - Ks;
    shininess = 1.0f;
    beta = shininess;
    mu_t = 0.0f;

}

Material::Material(vec3 a, vec3 d, vec3 s, float shin) {
    //Fase 2
    Ka = a;
    Kd = d;
    Ks = s;
    kt = vec3(1.0f) - Ks;
    shininess = shin;
    beta = shin;
    mu_t = 0.0f;
}

Material::Material(vec3 a, vec3 d, vec3 s, float shin, float opac) {
    //Fase 2
    Ka = a;
    Kd = d;
    Ks = s;
    kt = vec3(1.0f) - Ks;
    shininess = shin;
    beta = shin;
    opacity = opac;
    mu_t = 0.0f;
}

Material::Material(vec3 a, vec3 d, vec3 s, vec3 t, float shin, float opac, float mu) {
    //Fase 2
    Ka = a;
    Kd = d;
    Ks = s;
    kt = t;
    shininess = shin;
    beta = shin;
    opacity = opac;
    mu_t = mu;
}



vec3 Material::getDiffuse(vec2 point) const {
    return Kd;
}

void Material::read (const QJsonObject &json)
{
    if (json.contains("ka") && json["ka"].isArray()) {
        QJsonArray auxVec = json["ka"].toArray();
        Ka[0] = auxVec[0].toDouble();
        Ka[1] = auxVec[1].toDouble();
        Ka[2] = auxVec[2].toDouble();
    }
    if (json.contains("kd") && json["kd"].isArray()) {
        QJsonArray auxVec = json["kd"].toArray();
        Kd[0] = auxVec[0].toDouble();
        Kd[1] = auxVec[1].toDouble();
        Kd[2] = auxVec[2].toDouble();
    }
    if (json.contains("ks") && json["ks"].isArray()) {
        QJsonArray auxVec = json["ks"].toArray();
        Ks[0] = auxVec[0].toDouble();
        Ks[1] = auxVec[1].toDouble();
        Ks[2] = auxVec[2].toDouble();
    }
    if (json.contains("kt") && json["kt"].isArray()) {
        QJsonArray auxVec = json["kt"].toArray();
        kt[0] = auxVec[0].toDouble();
        kt[1] = auxVec[1].toDouble();
        kt[2] = auxVec[2].toDouble();
    }
    if (json.contains("shininess") && json["shininess"].isDouble())
        shininess = json["shininess"].toDouble();
        beta = shininess;
    if (json.contains("opacity") && json["opacity"].isDouble())
        opacity = json["opacity"].toDouble();
    if (json.contains("nut") && json["nut"].isDouble())
        mu_t = json["nut"].toDouble();


}


//! [1]
void Material::write(QJsonObject &json) const
{
    QJsonArray auxArray;
    auxArray.append(Ka[0]);auxArray.append(Ka[1]);auxArray.append(Ka[2]);
    json["ka"] = auxArray;

    QJsonArray auxArray2;
    auxArray2.append(Kd[0]);auxArray2.append(Kd[1]);auxArray2.append(Kd[2]);
    json["kd"] = auxArray2;

    QJsonArray auxArray3;
    auxArray3.append(Ks[0]);auxArray3.append(Ks[1]);auxArray3.append(Ks[2]);
    json["ks"] = auxArray3;

    QJsonArray auxArray4;
    auxArray4.append(kt[0]);auxArray4.append(kt[1]);auxArray4.append(kt[2]);
    json["kt"] = auxArray4;

    json["opacity"] = opacity;
    json["shininess"] = shininess;
    json["nut"] = mu_t;
}

//! [1]

void Material::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "Ka:\t" << Ka[0] << ", "<< Ka[1] << ", "<< Ka[2] << "\n";
    QTextStream(stdout) << indent << "Kd:\t" << Kd[0] << ", "<< Kd[1] << ", "<< Kd[2] << "\n";
    QTextStream(stdout) << indent << "Ks:\t" << Ks[0] << ", "<< Ks[1] << ", "<< Ks[2] << "\n";
    QTextStream(stdout) << indent << "kt:\t" << kt[0] << ", "<< kt[1] << ", "<< kt[2] << "\n";
    QTextStream(stdout) << indent << "shininess:\t" << shininess<< "\n";
    QTextStream(stdout) << indent << "opacity:\t" << opacity<< "\n";
    QTextStream(stdout) << indent << "Refraction index:\t" << mu_t<< "\n";
}


