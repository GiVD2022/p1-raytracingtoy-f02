#pragma once

#include "Material.hh"
#include "Lambertian.hh"
#include "ToonMaterial.hh"
#include "Transparent.hh"
#include "MaterialTextura.hh"
#include "Metal.h"

class MaterialFactory
{
    MaterialFactory(){};
public:
    typedef enum  MATERIAL_TYPES{
        LAMBERTIAN,
        METAL,
        TRANSPARENT,
        MATERIALTEXTURA,
    } MATERIAL_TYPES;

    static MaterialFactory& getInstance() {
        static MaterialFactory instance;
        return instance;
    }

    shared_ptr<Material> createMaterial(MATERIAL_TYPES t);
    shared_ptr<Material> createMaterial(vec3 a, vec3 d, vec3 s, vec3 t,float beta, float opacity, float mu, MATERIAL_TYPES type);
    MATERIAL_TYPES getIndexType (shared_ptr<Material> m);
    MATERIAL_TYPES getMaterialType( QString name);
    QString        getNameType(MATERIAL_TYPES  t);

};
