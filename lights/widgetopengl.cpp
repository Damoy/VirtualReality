// Cours de Réalité Virtuelle
// leo.donati@univ-cotedazur.fr
//
// EPU 2018-19
// -------------
// Updated by FORNALI Damien
// Master 2 - IFI, Nice-Sophia-Antipolis University, 2019
// -------------

#include "widgetopengl.h"

#define BUFFER_OFFSET(i)   ((char *)NULL + (i))

WidgetOpenGL::WidgetOpenGL(QWidget* parent)
    :QOpenGLWidget(parent),QOpenGLFunctions()
{
    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_timer = new QTimer();
    animationRunning = false;
}

WidgetOpenGL::~WidgetOpenGL()
{
    delete m_vbo;

    // delete all drawables
    for(Drawable* drawable : m_objects){
        delete drawable;
    }
}

void WidgetOpenGL::update(){
    updateAnimation();
    QOpenGLWidget::update();
}

// Updating drawables animation
void WidgetOpenGL::updateAnimation(){
    if(animationRunning){
        for(Drawable* drawable : m_objects){
            // if not a skybox, rotate
            if(dynamic_cast<Skybox*>(drawable) == nullptr)
                drawable->rotateOf(1, 1, 0);
        }
    }
}

// To start / stop the animation
void WidgetOpenGL::startAnimation(){
    animationRunning = !animationRunning;
}

// To reset the animation
void WidgetOpenGL::resetAnimation(){
    Drawable* skybox = m_objects[0];
    clearAllDrawables();
    m_objects.append(skybox);
    m_camera->setRho(10);
    m_camera->setPhi(0);
    m_camera->setTheta(0);
}

// Clear drawables list
void WidgetOpenGL::clearAllDrawables(){
    m_objects.clear();
}

// change fov [10, 120]
void WidgetOpenGL::changeFov(int value){
    if(value < 10) value = 10;
    if(value > 120) value = 120;
    m_camera->setFov(value);
}

// update last position
void WidgetOpenGL::mousePressEvent(QMouseEvent* event) {
    lastPos = event->pos();
}

void WidgetOpenGL::mouseMoveEvent(QMouseEvent *event) {
    // get event position
    QPoint pos = event->pos();

    // compute position diff
    GLfloat dx = (pos.x() - lastPos.x()) / static_cast<GLfloat>(width());
    GLfloat dy = (pos.y() - lastPos.y()) / static_cast<GLfloat>(height());
//    dx *= 2;
//    dy *= 2;

    m_camera->setTheta(m_camera->theta() + dx);
    m_camera->setPhi(m_camera->phi() + dy);

    QOpenGLWidget::update();
    lastPos = pos;
}

Light *WidgetOpenGL::light() const
{
    return m_light;
}

void WidgetOpenGL::setLight(Light *light)
{
    m_light = light;
}

void WidgetOpenGL::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    
    // enable color alpha component
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // initialize timer
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(0);

    // camera initialization
    m_camera = new CameraSpherique();
    m_camera->setAspect_ratio(static_cast<GLfloat>(width()) / height());
    m_camera->setPosition(QVector3D(0, 0, 3));

    // light initialization
    m_light = new Light();

    // cube initialization
    m_objects = QList<Drawable*>();

    // skybox
    Skybox* skybox = new Skybox();
    skybox->setPosition(0, 0, 0);
    skybox->setOrientation(0, 0, 0);
    skybox->setTexture(":/images/front", 0);
    skybox->setTexture(":/images/left", 1);
    skybox->setTexture(":/images/back", 2);
    skybox->setTexture(":/images/right", 3);
    skybox->setTexture(":/images/top", 4);
    skybox->setTexture(":/images/bottom", 5);

    addDrawable(skybox);

    // create initial blocks
    CubeEclaire* container1 = new CubeEclaire();
    CubeEclaire* container2 = new CubeEclaire();
    CubeEclaire* container3 = new CubeEclaire();

    container1->setPosition(0, 0, -2);
    container1->setTexture(":/images/container");
    container1->setLight(m_light);

    container2->setPosition(0, 0, 0);
    container2->setTexture(":/images/container");
    container2->setLight(m_light);

    container3->setPosition(0, 0, 2);
    container3->setTexture(":/images/container");
    container3->setLight(m_light);

    addDrawable(container1);
    addDrawable(container2);
    addDrawable(container3);
}

void WidgetOpenGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(Drawable* drawable : m_objects){
        drawable->draw();
    }
}

void WidgetOpenGL::resizeGL(int width, int height)
{
    //transformation de viewport
    glViewport(0, 0, width, height);
}

void WidgetOpenGL::addDrawable(Drawable* drawable){
    this->makeCurrent();
    drawable->initializeVAO();
    drawable->setCamera(m_camera);
    m_objects.append(drawable);
}
