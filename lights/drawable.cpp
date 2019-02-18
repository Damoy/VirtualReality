// Cours de Réalité Virtuelle
// leo.donati@unice.fr
//
// 2016_2017
//
// Correction TP3
// -------------
// Updated by FORNALI Damien
// Master 2 - IFI, Nice-Sophia-Antipolis University, 2019
// -------------

#include "drawable.h"

Drawable::Drawable()
    : QOpenGLFunctions(),
      m_position(0.0f,0.0f,0.0f),
      m_roulis(0.0f),
      m_tangage(0.0f),
      m_lacet(0.0f)
{
    m_programme = new QOpenGLShaderProgram();
    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vao = new QOpenGLVertexArrayObject();
}

Drawable::~Drawable()
{
    m_programme->removeAllShaders();
    delete m_programme;
    delete m_vbo;
    delete m_vao;
}

void Drawable::initializeShader(QString vs, QString fs)
{
    initializeOpenGLFunctions();

    bool resultat;
    m_programme->create();

    //Vertex Shader
    resultat = m_programme->addShaderFromSourceFile(QOpenGLShader::Vertex, vs);
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Vertex shader");
        msg.setText(m_programme->log());
        msg.exec();
    }

    //Fragment Shader
    resultat = m_programme->addShaderFromSourceFile(QOpenGLShader::Fragment, fs);
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

QMatrix4x4 Drawable::world(){
    QMatrix4x4 world = QMatrix4x4();
    world.translate(m_position);
    world.rotate(m_tangage, 1, 0, 0);
    world.rotate(m_lacet, 0, 1, 0);
    world.rotate(m_roulis, 0, 0, 1);
    return world;
}

void Drawable::rotateOf(GLfloat droulis, GLfloat dtangage, GLfloat dlacet){
    m_roulis += droulis;
    m_tangage += dtangage;
    m_lacet += dlacet;
}

void Drawable::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
    m_position = QVector3D(x, y, z);
}

void Drawable::setOrientation(GLfloat roulis, GLfloat tangage, GLfloat lacet)
{
    m_roulis = roulis; // roll ; z
    m_tangage = tangage; // pitch ; x
    m_lacet = lacet; // yaw ; y
}

Camera *Drawable::camera() const
{
    return m_camera;
}

void Drawable::setCamera(Camera *camera)
{
    m_camera = camera;
}

Light *Drawable::light() const
{
    return m_light;
}

void Drawable::setLight(Light *light)
{
    m_light = light;
}
