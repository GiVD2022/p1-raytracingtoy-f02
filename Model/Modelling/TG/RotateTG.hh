#pragma once

#include "TG.hh"

class RotateTG : public TG
{
public:
    float angle;
    glm::vec3 axis;

    RotateTG(float angle, glm::vec3 axis);
    virtual ~RotateTG();

};
