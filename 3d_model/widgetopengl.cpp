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
    grabKeyboard();
}

WidgetOpenGL::~WidgetOpenGL()
{
    delete m_plan;
    delete m_avion;
    // delete m_camera;
    delete m_light;
}

void WidgetOpenGL::update(){
    // move plane
    m_avion->avance(1.0f);

    // update camera relative to it
    m_camera->setTarget(m_avion->position());
    float cameraTheta = qDegreesToRadians(90 - m_avion->lacet());
    float cameraPhi = qDegreesToRadians(90 - m_avion->tangage()); // - m_avion->tangage() ?

    m_camera->setTheta(cameraTheta);
    m_camera->setPhi(cameraPhi);
    m_camera->update_position();

    QOpenGLWidget::update();
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
    dx *= 2;
    dy *= 2;

    m_camera->setTheta(m_camera->theta() + dx);
    m_camera->setPhi(m_camera->phi() + dy);

    QOpenGLWidget::update();
    lastPos = pos;
}

Avion *WidgetOpenGL::avion() const
{
    return m_avion;
}

void WidgetOpenGL::setAvion(Avion *avion)
{
    m_avion = avion;
}

Plan *WidgetOpenGL::plan() const
{
    return m_plan;
}

void WidgetOpenGL::setPlan(Plan *plan)
{
    m_plan = plan;
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
    glClearColor(0.0f, 0.61f, 0.86f, 1.0f);
    
    // enable color alpha component
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // camera initialization
    m_camera = new CameraSpherique();
    m_camera->setAspect_ratio(static_cast<GLfloat>(width()) / height());
    m_camera->setPosition(QVector3D(0, 1, 3));
    m_camera->setRho(45.0f);

    // light initialization
    m_light = new Light();
    m_light->setPosition(QVector3D(0, 20, 0));
    m_light->setSpecularStrength(500.0f);

    // create plan
    m_plan = new Plan();
    m_plan->setLargeur(300);
    m_plan->setLongueur(300);
    m_plan->setPosition(0, -20, 0);
    m_plan->setSegLargeur(100);
    m_plan->setSegLongueur(100);
    m_plan->setTexture(":/images/bottom");
    m_plan->setHeightMap(":/images/heightmap7-420x420.png");
    m_plan->initializeVAO();
    m_plan->setLight(m_light);
    m_plan->setCamera(m_camera);

    // create plane
    m_avion = new Avion();
    m_avion->setPosition(0, 0, 0);
    m_avion->setScale(0.5f);
    m_avion->initializeVAO();
    m_avion->setLight(m_light);
    m_avion->setCamera(m_camera);
}

void WidgetOpenGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_avion->draw();
    m_plan->draw();
    update();
}

void WidgetOpenGL::resizeGL(int width, int height)
{
    //transformation de viewport
    glViewport(0, 0, width, height);
}

void WidgetOpenGL::keyPressEvent(QKeyEvent* event){
    // roulis pour tourner sur les cotes (roll)
    // (tangage) pitch pour monter / descendre
    // lacet (yaw) changer de direction

    float speed = 1.0f;

    switch(event->key()){
        case Qt::Key_Up: {
            m_avion->rotateOf(-speed, 0, 0);
            break;
        }
        case Qt::Key_Down: {
            m_avion->rotateOf(speed, 0, 0);
            break;
        }
        case Qt::Key_Right: {
            m_avion->rotateOf(0, -speed, -speed);
            break;
        }
        case Qt::Key_Left: {
            m_avion->rotateOf(0, speed, speed);
            break;
        }
        case Qt::Key_Z: {
            m_avion->accelere(0.02f);
            break;
        }
        case Qt::Key_S: {
            m_avion->accelere(-0.02f);
            break;
        }
//        default: {
//            m_avion->setVitesse(m_avion->vitesse() * 0.98f);
//            break;
//        }
    }

    update();
}
