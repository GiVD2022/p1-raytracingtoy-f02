#ifndef SCALETG_HH
#define SCALETG_HH

#include "TG.hh"

class ScaleTG:public TG
{
public:
    glm::vec3 scale;
    ScaleTG(glm::vec3 scale);
    virtual ~ScaleTG();
};

#endif // SCALETG_HH
