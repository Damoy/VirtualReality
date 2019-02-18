// Cours de Réalité Virtuelle
// leo.donati@univ-cotedazur.fr
//
// EPU 2018-19

#include "widgetopengl.h"

#define BUFFER_OFFSET(i)   ((char *)NULL + (i))

WidgetOpenGL::WidgetOpenGL(QWidget* parent)
    :QOpenGLWidget(parent),QOpenGLFunctions()
{
    m_programme = new QOpenGLShaderProgram(this);
    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vao = new QOpenGLVertexArrayObject(this);
    m_timer = new QTimer();
    m_angleX = 30.0f;
    m_angleY = 30.0f;
    m_angleZ = 0.0f;
    animationRunning = false;
    m_angleDx = 1.0f;
    m_angleDy = 1.0f;
    m_angleDz = 1.0f;
    fov = 30;
    m_opacity = 1.0f;
}

WidgetOpenGL::~WidgetOpenGL()
{
    m_programme->removeAllShaders();
    delete m_programme;
    delete m_vbo;
    delete m_vao;
}

void WidgetOpenGL::update(){
    updateAnimation();
    QOpenGLWidget::update();
}

// Updating animation
void WidgetOpenGL::updateAnimation(){
    // rotation animation
    if(animationRunning){
        m_angleX += m_angleDx;
        m_angleY += m_angleDy;
        m_angleZ += m_angleDz;

        if(m_angleX >= 360.0f || m_angleX <= 0.0f){
            m_angleDx = -m_angleDx;
        }

        if(m_angleY >= 360.0f || m_angleY <= 0.0f){
            m_angleDy = -m_angleDy;
        }

        if(m_angleZ >= 360.0f || m_angleZ <= 0.0f){
            m_angleDz = -m_angleDz;
        }
    }
}

// To start / stop the animation
void WidgetOpenGL::startAnimation(){
    animationRunning = !animationRunning;
    if(!animationRunning){
        resetAnimation();
    }
}

// To reset animation
void WidgetOpenGL::resetAnimation(){
    m_angleX = 30.0f;
    m_angleY = 30.0f;
    m_angleZ = 0.0f;
    animationRunning = false;
    m_angleDx = 1.0f;
    m_angleDy = 1.0f;
    m_angleDz = 1.0f;
}

// change fov [10, 120]
void WidgetOpenGL::changeFov(int value){
    if(value < 10) value = 10;
    if(value > 120) value = 120;
    this->fov = value;
}

//  change opacity using 100 steps slider
void WidgetOpenGL::changeOpacity(int value){
    m_opacity = 0.01f * value;
    if(m_opacity < 0) m_opacity = 0;
    if(m_opacity > 1) m_opacity = 1;
}

// update last position
void WidgetOpenGL::mousePressEvent(QMouseEvent* event) {
    lastPos = event->pos();
}

void WidgetOpenGL::mouseMoveEvent(QMouseEvent *event) {
    // get event position
    QPoint pos = event->pos();
    // compute position diff
    float dx = (pos.x() - lastPos.x()) / static_cast<float>(width());
    float dy = (pos.y() - lastPos.y()) / static_cast<float>(height());

    // rotate if right button is pressed
    if(event->buttons() == Qt::RightButton){
        m_angleX += dx * 180;
        m_angleY += dy * 180;
    }

    QOpenGLWidget::update();
    // update last position
    lastPos = pos;
}

void WidgetOpenGL::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(1.0f,1.0f,1.0f,1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    initializeShader();
    initializeVAO();

    // enable color alpha component
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // initialize timer
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(0);
}

void WidgetOpenGL::initializeShader()
{
    bool resultat;
    m_programme->create();

    //Vertex Shader
    resultat = m_programme->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Vertex shader");
        msg.setText(m_programme->log());
        msg.exec();
    }

    //Fragment Shader
    resultat = m_programme->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Fragment shader");
        msg.setText(m_programme->log());
        msg.exec();
    }

    //Link
    resultat = m_programme->link();
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Link du shader program");
        msg.setText(m_programme->log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Libération
    m_programme->release();
}

//Dans la classe WidgetOpenGL on modifie la
//méthode initializeVAO qui va se charger de
//créer et remplir le VBO. Dans ce vertex buffer
//il faudra mettre 24 sommets (4 par face) et 24
//couleurs : on définit donc 8 QVector3D
//appelés A, B, C, D, E, F, G, H correspondant
//aux 8 sommets du cube (utilisez le dessin) et
//6 autres QVector3D appelés rouge, vert, bleu,
//cyan, mage

void WidgetOpenGL::initializeVAO()
{
    //Tableau des données : 3 sommets puis 3 couleurs
//    GLfloat vertex_data[] = {
//        1.0f, 0.0f, 0.0f,
//        0.0f, 1.0f, 0.0f,
//        -1.0f, 0.0f, 0.0f,
//        1.0f, 0.0f, 0.0f,
//        0.0f, 1.0f, 0.0f,
//        0.0f, 0.0f, 1.0f
//    };

    // NEW - cube vertices
    QVector3D A(0, 0, 1);
    QVector3D B(1, 0, 1);
    QVector3D C(1, 1, 1);
    QVector3D D(0, 1, 1);
    QVector3D E(0, 0, 0);
    QVector3D F(1, 0, 0);
    QVector3D G(1, 1, 0);
    QVector3D H(0, 1, 0);

    // cube colors
    QVector3D red(1, 0, 0);
    QVector3D green(0, 1, 0);
    QVector3D blue(0, 0, 1);
    QVector3D cyan(0, 1, 1);
    QVector3D magenta(1, 0, 1);
    QVector3D yellow(1, 1, 0);

    // cube data
    QVector3D vertex_data[] = {
        A, B, C, D, // front
        D, C, G, H, // top
        B, F, G, C, // right
        F, E, H, G, // behind
        E, A, D, H, // left
        E, F, B, A, // down

        // colors
        red, red, red, red,
        blue, blue, blue, blue,
        magenta, magenta, magenta, magenta,
        cyan, cyan, cyan, cyan,
        yellow, yellow, yellow, yellow,
        green, green, green, green
    };

    //creation du VA0 et du VBO
    m_vao->create();
    m_vbo->create();

    //Lien du VAO
    m_vao->bind();

        //lien du VBO
        m_vbo->bind();

        //Ecriture des données dans le VBO
        m_vbo->allocate(vertex_data,sizeof(vertex_data));
        m_vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);

        //Lien entre VBO et les variables d'attribut du vertex shader
        m_programme->bind();

            //Lien avec les attributs du programme
            m_programme->setAttributeArray("pos", GL_FLOAT, BUFFER_OFFSET(0), 3);
            m_programme->setAttributeArray("col", GL_FLOAT, BUFFER_OFFSET(24 * sizeof(QVector3D)), 3);

            //Activation des attributs
            m_programme->enableAttributeArray("pos");
            m_programme->enableAttributeArray("col");

        m_programme->release();

        //Liberation
        m_vbo->release();
    m_vao->release();

}

void WidgetOpenGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Définition de la matrice de projetcion
    QMatrix4x4 proj = QMatrix4x4();
    GLfloat aspectRatio = GLfloat(width()) / height();
    proj.perspective(fov, aspectRatio, 0.1f, 100.0f);

    //Définiion de la matrice de vue
    QMatrix4x4 vue = QMatrix4x4();
    vue.translate(0, 0, -5.0f);

    //Définition de la matrice de placement
    QMatrix4x4 model = QMatrix4x4();
    model.rotate(m_angleX, 1, 0, 0);
    model.rotate(m_angleY, 0, 1, 0);
    model.rotate(m_angleZ, 0, 0, 1);
    model.translate(-0.5f, -0.5f, -0.5f);

    //Produit des trois matrices (dans ce sens!)
    QMatrix4x4 matrix = proj * vue * model;

    m_programme->bind();
    m_programme->setUniformValue("u_ModelViewProjectionMatrix", matrix);
    m_programme->setUniformValue("u_opacity", m_opacity);

    m_vao->bind();

    // cube
    for(int i = 0; i < 6; ++i){
        glDrawArrays(GL_TRIANGLE_FAN, 4 * i, 4);
    }

    m_vao->release();
    m_programme->release();
}


void WidgetOpenGL::resizeGL(int width, int height)
{
    //transformation de viewport
    glViewport(0, 0, width, height);
}
