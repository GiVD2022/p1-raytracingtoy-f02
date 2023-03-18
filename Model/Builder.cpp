#include "Builder.hh"


void Builder::newSphere()
{
    vec3 position(0.0, 0.0, 0.0);
    float radius = 0.5;
    QMessageBox msgBox;
    if (Controller::getInstance()->createScene(position, radius))
            msgBox.setText("One Sphere is created.");
    else msgBox.setText("Not enough memory. Error.");
    msgBox.exec();
}

void Builder::newTriangle()
{
    vec3 v1(0.0, 0.0, 0.0);
    vec3 v2(1.0, 0.0, 0.0);
    vec3 v3(0.0, 1.0, 0.0);
    QMessageBox msgBox;
    if (Controller::getInstance()->createTriangleScene(v1, v2, v3)){
        msgBox.setText("One triangle is created.");
    }else{
        msgBox.setText("Not enogh memory. Error!!");
    }
    msgBox.exec();
}

void Builder::newBox()
{

    vec3 pmin(-0.5, -0.5, -0.5);
    vec3 pmax(0.5, 0.5, 0.5);
    QMessageBox msgBox;
    if (Controller::getInstance()->createBoxScene(pmin, pmax))
            msgBox.setText("One Box is created.");
    else msgBox.setText("Not enough memory. Error.");
    msgBox.exec();
}

void Builder::newCylinder()
{
    vec3 center = vec3(0.0,-0.5,0.0);
    vec3 axis = vec3(0.0,1,0.0);
    float radious = 1;
    float height = 1;
    QMessageBox msgBox;
    if (Controller::getInstance()->createCylinderScene(center,axis, radious, height))
            msgBox.setText("One Cylinder is created.");
    else msgBox.setText("Not enough memory. Error.");
    msgBox.exec();
}

void Builder::newSimulatedScene()
{
   QMessageBox msgBox;
   if (Controller::getInstance()->createScene())
           msgBox.setText("A simulated Scene is created.");
   else msgBox.setText("Not enough memory. Error.");
   msgBox.exec();
}


void Builder::newVirtualScene()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (!fileName.isNull()) {
        QMessageBox msgBox;
        if(Controller::getInstance()->createScene(SceneFactory::SCENE_TYPES::VIRTUALWORLD, fileName))
            msgBox.setText("Virtual Scene well loaded.");
        else msgBox.setText("Scene NOT loaded. Error reading data.");
        msgBox.exec();
    }
}


void Builder::newDataScene()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (!fileName.isNull()) {
        QMessageBox msgBox;
        if (Controller::getInstance()->createScene(SceneFactory::SCENE_TYPES::REALDATA, fileName)) {
                msgBox.setText("Data Scene well loaded.");
        } else msgBox.setText("Scene NOT loaded. Error reading data.");
        msgBox.exec();
    }
}

void Builder::loadSettings() {
    QString fileName = QFileDialog::getOpenFileName();
    if (!fileName.isNull()) {
        QMessageBox msgBox;
        if (Controller::getInstance()->createSettings(fileName)) {
                msgBox.setText("Visual Settings well loaded.");

        } else msgBox.setText("Settings NOT loaded. Error reading data.");
        msgBox.exec();
        emit settingsChanged();
    }
}

void Builder::activaColorShading() {
    QMessageBox msgBox;
    if (Controller::getInstance()->createShading(ShadingFactory::SHADING_TYPES::COLOR)) {
        msgBox.setText("Color Shading created.");
    } else msgBox.setText("Error creating shading");
    msgBox.exec();
}

void Builder::activaNormalShader() {
    QMessageBox msgBox;
    if (Controller::getInstance()->createShading(ShadingFactory::SHADING_TYPES::NORMAL)) {
        msgBox.setText("Normal Shading created.");
    } else msgBox.setText("Error creating shading");
    msgBox.exec();
}

void Builder::activaDepthShader() {
    QMessageBox msgBox;
    if (Controller::getInstance()->createShading(ShadingFactory::SHADING_TYPES::DEPTH)) {
        msgBox.setText("Depth Shading created.");
    } else msgBox.setText("Error creating shading");
    msgBox.exec();
}

void Builder::activaPhongShading() {
    QMessageBox msgBox;
    if (Controller::getInstance()->createShading(ShadingFactory::SHADING_TYPES::PHONG)) {
        msgBox.setText("Phong Shading created.");
    } else msgBox.setText("Error creating shading");
    msgBox.exec();
}

void Builder::activaBlinn_Phong() {
    QMessageBox msgBox;
    if (Controller::getInstance()->createShading(ShadingFactory::SHADING_TYPES::BLINNPHONG)) {
        msgBox.setText("Blinn-Phong Shading created.");
    } else msgBox.setText("Error creating shading");
    msgBox.exec();
}

void Builder::activaCell_Shading() {
    QMessageBox msgBox;
    if (Controller::getInstance()->createShading(ShadingFactory::SHADING_TYPES::CEL)) {
        msgBox.setText("Cel Shading created.");
    } else msgBox.setText("Error creating shading");
    msgBox.exec();
}


