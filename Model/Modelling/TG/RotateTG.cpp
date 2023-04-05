#include "RotateTG.hh"

RotateTG::RotateTG(float angle, glm::vec3 axis) : angle(angle), axis(axis) {
    matTG = glm::rotate(glm::mat4(1.0f), angle, axis);
}

RotateTG::~RotateTG() {}

