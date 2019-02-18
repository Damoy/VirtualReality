// FORNALI Damien
// Master 2 - IFI, Nice-Sophia-Antipolis University, 2019
// -------------

#include "deAJouer.h"

DeAJouer::DeAJouer() : Drawable::Drawable(){
    this->setTexture(":/images/texture_de.jpg");
}

void DeAJouer::setTexture(QString textureFileName){
    this->m_texture = new QOpenGLTexture(QImage(textureFileName).mirrored());
}

QMatrix4x4 DeAJouer::world(){
    QMatrix4x4 worldCubeMatrix = Drawable::world();
    worldCubeMatrix.translate(-0.5f, -0.5f, -0.5f);
    return worldCubeMatrix;
}

void DeAJouer::initializeVAO(){
    initializeOpenGLFunctions();
    initializeShader(":/shaders/texture.vert", ":/shaders/texture.frag");

    // NEW - cube vertices
    QVector3D A(0, 0, 1);
    QVector3D B(1, 0, 1);
    QVector3D C(1, 1, 1);
    QVector3D D(0, 1, 1);
    QVector3D E(0, 0, 0);
    QVector3D F(1, 0, 0);
    QVector3D G(1, 1, 0);
    QVector3D H(0, 1, 0);

    // cube data
    QVector3D vertex_data[] = {
        A, B, C, D, // front
        D, C, G, H, // top
        B, F, G, C, // right
        F, E, H, G, // behind
        E, A, D, H, // left
        E, F, B, A, // down

        // texture coords
        // SW, NW, NE, SE
        QVector3D(0, 0.5, 0), QVector3D(0, 0.75, 0), QVector3D(0.25, 0.75, 0), QVector3D(0.25, 0.5, 0),
        QVector3D(0, 0.75, 0), QVector3D(0, 1, 0), QVector3D(0.25, 1, 0), QVector3D(0.25, 0.75, 0),
        QVector3D(0.25, 0.5, 0), QVector3D(0.25, 0.75, 0), QVector3D(0.5, 0.75, 0), QVector3D(0.5, 0.5, 0),
        QVector3D(0.5, 0.5, 0), QVector3D(0.5, 0.75, 0), QVector3D(0.75, 0.75, 0), QVector3D(0.75, 0.5, 0),
        QVector3D(0.75, 0.5, 0), QVector3D(0.75, 0.75, 0), QVector3D(1, 0.75, 0), QVector3D(1, 0.5, 0),
        QVector3D(0, 0.25, 0), QVector3D(0, 0.5, 0), QVector3D(0.25, 0.5, 0), QVector3D(0.25, 0.25, 0)
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
            m_programme->setAttributeArray("tex", GL_FLOAT, BUFFER_OFFSET(24 * sizeof(QVector3D)), 3);

            //Activation des attributs
            m_programme->enableAttributeArray("pos");
            m_programme->enableAttributeArray("tex");

        m_programme->release();

        //Liberation
        m_vbo->release();
    m_vao->release();
}

void DeAJouer::draw(){
    // world matrix
    QMatrix4x4 matrix = m_camera->projection() * m_camera->view() * this->world();

    // shader start
    m_programme->bind();
    m_programme->setUniformValue("u_ModelViewProjectionMatrix", matrix);
    m_programme->setUniformValue("texture0", 0);
    m_vao->bind();

    // texture
    m_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_texture->bind();

    // enabling
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    for(int i = 0; i < 6; ++i){
        glDrawArrays(GL_TRIANGLE_FAN, 4 * i, 4);
    }

    // disabling
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);

    m_texture->release();
    m_vao->release();
    m_programme->release();
}
