// FORNALI Damien
// Master 2 - IFI, Nice-Sophia-Antipolis University, 2019
// -------------

#ifndef CUBETEX_H
#define CUBETEX_H

#include "drawable.h"

class CubeTex : public Drawable {
public:
    CubeTex();
    void setTexture(QString textureFileName);
    /** Initialize the textured cube Vertex Array Object */
    void initializeVAO();
    /** Create the textured cube transformation matrix */
    QMatrix4x4 world();
    /** Render the textured cube */
    void draw();
private:
    QOpenGLTexture* m_texture;

};

#endif // CUBETEX_H
