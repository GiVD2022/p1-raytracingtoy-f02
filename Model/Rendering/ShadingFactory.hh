#pragma once

#include "ShadingStrategy.hh"
#include "ColorShading.hh"
#include "ColorShadow.hh"
#include "NormalShading.h"
#include "DepthShading.h"
#include "BlinnPhongShading.hh"
#include "BlinnPhongShadow.hh"

class ShadingFactory
{
public:
    ShadingFactory() {};
    typedef enum  SHADING_TYPES{
        COLOR,
        COLORSHADOW,
        NORMAL,
        DEPTH,
        PHONG,
        BLINNPHONG,
        BLINNPHONGSHADOW
    } SHADING_TYPES;

    static ShadingFactory& getInstance() {
        static ShadingFactory instance;
        return instance;
    }

    shared_ptr<ShadingStrategy>   createShading(SHADING_TYPES t);
    SHADING_TYPES                 getShadingType(QString s);
    QString                       getNameType(SHADING_TYPES t);
    ShadingFactory::SHADING_TYPES getIndexType(shared_ptr<ShadingStrategy> m);
    shared_ptr<ShadingStrategy>   switchShading(shared_ptr<ShadingStrategy> m, bool shadow);
};

