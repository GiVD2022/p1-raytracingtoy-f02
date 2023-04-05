//
// Created by anna on 20/01/2022.
//
#include "Texture.hh"
#include <QTextStream>

Texture::Texture(QString nomfitxer)
{
    success = image.load(nomfitxer);
    if (!success) std::cerr << "Imatge de textura no trobada" << endl;
}
Texture::~Texture() {

}
vec3 Texture::getColorPixel(vec2 uv) {

    if (success) {
        QColor c(image.pixel(qMax(1, int((uv.x)*image.width())), qMax(1, int((uv.y)*image.height() ))));
        return(vec3(c.redF(), c.greenF(), c.blueF()));
    }
    return vec3(0.0f);
}

bool Texture::getSuccess(){
    return success;
}
