// FORNALI Damien
// Master 2 - IFI, Nice-Sophia-Antipolis University, 2019
// -------------

#ifndef CUBEECLAIRE_H
#define CUBEECLAIRE_H

#include "drawable.h"

class CubeEclaire : public Drawable {
public:
    CubeEclaire();
    void setTexture(QString textureFileName);
    /** Initialize the enlightened textured cube Vertex Array Object */
    void initializeVAO();
    /** Create the enlightened textured cube transformation matrix */
    QMatrix4x4 world();
    /** Render the enlightened textured cube */
    void draw();
private:
    QOpenGLTexture* m_texture;

};

#endif // CUBEECLAIRE_H
