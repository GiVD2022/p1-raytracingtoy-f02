#ifndef ROTATETG_HH
#define ROTATETG_HH

#include "TG.hh"

class RotateTG : public TG
{
public:
    glm::vec3 axis;
    float angle;
    RotateTG(float angle, glm::vec3 axis);
    virtual ~RotateTG();

};

#endif // ROTATETG_HH
