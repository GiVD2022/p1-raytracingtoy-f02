#include "SceneFactoryData.hh"

SceneFactoryData::SceneFactoryData(shared_ptr<VisualMapping> mr):SceneFactory()
{
    mapping = mr;
}


shared_ptr<Scene> SceneFactoryData::createScene(QString nameFile) {
    scene = make_shared<Scene>();
    load(nameFile);
    print(0);
    return visualMaps();
}


shared_ptr<Scene> SceneFactoryData::createScene() {
    auto scene= make_shared<Scene>();
    //  TODO: Només si voleu provar manualment algunes dades posades
    //  hardcoded aqui

    return scene;
}


//! [3]
bool SceneFactoryData::load(QString nameFile)
{
    QFile loadFile(nameFile);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open the data scene file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonParseError error;
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData, &error));


    if (loadDoc.isNull()) {
        qWarning("Parse error in json data scene file.");
        return false;
    }
    QJsonObject object = loadDoc.object();
    read(object);

    QTextStream(stdout) << "Loaded data scene" << "...\n";
    return true;
}
//! [3]

//! [4]
bool SceneFactoryData::save(QString nameFile) const
{
    QFile saveFile(QString(nameFile.append(".json")));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open data file.");
        return false;
    }

    QJsonObject setUpObject;
    write(setUpObject);
    saveFile.write(QJsonDocument(setUpObject).toJson());

    return true;
}

//! [0]
void SceneFactoryData::read(const QJsonObject &json)
{
    QTextStream(stdout)<<"read"<<"\n";
    if (json.contains("scene") && json["scene"].isString()){
        QTextStream(stdout)<<"contains scene"<<"\n";
        scene->name = json["scene"].toString();
    }

    if (json.contains("typeScene") && json["typeScene"].isString()){
        QTextStream(stdout)<<"contains typeScene"<<"\n";
        currentType = getSceneFactoryType(json["typeScene"].toString());
    }

    if (json.contains("base") && json["base"].isObject()) {
        QTextStream(stdout)<<"contains base and is object"<<"\n";
        QJsonObject jbase = json["base"].toObject();
        shared_ptr<Object> o;
        if (jbase.contains("type") && jbase["type"].isString()) {

            QString objStr = jbase["type"].toString().toUpper();

            // TO DO: Fase 1: PAS 5: Afegeix l'objecte base a l'escena.
            // En aquestes linies es crea però no s'afegeix

            o = ObjectFactory::getInstance().createObject(ObjectFactory::getInstance().getObjectType(objStr));
            o->read(jbase);

            // Afegir objecte base a l'escena
            if (o) {
                if (objStr == "FITTEDPLANE") {
                    scene->setBaseObject(o);
                    scene->setDimensions(std::static_pointer_cast<FittedPlane>(o)->getPMin(), std::static_pointer_cast<FittedPlane>(o)->getPMax());
                    scene->objects.push_back(o);
                } else if(objStr == "SPHERE"){
                    scene->setBaseObject(o);
                    scene->setDimensions(std::static_pointer_cast<Sphere>(o)->getPMin(), std::static_pointer_cast<Sphere>(o)->getPMax());
                    scene->objects.push_back(o);
                }
            }
        }

    }
    mapping = make_shared<VisualMapping>();
    mapping->read(json);

    if (json.contains("attributes") && json["attributes"].isArray()) {
      QJsonArray attributeMappingsArray = json["attributes"].toArray();
      for (int propIndex = 0; propIndex < attributeMappingsArray.size(); propIndex++) {
          QJsonObject propObject = attributeMappingsArray[propIndex].toObject();
          mapping->readAttribute(propObject);
          readData(propObject);

      }
    }
}
//! [0]

void SceneFactoryData::write(QJsonObject &json) const
{
   json["scene"] = scene->name;
   json["typeScene"] = SceneFactory::getNameType(currentType);

   QJsonObject jbase;
   // TO DO Fase 1: Opcional: Cal escriure l'objecte base al fitxer:
   // Descomenta les següents línies
   scene->baseObject->write(jbase);
   auto value = ObjectFactory::getInstance().getIndexType(scene->baseObject);
   jbase["type"]  = ObjectFactory::getInstance().getNameType(value);

   json["base"] = jbase;


   mapping->write(json);

   // Recorrem tots els attributs i per cadascun d'ell
   // fer write dels seus AttributeMapping i de les seves dades associades.
   QJsonArray propsArray;
   for (unsigned int i=0; i<dades.size(); i++) {
       QJsonObject propJson;

       propJson["name"] = dades[i].first;

       writeData(propJson, i);
       mapping->writeAttribute(propJson, i);
       propsArray.append(propJson);
   }
   json["attributes"] = propsArray;
}


void SceneFactoryData::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "scene:\t" << scene->name << "\n";
    QTextStream(stdout) << indent << "typeScene:\t" << SceneFactory::getNameType(currentType) << "\n";
    QTextStream(stdout) << indent << "base:\t\n";
    if(scene->baseObject != nullptr){
        scene->baseObject->print(indentation +2);
    }
    mapping->print(indentation+2);

    QTextStream(stdout) << indent << "Attributes:\t\n";
    for (unsigned int i=0; i<dades.size(); i++) {
        mapping->printAttribute(i, indentation);
        QTextStream(stdout) << indent << "data:\t\n";
        for (unsigned int j=0; j<dades[i].second.size(); j++) {
               QTextStream(stdout) << indent << "[ "<< dades[i].second[j][0]<< ", "<< dades[i].second[j][1]<< ", "<<dades[i].second[j][2]<< " ]\n ";
        }
    }
}



void SceneFactoryData::readData(const QJsonObject &json) {

    vector<vec3> values;

    if (json.contains("data") && json["data"].isArray()) {
        QJsonArray dataArray = json["data"].toArray();
        for (int dataIndex = 0; dataIndex < dataArray.size(); dataIndex++) {
            QJsonArray value = dataArray[dataIndex].toArray();
            vec3 sample;
            sample[0] = value[0].toDouble();
            sample[1] = value[1].toDouble();
            sample[2] = value[2].toDouble();
            values.push_back(sample);
        }
        if (json.contains("name") && json["name"].isString()) {
            QString name = json["name"].toString().toUpper();
            dades.push_back(make_pair(name, values));
        }
    }
}

void SceneFactoryData::writeData (QJsonObject &json, int i) const {

    QJsonArray valuesJson;
    for (unsigned int j=0; j<dades[i].second.size(); j++) {
        QJsonArray val;
        val.append(dades[i].second[j][0]);
        val.append(dades[i].second[j][1]);
        val.append(dades[i].second[j][2]);

        valuesJson.append(val);
    }
    json["data"] = valuesJson;
}

// Metode que mapeja les dades llegides a una escena virtual segons la informació del Visual Mapping
shared_ptr<Scene> SceneFactoryData::visualMaps() {
    QTextStream(stdout)<<"Visual maps"<< dades.size() << "\n";

    // TO DO: A partir de les dades carregades, cal contruir l'escena virtual amb tot colocat al seu lloc
    // i a la seva mida

    // TO DO: Fase 1: PAS 5. Recorregut de les dades:
    for (unsigned int i=0; i< dades.size(); i++) {

        // Per cada valor de l'atribut, cal donar d'alta un objecte (gizmo) a l'escena
        for (unsigned int j=0; j<dades[i].second.size(); j++) {
            auto o = objectMaps(i, j);
            o->setMaterial(materialMaps(i, j));

             // Afegir objecte a l'escena virtual ja amb el seu material corresponent
             scene->objects.push_back(o);
         }
    }
      QTextStream(stdout) << "scene length" << scene->objects.size() << "\n";
    return scene;
}






shared_ptr<Object> SceneFactoryData::objectMaps(int i, int j) {
    QTextStream(stdout)<< "soc al objectMaps: "<< i << " " << j <<"\n";

    // Gyzmo és el tipus d'objecte

    shared_ptr<Object> o;
    // Crea Objecte unitari
    o = ObjectFactory::getInstance().createObject(mapping->attributeMapping[i]->gyzmo);

    // TODO: Fase 1. Cal situar l'objecte unitari creat al (0,0,0) a escala proporcional
    // monReal-monVirtual (valors de mapping) i el valor de la dada, i a la posició corresponent segons
    // les coordenades donades a la dada (corresponen a x, z de mon virtual)
    // Dades (x, y, z) --> Escena Virtual (x_v, 0, z_v) i l'objecte escalat segons
    // la relació de y a escala amb el mon virtual


    // Obtenim les dimensions del mon virtual
    float mv_width = mapping->Vxmax - mapping->Vxmin -1;
    float mv_depth = mapping->Vzmax - mapping->Vzmin -1 ;
    float mv_height = mapping->Vymax - mapping->Vymin;

    // Obtenim les dimensions del mon real
    float mr_width = mapping->Rxmax - mapping->Rxmin;
    float mr_depth = mapping->Rzmax - mapping->Rzmin;

    // a. Calcula primer l'escala
    vec3 sc;

    float scale = 0.25 + 0.8 * ((dades[i].second.at(j).z - mapping->attributeMapping[0]->minValue) / (mapping->attributeMapping[i]->maxValue - mapping->attributeMapping[i]->minValue));
    // Per Zoom i OneValue
    // Perque el major valor tingui radi 2.3 (1.75^(3/2)) i la més petita radi 0.35 (0.5^(2/3))
    //float scale = 0.5 + 1.25 * ((dades[i].second.at(j).z - mapping->attributeMapping[0]->minValue) / (mapping->attributeMapping[i]->maxValue - mapping->attributeMapping[i]->minValue));

    if(mapping->attributeMapping[i]->gyzmo ==  ObjectFactory::getInstance().SPHERE || mapping->attributeMapping[i]->gyzmo ==  ObjectFactory::getInstance().TRIANGLE ){
        sc = vec3(scale);
    } else if (mapping->attributeMapping[i]->gyzmo ==  ObjectFactory::getInstance().BOX || mapping->attributeMapping[i]->gyzmo ==  ObjectFactory::getInstance().CYLINDER){
        //only scale y
        sc = vec3(0.5, scale, 0.5);
    } else {
        QTextStream(stdout)<< "UNKNOWN GYZMO SceneFactoryData::ObjectMaps\n";
    }


    // b. Calcula la translació
    // centre de l'esfera a y = 0
    // Per defecte, l'obj base és un pla
    vec3 trasl;
    float new_x = mapping->Vxmin + 1 + ((dades[i].second.at(j).x - mapping->Rxmin) / mr_width * (mv_width - 2));
    float new_y = 0.f;
    float new_z = mapping->Vzmin + 1 + ((dades[i].second.at(j).y - mapping->Rzmin) / mr_depth * (mv_depth -2 ));
    trasl = vec3(new_x, new_y, new_z);
    // Si és una esfera, modifiquem la translació
    if (auto sphere = std::dynamic_pointer_cast<Sphere>(scene->baseObject)) {
        float phi = new_x * 2.0f * M_PI;
        float theta = new_z * M_PI;

        float x = sphere->getRadius() * std::sin(theta) * std::cos(phi);
        float y = sphere->getRadius() * std::sin(theta) * std::sin(phi);
        float z = sphere->getRadius() * std::cos(theta);
        trasl = glm::vec3(x, y, z) + sphere->getCenter();
    }


    QTextStream(stdout) << "  "  << "scale:\t" << sc[0] << ", "<< sc[1] << ", "<< sc[2] << "\n";
    QTextStream(stdout) << "  "  << "traslation:\t" << trasl[0] << ", "<< trasl[1] << ", "<< trasl[2] << "\n";

    // c. Aplica la TG a l'objecte usant
    //        o->aplicaTG(transformacio)
    auto translation = make_shared<TranslateTG>(TranslateTG(trasl));
    o->aplicaTG(translation);
    auto scalation = make_shared<ScaleTG>(ScaleTG(sc));
    o->aplicaTG(scalation);

    return o;
}

shared_ptr<Material> SceneFactoryData::materialMaps(int i,  int j) {

    AttributeMapping *propinfo = mapping->attributeMapping[i];

    auto tCM = propinfo->colorMapType;
    auto cm = make_shared<ColorMapStatic>(tCM);

    float valorDada = dades[i].second[j][2];

    auto tMat = MaterialFactory::getInstance().getIndexType(propinfo->material);

    // Calcul de l'index de la paleta
    int idx = (int)(255.0*(valorDada-propinfo->minValue)/(propinfo->maxValue-propinfo->minValue));

    return MaterialFactory::getInstance().createMaterial(propinfo->material->Ka,
                                                         cm->getColor(idx),
                                                         propinfo->material->Ks,
                                                         propinfo->material->kt,
                                                         propinfo->material->shininess,
                                                         propinfo->material->opacity,
                                                         propinfo->material->mu_t,tMat);
}

vec3 SceneFactoryData::getPuntBase(ObjectFactory::OBJECT_TYPES gyzmo, vec2 puntReal) {
    if (gyzmo == ObjectFactory::FITTEDPLANE || gyzmo == ObjectFactory::PLANE) {
        return vec3(puntReal.x, 0.0, puntReal.y);
    } else if(gyzmo == ObjectFactory::SPHERE) {
        float lon = -puntReal.x * glm::pi<float>() / 180;
        float lat = puntReal.y * glm::pi<float>() / 180;
        float r = 1.0f;
        vec3 centre(puntReal.x, 0.0, puntReal.y);
        return vec3(r * cos(lat) * cos(lon) + centre.x, r * sin(lat) + centre.y, r * cos(lat) * sin(lon) + centre.z);
    }
    return vec3(0);
}
