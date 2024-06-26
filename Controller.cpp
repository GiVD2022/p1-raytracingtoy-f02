#include "Controller.hh"
#include <iostream>

Controller::Controller()
{
    scene = make_shared<Scene>();
    // Valors per defecte de visualSetup
    visualSetup = make_shared<SetUp>();
}


bool Controller::createScene(SceneFactory::SCENE_TYPES currentType, QString name) {
    shared_ptr<SceneFactory> sf = nullptr;
    switch (currentType)  {
    case SceneFactory::SCENE_TYPES::VIRTUALWORLD:
        std::cout << "Crea escena virtual" << std::endl;
        sf = make_shared<SceneFactoryVirtual>();
        break;
    case SceneFactory::SCENE_TYPES::REALDATA:
        sf = make_shared<SceneFactoryData>();
        break;
    case SceneFactory::SCENE_TYPES::TEMPORALVW:
        // TO DO:  Afegir les factories de escenes temporals amb les animacions
        return false;
      break;
    default:
        break;
    }
    scene = sf->createScene(name);
    return (scene != nullptr);
}

bool Controller::createScene(vec3 position, float radius) {
    // Create a single Sphere
    scene = make_shared<Scene>();
    auto sphere = make_shared<Sphere>(position, radius, 1.0);
    sphere->setMaterial(make_shared<Lambertian>(vec3(0.5, 0.2, 0.7)));
    scene->objects.push_back(sphere);
    return true;

}

bool Controller::createTriangleScene(vec3 v1, vec3 v2, vec3 v3){
    scene = make_shared<Scene>();
    auto triangle = make_shared<Triangle>(v1, v2, v3, -1);
    triangle->setMaterial(make_shared<Lambertian>(vec3(0.3, 0.33, 0.6)));
    scene->objects.push_back(triangle);
    return true;
}

bool Controller::createBoxScene(vec3 pmin, vec3 pmax){
    scene = make_shared<Scene>();
    auto box = make_shared<Box>(pmin, pmax, 1.0);
    box->setMaterial(make_shared<Lambertian>(vec3(0.5, 0.2, 0.7)));
    scene->objects.push_back(box);
    return true;
}

bool Controller::createCylinderScene(vec3 base, vec3 axis, float radious, float height){
    scene = make_shared<Scene>();
    auto cyl = make_shared<Cylinder>(base, axis, radious, height, 1.0);
    cyl->setMaterial(make_shared<Lambertian>(vec3(0.5, 0.2, 0.7)));
    scene->objects.push_back(cyl);
    return true;
}


bool Controller::createScene() {
    //TODO: Pots posar codi per a fer una escena amb multiples esferes
    return true;
}

bool Controller::createScene(int nFrames) {

    //TO DO Fase 3 opcional: Codi exemple amb animacions però que es pot canviar
    // pel que creguis convenient

    auto sphere = make_shared<Sphere>(vec3(0, 0, -1), 0.5, 1.0);
    sphere->setMaterial(make_shared<Lambertian>(vec3(0.5, 0.2, 0.7)));

    shared_ptr<Animation> anim = make_shared<Animation>();
    anim->transf =  make_shared<TranslateTG>(vec3(0.2));
    sphere->addAnimation(anim);

    return true;
}
bool Controller::createSettings(QString name) {
    // Create Settings and set them to the scene
    visualSetup = make_shared<SetUp>();
    if (visualSetup->load(name) ) {
        visualSetup->print(0);
        return (true);
    }
    return false;
}

void Controller::rendering(QImage *image) {
    RayTracer *tracer = new RayTracer(image);
    tracer->run();
    delete tracer;
}


bool Controller::createShading(ShadingFactory::SHADING_TYPES t) {
    visualSetup->setShadingStrategy(ShadingFactory::getInstance().createShading(t));
    return visualSetup->getShadingStrategy()!=nullptr;

}

void Controller::update(int i) {
    scene->update(i);
}
