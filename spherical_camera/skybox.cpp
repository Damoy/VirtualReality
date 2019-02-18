// FORNALI Damien
// Master 2 - IFI, Nice-Sophia-Antipolis University, 2019
// -------------

#include "skybox.h"

Skybox::Skybox() : Drawable::Drawable(){
}

void Skybox::setTexture(QString textureFileName, int textureIndex){
    this->m_texture[textureIndex] = new QOpenGLTexture(QImage(textureFileName).mirrored());
}

QMatrix4x4 Skybox::world(){
    QMatrix4x4 worldCubeMatrix = Drawable::world();
    worldCubeMatrix.scale(100);
    worldCubeMatrix.translate(-0.5f, -0.5f, -0.5f);
    // last operation is first activated
    return worldCubeMatrix;
}

void Skybox::initializeVAO(){
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

    // cube texture related
    QVector3D NW = QVector3D(0, 1, 0);
    QVector3D NE = QVector3D(1, 1, 0);
    QVector3D SW = QVector3D(0, 0, 0);
    QVector3D SE = QVector3D(1, 0, 0);

    // cube data
    QVector3D vertex_data[] = {
        A, B, C, D, // front
        B, F, G, C, // left
        F, E, H, G, // back
        E, A, D, H, // right
        D, C, G, H, // top
        E, F, B, A, // down

        // texture coords
        SW, SE, NE, NW,
        SW, SE, NE, NW,
        SW, SE, NE, NW,
        SW, SE, NE, NW,
        SW, SE, NE, NW,
        SW, SE, NE, NW
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

void Skybox::draw(){
    // world matrix
    QMatrix4x4 matrix = m_camera->projection() * m_camera->view() * this->world();

    // shader start
    m_programme->bind();
    m_programme->setUniformValue("u_ModelViewProjectionMatrix", matrix);
    m_programme->setUniformValue("texture0", 0);
    m_vao->bind();

    // texture
    glDisable(GL_DEPTH_TEST);
    glFrontFace(GL_CW);
    glEnable(GL_TEXTURE_2D);

    for(int i = 0; i < 6; ++i){
        m_texture[i]->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        m_texture[i]->setMagnificationFilter(QOpenGLTexture::Linear);
        m_texture[i]->bind();
        glDrawArrays(GL_TRIANGLE_FAN, 4 * i, 4);
        m_texture[i]->release();
    }

    glDisable(GL_TEXTURE_2D);
    //glDisable(GL_CW);
    glEnable(GL_DEPTH_TEST);

    m_vao->release();
    m_programme->release();
}
