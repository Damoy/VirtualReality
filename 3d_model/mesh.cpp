#include "mesh.h"

Mesh::Mesh() : Drawable::Drawable(){
    m_ibo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
}

Mesh::~Mesh(){
    delete m_ibo;
}

void Mesh::setTexture(QString textureFileName){
    this->m_texture = new QOpenGLTexture(QImage(textureFileName));
}

int Mesh::nbVertices() const
{
    return m_nbVertices;
}

void Mesh::setNbVertices(int nbVertices)
{
    m_nbVertices = nbVertices;
}

int Mesh::nbIndices() const
{
    return m_nbIndices;
}

void Mesh::setNbIndices(int nbIndices)
{
    m_nbIndices = nbIndices;
}

void Mesh::initializeVAO(QVector<Vertex>* vec, QVector<GLuint>* ind){
    m_nbVertices = vec->size();
    m_nbIndices = ind->size();

    initializeOpenGLFunctions();
    initializeShader(":/shaders/mesh.vert", ":/shaders/mesh.frag");

    //creation du VA0 et du VBO
    m_vao->create();
    m_vbo->create();
    m_ibo->create();

    //Lien du VAO
    m_vao->bind();

        //lien du VBO
        m_vbo->bind();
        m_ibo->bind();

        //Ecriture des données dans le VBO
        m_vbo->allocate(&(vec->at(0)), m_nbVertices * sizeof(Vertex));
        m_vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);

        m_ibo->allocate(&(ind->at(0)), m_nbIndices * sizeof(GLuint));
        m_ibo->setUsagePattern(QOpenGLBuffer::StaticDraw);

        //Lien entre VBO et les variables d'attribut du vertex shader
        m_programme->bind();

            //Lien avec les attributs du programme
            m_programme->setAttributeArray("pos", GL_FLOAT, BUFFER_OFFSET(0), 3, sizeof(Vertex));
            m_programme->setAttributeArray("normal", GL_FLOAT, BUFFER_OFFSET(sizeof(QVector3D)), 3, sizeof(Vertex));
            m_programme->setAttributeArray("tex", GL_FLOAT, BUFFER_OFFSET(2 * sizeof(QVector3D)), 2, sizeof(Vertex));

            //Activation des attributs
            m_programme->enableAttributeArray("pos");
            m_programme->enableAttributeArray("tex");
            m_programme->enableAttributeArray("normal");

        m_programme->release();

        //Liberation
        //m_vbo->release();
        //m_ibo->release();
    m_vao->release();
}

QOpenGLTexture *Mesh::texture() const
{
    return m_texture;
}

void Mesh::draw(){
    // shader start
    m_programme->bind();
    m_programme->setUniformValue("model", this->world());
    m_programme->setUniformValue("view", m_camera->view());
    m_programme->setUniformValue("projection", m_camera->projection());

    // light
    m_programme->setUniformValue("light_ambient_color", m_light->ambientColor());
    m_programme->setUniformValue("light_diffuse_color", m_light->diffuseColor());
    m_programme->setUniformValue("light_specular_color", m_light->specularColor());
    m_programme->setUniformValue("light_position", m_light->position());
    m_programme->setUniformValue("light_specular_strength", m_light->specularStrength());

    m_programme->setUniformValue("opacity", 1.0f);
    m_programme->setUniformValue("view_position", QVector3D(0, 0, 0));
    m_programme->setUniformValue("texture0", 0);
    m_vao->bind();

    // texture
    glActiveTexture(GL_TEXTURE0); // use first texture
    m_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_texture->bind();

    // enabling
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    glDrawElements(GL_TRIANGLES, m_nbIndices, GL_UNSIGNED_INT, 0);

    // disabling
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);

    m_texture->release();
    m_vao->release();
    m_programme->release();
}
