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
    void newSimulatedScene();
    void newVirtualScene();
    void newDataScene();
    void loadSettings();
    void activaColorShading();
    void activaDepthShader();
    void activaNormalShader();

signals:
     void settingsChanged();
};

