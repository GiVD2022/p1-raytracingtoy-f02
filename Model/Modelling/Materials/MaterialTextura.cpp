#include "MaterialTextura.hh"

MaterialTextura::MaterialTextura(const vec3& color): ToonMaterial()
{
    Kd = color;
}

MaterialTextura::MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k):
    ToonMaterial(a, d, s, k) {
}

MaterialTextura::MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k, const float o):
    ToonMaterial(a, d, s, k, o) {

}

MaterialTextura::~MaterialTextura()
{
}

vec3 MaterialTextura::getDiffuse(vec2 point) const {
    return textura->getColorPixel(point);
}

bool MaterialTextura::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const  {
    color = textura->getColorPixel(rec.uv);
    return textura->getSuccess();
}

void MaterialTextura::read(const QJsonObject &json){
Material::read(json);
QTextStream(stdout)<< "llegint com a textura \n";
if (json.contains("textureFile") && json["textureFile"].isString())
    textura = make_shared<Texture>(json["textureFile"].toString());
}
