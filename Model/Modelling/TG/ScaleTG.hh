#pragma once

#include "TG.hh"

class ScaleTG : public TG
{
public:
    glm::vec3 scale;

    ScaleTG(glm::vec3 scale);
    virtual ~ScaleTG();
};
