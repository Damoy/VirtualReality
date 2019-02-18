// -------------
// Updated by FORNALI Damien
// Master 2 - IFI, Nice-Sophia-Antipolis University, 2019
// -------------

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createColoredCube(){
    Cube* de = new Cube();
    double cubeX = ui->position_x_box->value();
    double cubeY = ui->position_y_box->value();
    double cubeZ = ui->position_z_box->value();
    double cubeRotX = ui->rotation_pitch_box->value();
    double cubeRotY = ui->rotation_yaw_box->value();
    double cubeRotZ = ui->rotation_roll_box->value();
    de->setPosition(static_cast<GLfloat>(cubeX), static_cast<GLfloat>(cubeY), static_cast<float>(cubeZ));
    de->setOrientation(static_cast<GLfloat>(cubeRotX), static_cast<GLfloat>(cubeRotY), static_cast<float>(cubeRotZ));
    ui->openGLWidget->addDrawable(de);
}

void MainWindow::createDeAJouer(){
    DeAJouer* de = new DeAJouer();
    double cubeX = ui->position_x_box->value();
    double cubeY = ui->position_y_box->value();
    double cubeZ = ui->position_z_box->value();
    double cubeRotX = ui->rotation_pitch_box->value();
    double cubeRotY = ui->rotation_yaw_box->value();
    double cubeRotZ = ui->rotation_roll_box->value();
    de->setPosition(static_cast<GLfloat>(cubeX), static_cast<GLfloat>(cubeY), static_cast<float>(cubeZ));
    de->setOrientation(static_cast<GLfloat>(cubeRotX), static_cast<GLfloat>(cubeRotY), static_cast<float>(cubeRotZ));
    ui->openGLWidget->addDrawable(de);
}

void MainWindow::createTexturedCube(){
    CubeTex* de = new CubeTex();
    QString image = ui->texture_path->toPlainText();
    QString filepath = ":/images/" + image;
    QDirIterator it(":/images/");
    GLboolean exists = false;

    // could be improve with other files formats
    while (it.hasNext()) {
        QString nextImage = it.next();
        if(nextImage == filepath + ".jpg"){
            exists = true;
            break;
        }
    }

    if(!exists){
        std::cout << "Image does not exists !" << std::endl;
        return;
    }

    double cubeX = ui->position_x_box->value();
    double cubeY = ui->position_y_box->value();
    double cubeZ = ui->position_z_box->value();
    double cubeRotX = ui->rotation_pitch_box->value();
    double cubeRotY = ui->rotation_yaw_box->value();
    double cubeRotZ = ui->rotation_roll_box->value();

    de->setTexture(filepath);
    de->setPosition(static_cast<GLfloat>(cubeX), static_cast<GLfloat>(cubeY), static_cast<float>(cubeZ));
    de->setOrientation(static_cast<GLfloat>(cubeRotX), static_cast<GLfloat>(cubeRotY), static_cast<float>(cubeRotZ));
    ui->openGLWidget->addDrawable(de);
}

void MainWindow::createEnlightenedCube(){
    CubeEclaire* cube = new CubeEclaire();
    cube->setTexture(":/images/container");
    cube->setLight(ui->openGLWidget->light());
    double cubeX = ui->position_x_box->value();
    double cubeY = ui->position_y_box->value();
    double cubeZ = ui->position_z_box->value();
    double cubeRotX = ui->rotation_pitch_box->value();
    double cubeRotY = ui->rotation_yaw_box->value();
    double cubeRotZ = ui->rotation_roll_box->value();
    cube->setPosition(static_cast<GLfloat>(cubeX), static_cast<GLfloat>(cubeY), static_cast<float>(cubeZ));
    cube->setOrientation(static_cast<GLfloat>(cubeRotX), static_cast<GLfloat>(cubeRotY), static_cast<float>(cubeRotZ));
    ui->openGLWidget->addDrawable(cube);
}

void MainWindow::changeAmbientLight(){
    Light* light = ui->openGLWidget->light();
    QColor col = QColorDialog::getColor(light->ambientColor(), this);
    if (col.isValid()) {
        QString qss = QString("background-color: %1;\n border: 1px solid black;\n border-radius: 5px;").arg(col.name());
        ui->ambientButton->setStyleSheet(qss);
        light->setAmbientColor(col);
    }
}

void MainWindow::changeDiffuseLight(){
    Light* light = ui->openGLWidget->light();
    QColor col = QColorDialog::getColor(light->diffuseColor(), this);
    if (col.isValid()) {
        QString qss = QString("background-color: %1;\n border: 1px solid black;\n border-radius: 5px;").arg(col.name());
        ui->diffuseButton->setStyleSheet(qss);
        light->setDiffuseColor(col);
    }
}

void MainWindow::changeSpecularLight(){
    Light* light = ui->openGLWidget->light();
    QColor col = QColorDialog::getColor(light->specularColor(), this);
    if (col.isValid()) {
        QString qss = QString("background-color: %1;\n border: 1px solid black;\n border-radius: 5px;").arg(col.name());
        ui->specularButton->setStyleSheet(qss);
        light->setSpecularColor(col);
    }
}

void MainWindow::changeLightPosition(){
    float lightX = static_cast<float>(ui->lightX->value());
    float lightY = static_cast<float>(ui->lightY->value());
    float lightZ = static_cast<float>(ui->lightZ->value());
    ui->openGLWidget->light()->setPosition(QVector3D(lightX, lightY, lightZ));
}

void MainWindow::changeSpecularReflectionCoefficient(){
    ui->openGLWidget->light()->setSpecularStrength(ui->coeffSpecular->maximum() - ui->coeffSpecular->value());
}
