#include "DepthShading.h"

vec3 DepthShading::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom) {
    vec3 hit_point = info.p;
    float distance = length(hit_point - lookFrom);

    float max_distance = 10.0f; // maximum distance value to avoid overexposure
    float normalized_distance = distance / max_distance; // normalize distance by max_distance

    // Apply exponential function to adjust the shading factor
    float exponent = 2.0f;
    float factor = exp(-exponent * normalized_distance);

    vec3 color = vec3(1.0f) * (1.0f - factor); // invert the shading factor for distant pixels
    color = clamp(color, vec3(0), vec3(1)); // clamp the color values to ensure they are within [0,1]
    return color;
 }
