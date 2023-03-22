#include "MaterialFactory.hh"

shared_ptr<Material> MaterialFactory::createMaterial(MATERIAL_TYPES t) {
    shared_ptr<Material> m;
    switch (t) {
    case LAMBERTIAN:
        m = make_shared<Lambertian>();
        break;
    case METAL:
        m = make_shared<Metal>();
        break;
    case TRANSPARENT:
        m = make_shared<Transparent>();
        break;
    case MATERIALTEXTURA:
        m = make_shared<MaterialTextura>();
        break;
    default:
        break;
    }
    return m;
}


shared_ptr<Material> MaterialFactory::createMaterial(vec3 a, vec3 d, vec3 s, vec3 t, float beta, float opacity, float mu, MATERIAL_TYPES type) {
    shared_ptr<Material> m;
    switch (type) {
    case LAMBERTIAN:
        m = make_shared<Lambertian>(a, d, s, beta, opacity);
        break;
    case METAL:
        m = make_shared<Metal>(a,d,s,beta, opacity);
        break;
    case TRANSPARENT:
        // En principi nomes transparent fa servir l'index de refraccio i kt
        m = make_shared<Transparent>(a,d,s,t,beta, opacity,mu);
        break;
    case MATERIALTEXTURA:
        m = make_shared<MaterialTextura>(a,d,s,beta, opacity);
        break;
    default:
        break;
    }
    return m;
}

MaterialFactory::MATERIAL_TYPES MaterialFactory::getIndexType(shared_ptr<Material> m) {
    if (dynamic_pointer_cast<Lambertian>(m) != nullptr) {
        return MATERIAL_TYPES::LAMBERTIAN;
    } else if (dynamic_pointer_cast<Metal>(m) != nullptr) {
        return MATERIAL_TYPES::METAL;
    } else if (dynamic_pointer_cast<Transparent>(m) != nullptr) {
        return MATERIAL_TYPES::TRANSPARENT;
    }else if (dynamic_pointer_cast<MaterialTextura>(m) != nullptr) {
        return MATERIAL_TYPES::MATERIALTEXTURA;
    }
    return MATERIAL_TYPES::LAMBERTIAN;
}

MaterialFactory::MATERIAL_TYPES MaterialFactory::getMaterialType( QString name) {
    if (name=="LAMBERTIAN") return MATERIAL_TYPES::LAMBERTIAN;
    else if (name=="METAL") return MATERIAL_TYPES::METAL;
    else if (name=="TRANSPARENT") return MATERIAL_TYPES::TRANSPARENT;
    else if (name=="MATERIALTEXTURA") return MATERIAL_TYPES::MATERIALTEXTURA;
    else return  MATERIAL_TYPES::LAMBERTIAN;
}

QString MaterialFactory::getNameType(MATERIAL_TYPES t)
{
    switch(t) {
    case LAMBERTIAN:
        return(QString("LAMBERTIAN"));
        break;
    case METAL:
        return(QString("METAL"));
        break;
    case TRANSPARENT:
        return(QString("TRANSPARENT"));
        break;
    case MATERIALTEXTURA:
        return(QString("MATERIALTEXTURA"));
        break;
    default:
        return(QString("LAMBERTIAN"));
        break;
    }
}
