#include "RayTracer.hh"


RayTracer::RayTracer(QImage *i):
    image(i) {

    setup = Controller::getInstance()->getSetUp();
    scene = Controller::getInstance()->getScene();
}


void RayTracer::run() {

    init();
    auto camera = setup->getCamera();
    int  width = camera->viewportX;
    int  height = camera->viewportY;

    for (int y = height-1; y >= 0; y--) {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;  // Progrés del càlcul
        for (int x = 0; x < width; x++) {

            //TODO FASE 2: mostrejar més rajos per pixel segons el valor de "samples"

            float u = (float(x)) / float(width);
            float v = (float(height -y)) / float(height);
            vec3 color(0, 0, 0);

            Ray r = camera->getRay(u, v);

            color = this->RayPixel(r, 0);

            // TODO FASE 2: Gamma correction

            color *= 255;
            setPixel(x, y, color);
        }
    }
}


void RayTracer::setPixel(int x, int y, vec3 color) {

    if (color.r < 0) color.r = 0;
    if (color.g < 0) color.g = 0;
    if (color.b < 0) color.b = 0;

    if (color.r > 255) color.r = 255;
    if (color.g > 255) color.g = 255;
    if (color.b > 255) color.b  = 255;

    image->setPixelColor(x, y, QColor(color.r, color.g, color.b));

}

/* Mètode RayPixel
** TODO: Cal modificar la funcio RayPixel es la funcio recursiva del RayTracing. Cal retocar-lo per:
** FASE 0 per a fer el degradat del fons
** FASES 0 i 1 per a cridar a la intersecció amb l'escena i posar el color de l'objecte (via color, depth o normal)
** FASE 2 per incloure els shading més realistes (Blinn-Phong  i ombres)
** FASE 2 per a tractar reflexions i transparències
**
*/

// Funcio recursiva que calcula el color.
vec3 RayTracer::RayPixel(Ray &ray, int depth) {

    vec3 color = vec3(0);
    vec3 unit_direction;
    HitInfo info;

    if (depth <= setup->getMAXDEPTH() && scene->hit(ray, 0.001, FLT_MAX, info)) {
        vec3 shading_color = setup->getShadingStrategy()->shading(scene, info, setup->getLights(), ray.getOrigin(), setup->getGlobalLight());
        color = clamp(shading_color, vec3(0), vec3(1));

        vec3 attenuation;
        Ray scattered_ray;
        if (info.mat_ptr->scatter(ray, info, attenuation, scattered_ray)) {
            vec3 reflected_color = RayPixel(scattered_ray, depth + 1);
            color += reflected_color * attenuation;
        }

    } else {
        if (setup->getBackground()) {
            // Get the direction of the ray and normalize it
            vec3 ray2 = normalize(ray.getDirection());
            vec3 topColor = setup->getTopBackground();
            vec3 bottomColor = setup->getDownBackground();
            // Interpolate between white and blue based on the y coordinate
            float t = 0.5f * (ray2.y + 1.0f);
            // Compute degradation from white to blue
            color = (1.0f - t) * bottomColor + t * topColor;
        } else {
            color = setup->getGlobalLight();
        }
    }

    return color;
}


void RayTracer::init() {
    auto s = setup->getShadingStrategy();
    auto s_out = ShadingFactory::getInstance().switchShading(s, setup->getShadows());
    if (s_out!=nullptr) setup->setShadingStrategy(s_out);
}

