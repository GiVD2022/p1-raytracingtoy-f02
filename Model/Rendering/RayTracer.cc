#include "RayTracer.hh"
#define EPS 0.001f

RayTracer::RayTracer(QImage *i):
    image(i) {
    setup = Controller::getInstance()->getSetUp();
    scene = Controller::getInstance()->getScene();

}

vec3 RayTracer::getMeanColor(int x, int y, int width, int height, shared_ptr<Camera> camera){
    vec3 color(0,0,0);
    Ray r;
    for(int i = 0; i < setup->getSamples(); i++){
        float random_x = linearRand((float)x, (float) x + 1 );//Prenem valors random dins del pixel
        float random_y = linearRand((float)y, (float) y + 1 );
        float u = (float(random_x)) / float(width);
        float v = (float(height) - random_y) / float(height);
        r = camera->getRay(u,v); //Calculem el raig per cada valor
        color += this->RayPixel(r,0);
    }
    color /= setup->getSamples(); //Calculem la mitjana de tots els rajos
    return clamp(color, vec3(0), vec3(1));;
}


void RayTracer::run() {

    init();
    auto camera = setup->getCamera();
    int  width = camera->viewportX;
    int  height = camera->viewportY;

    for (int y = height-1; y >= 0; y--) {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;  // Progrés del càlcul
        for (int x = 0; x < width; x++) {
            vec3 color(0, 0, 0);
            color = getMeanColor(x,y,width,height,camera); //Calculem la mitjana per a disminuir l'escalonat
            color = sqrt(color); //Correció del color
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

    vec3 color = vec3(0); // initialize the color to black
    HitInfo info;
    const vec3& global_light = setup->getGlobalLight();

    if (scene->hit(ray, EPS, FLT_MAX, info)) { //en el cas d'intersecar amb un objecte
        vec3 shading_color = setup->getShadingStrategy()->shading(scene, info, setup->getLights(), ray.getOrigin(), setup->getGlobalLight());
        color = shading_color;
        // Check if the maximum depth has been reached
        if(depth < setup->getMAXDEPTH()){
            // Trace secondary rays
            vec3 attenuation;
            Ray scattered_ray;
            if(info.mat_ptr->scatter(ray, info, attenuation, scattered_ray)){
                color += RayPixel(scattered_ray, depth + 1) * attenuation;
            }
        }
    } else{
        if (setup->getBackground() && depth == 0){ //if background and primary ray
            // Get the direction of the ray and normalize it
            vec3 ray2 = normalize(ray.getDirection());
            vec3 topColor = setup->getTopBackground();
            vec3 bottomColor = setup->getDownBackground();
            // Interpolate between white and blue based on the y coordinate
            float t = 0.5f * (ray2.y + 1.0f);
            // Compute degradation from white to blue
            color = (1.0f - t) * bottomColor + t * topColor;
        } else{ //if secondary ray that doesn't intesect, global light
            color = global_light;
        }
    }
    return color;
}


void RayTracer::init() {
    auto s = setup->getShadingStrategy();
    auto s_out = ShadingFactory::getInstance().switchShading(s, setup->getShadows());
    if (s_out!=nullptr) setup->setShadingStrategy(s_out);
}

