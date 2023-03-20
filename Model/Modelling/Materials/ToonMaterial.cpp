#include "ToonMaterial.hh"
#include <iostream>
ToonMaterial::~ToonMaterial()
{}

ToonMaterial::ToonMaterial()
{
}

ToonMaterial::ToonMaterial(vec3 d): Material(d)
{
}
ToonMaterial::ToonMaterial(vec3 a, vec3 d, vec3 s, float shininess): Material(a, d, s, shininess)
{
}
ToonMaterial::ToonMaterial(vec3 a, vec3 d, vec3 s, float shininess, float opacity): Material(a, d, s, shininess, opacity)
{
}

ToonMaterial::ToonMaterial(vec3 a, vec3 d, vec3 s, vec3 t, float shininess, float opacity, float mu): Material(a, d, s, t, shininess, opacity, mu)
{
}


void ToonMaterial::read (const QJsonObject &json)
{
    Material::read(json);

    if (json.contains("colorGradient") && json["colorGradient"].isArray()){
        QJsonArray colorsArray = json["colorGradient"].toArray();
        for (int colorIndex = 0; colorIndex < colorsArray.size(); colorIndex++) {
            QJsonArray colorRGB = colorsArray[colorIndex].toArray();
            vec3 auxColor = vec3(0.0);
            auxColor[0] = colorRGB[0].toDouble();
            auxColor[1] = colorRGB[1].toDouble();
            auxColor[2] = colorRGB[2].toDouble();

            colorGradient.push_back(auxColor);
        }
    }

}


//! [1]
void ToonMaterial::write(QJsonObject &json) const
{
    Material::write(json);

    QJsonArray colorGradientArray;
    for (const auto& col : colorGradient){
        QJsonArray color;
        color.append(col[0]);color.append(col[1]);color.append(col[2]);
    }
    json["colorGradient"] = colorGradientArray;
}

//! [1]

void ToonMaterial::print(int indentation) const
{
    Material::print(indentation);
    const QString indent(indentation * 2, ' ');
    for (const auto& col : colorGradient){
        QTextStream(stdout) << indent << "colorGradinet:\t" << col[0] << ", "<< col[1] << ", "<< col[2] << "\n";
    }
}

