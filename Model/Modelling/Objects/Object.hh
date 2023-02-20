#pragma once

#include "Model/Modelling/Ray.hh"
#include "Model/Modelling/Hitable.hh"
#include "Model/Modelling/Animation.hh"

#include "Model/Modelling/Materials/MaterialFactory.hh"
#include "DataInOut/Serializable.hh"


using namespace std;
// Es la classe pare de tots els objectes que s'han de visualitzar.
// Es fa una classe Objectes que hereda de Hitable i ha d'implementar el metode intersection

class Object: public Hitable, public Animable, public Serializable {
  public:
    Object();
    Object(float d);
    virtual ~Object() {};

    // Metodes a implementar en les classes filles: son  metodes abstractes
    virtual bool hit(Ray& r, float tmin, float tmax, HitInfo& info) const override = 0;
    virtual void aplicaTG(shared_ptr<TG>) override = 0 ;

    // OPCIONAL: Mètode que retorna totes les interseccions de l'objecte
    //    virtual bool allHits(const Ray& r, vector<shared_ptr<HitInfo> infos) const = 0;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    float    getData();
    void     setMaterial(shared_ptr<Material> m);


    shared_ptr<Material> getMaterial();
    QString name;
protected:
    shared_ptr<Material> material;   // Material de l'objecte
    float data;           // valor samplejat per aquest objecte,
                          // en el cas que provingui d'un fitxer de dades
                          // sino, per defecte és -1

};

