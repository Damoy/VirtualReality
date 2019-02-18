#ifndef MESH_H
#define MESH_H

#include "drawable.h"

struct Vertex {
    QVector3D Position;
    QVector3D Normal;
    QVector2D TexCoords;
};

class Mesh : public Drawable
{
public:
    Mesh();
    ~Mesh();
    int nbVertices() const;
    void setNbVertices(int nbVertices);

    int nbIndices() const;
    void setNbIndices(int nbIndices);

    void setTexture(QString textureFileName);
    void draw();
    void initializeVAO(QVector<Vertex> *vec, QVector<GLuint> *ind);
    void initializeVAO(){} // to prevent being an abstract class (drawable has pure virtual method)
    QOpenGLTexture *texture() const;

private:
    int m_nbVertices;
    int m_nbIndices;
    QOpenGLBuffer* m_ibo;
    QOpenGLTexture* m_texture;
};

#endif // MESH_H
