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
