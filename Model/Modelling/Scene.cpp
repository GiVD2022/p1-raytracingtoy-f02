#include "Scene.hh"

Scene::Scene()
{
    pmin.x = -0.5f;  pmin.y = -0.5f; pmin.z = -0.5f;
    pmax.x = 0.5f;  pmax.y = 0.5f; pmax.z = 0.5f;
}

Scene::Scene(shared_ptr<Object> base): basePlane(nullptr), baseSphere(nullptr)
{
    pmin.x = -0.5f;  pmin.y = -0.5f; pmin.z = -0.5f;
    pmax.x = 0.5f;  pmax.y = 0.5f; pmax.z = 0.5f;
    // Check the type of base object
    if (auto plane = std::dynamic_pointer_cast<FittedPlane>(base)) {
        basePlane = plane;
    } else if (auto sphere = std::dynamic_pointer_cast<Sphere>(base)) {
        baseSphere = sphere;
    }
}


bool Scene::hit(Ray &raig, float tmin, float tmax, HitInfo& info) const {
    // TODO FASE 0 i FASE 1:
    // Heu de codificar la vostra solucio per aquest metode substituint el 'return true'
    // Una possible solucio es cridar el mètode "hit" per a tots els objectes i quedar-se amb la interseccio
    // mes propera a l'observador, en el cas que n'hi hagi més d'una.
    // Si un objecte es intersecat pel raig, el parametre  de tipus HitInfo conte
    // la informació sobre la interseccio.
    // Cada vegada que s'intersecta un objecte s'ha d'actualitzar el HitInfo del raig.
    bool hit_anything = false;
    float closest_t = tmax;
    HitInfo temp_info;
    if(basePlane != nullptr && basePlane->hit(raig, tmin, closest_t, temp_info)) {
        info = temp_info;
        hit_anything = true;
    } else {
        for (const auto& object : objects) {
            if (object->hit(raig, tmin, closest_t, temp_info)) {
                hit_anything = true;
                closest_t = temp_info.t;
                info = temp_info;
            }
        }
    }

    if (hit_anything) {
        // Pintar l'esfera de color lila
        if (info.mat_ptr->Kd == vec3(1.0f, 0.0f, 1.0f)) {
            info.mat_ptr->Kd = vec3(0.5f, 0.0f, 0.5f);
        }
    }
    return hit_anything;
}


void Scene::update(int nframe) {
    for (unsigned int i = 0; i< objects.size(); i++) {
        objects[i]->update(nframe);
    }
}

void Scene::setDimensions(vec3 p1, vec3 p2) {
    pmin = p1;
    pmax = p2;
}

