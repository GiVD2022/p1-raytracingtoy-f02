
#pragma once

#include <math.h>
#include <stdlib.h>

#include "Controller.hh"
#include "Model/Modelling/Materials/Material.hh"
#include "Model/Modelling/Materials/Transparent.hh"
#include "SetUp.hh"
#include "glm/gtc/random.hpp"
#include "glm/glm.hpp"

using namespace std;

class RayTracer {

	public:
        // Imatge on es calcularà el rendering
        QImage *image;

        // settings de l'algorisme de visualització: conté la camera, les llums, el
        // tipus de shadings, etc...
        shared_ptr<SetUp> setup;

        // Escena virtual
        shared_ptr<Scene>  scene;

        RayTracer(QImage *i);
        void setPixel(int x, int y, vec3 color);
        vec3 getMeanColor(int x, int y, int width, int heigth,shared_ptr<Camera> camera);
        void run();

private:
        // Funció d'inicialització del raytracing.
        void init();
        // Funcio recursiva que calcula el color. Inicialment
        // es crida a cada pixel de forma no recursiva.
        vec3 RayPixel (Ray &ray, int depth);
};

