#include "ObjectFactory.hh"

// TODO Fase 1: Crea objectes de més tipus
// Trobaràs l'enumeració d'OBJECT_TYPES en el fitxer FactoryObject.hh
shared_ptr<Object> ObjectFactory::createObject(OBJECT_TYPES t)
{
    shared_ptr<Object> o;
    switch (t) {
    case SPHERE:
        o = make_shared<Sphere>();
        break;
    case PLANE:
        o = make_shared<Plane>();
        break;
    default:
        break;
    }

    return o;
}

shared_ptr<Object> ObjectFactory::createObject( QString s, float data, OBJECT_TYPES t) {
    shared_ptr<Object> o;
    switch (t) {
    case SPHERE:
        o = make_shared<Sphere>(data);
        break;

    default:
        break;
    }

    return o;
}

ObjectFactory::OBJECT_TYPES ObjectFactory::getIndexType(shared_ptr<Object> l) {
    if (dynamic_pointer_cast<Sphere>(l) != nullptr) {
        return OBJECT_TYPES::SPHERE;

    } else if (dynamic_pointer_cast<Plane>(l) != nullptr) {
        return OBJECT_TYPES::PLANE;
    }
    return OBJECT_TYPES::SPHERE;
}

ObjectFactory::OBJECT_TYPES ObjectFactory::getObjectType( QString name) {
    if (name=="SPHERE") return OBJECT_TYPES::SPHERE;
    else if (name=="PLANE") return OBJECT_TYPES::PLANE;
    else if (name=="TRIANGLE") return OBJECT_TYPES::TRIANGLE;
    else if (name=="MESH") return OBJECT_TYPES::MESH;
    else if (name=="BOX") return OBJECT_TYPES::BOX;
    else if (name=="CYLINDER") return OBJECT_TYPES::CYLINDER;
    else if (name=="FITTEDPLANE") return OBJECT_TYPES::FITTEDPLANE;
    else return  OBJECT_TYPES::SPHERE;
}

QString ObjectFactory::getNameType(int t)
{
    switch(t) {
    case SPHERE:
        return(QString("SPHERE"));
        break;
    case PLANE:
        return(QString("PLANE"));
        break;
    case TRIANGLE:
        return(QString("TRIANGLE"));
        break;
    case BOX:
        return(QString("BOX"));
        break;
    case MESH:
        return(QString("MESH"));
        break;
    case CYLINDER:
        return(QString("CYLINDER"));
        break;
    case FITTEDPLANE:
        return(QString("FITTEDPLANE"));
        break;
    default:
        return(QString("SPHERE"));
        break;
    }
}
