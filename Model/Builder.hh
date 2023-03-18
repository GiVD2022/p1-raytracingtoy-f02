#pragma once

#include <QtWidgets>
#include "Controller.hh"

class Builder : public QObject {
    Q_OBJECT

public:
    Builder(){};

public slots:
    void newSphere();
    void newTriangle();
    void newBox();
    void newCylinder();
    void newSimulatedScene();
    void newVirtualScene();
    void newDataScene();
    void loadSettings();
    void activaColorShading();
    void activaDepthShader();
    void activaNormalShader();
    void activaBlinn_Phong();
    void activaCell_Shading();

signals:
     void settingsChanged();
};

