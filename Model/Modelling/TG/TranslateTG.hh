#pragma once

#include "TG.hh"

class TranslateTG : public TG
{
public:
    glm::vec3 traslation;

    TranslateTG(glm::vec3 trasl);
    virtual ~TranslateTG();
};
