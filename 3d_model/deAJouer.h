// FORNALI Damien
// Master 2 - IFI, Nice-Sophia-Antipolis University, 2019
// -------------

#ifndef DEAJOUER_H
#define DEAJOUER_H

#include "drawable.h"

class DeAJouer : public Drawable {
public:
    DeAJouer();
    void setTexture(QString textureFileName);
    /** Initialize the Vertex Array Object */
    void initializeVAO();
    /** Create the cube transformation matrix */
    QMatrix4x4 world();
    /** Render the cube */
    void draw();
private:
    QOpenGLTexture* m_texture;

};

#endif // DEAJOUER_H
