#include "RotateTG.hh"

RotateTG::RotateTG(float angle, glm::vec3 axis) : axis(axis), angle(angle) {
    matTG = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
}

RotateTG::~RotateTG() {}
