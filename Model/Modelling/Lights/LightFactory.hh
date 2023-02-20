#pragma once

#include "Light.hh"
#include "PointLight.hh"

class LightFactory
{
    LightFactory(){};
public:
    typedef enum  {
        POINTLIGHT,
        DIRECTIONALLIGHT,
        SPOTLIGHT,
        AREALIGHT
    } LIGHT_TYPES;

    static LightFactory& getInstance() {
        static LightFactory instance;
        return instance;
    }
    shared_ptr<Light> createLight( LIGHT_TYPES t);
    shared_ptr<Light> createLight(vec3 posicio, vec3 Ia, vec3 Id, vec3 Is, float a, float b, float c,  LIGHT_TYPES t);
    LIGHT_TYPES getIndexType (shared_ptr<Light> l);
    LIGHT_TYPES getLightType( QString name);
    QString getNameType(LIGHT_TYPES  t);

};
