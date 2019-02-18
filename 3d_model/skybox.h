// FORNALI Damien
// Master 2 - IFI, Nice-Sophia-Antipolis University, 2019
// -------------

#ifndef SKYBOX_H
#define SKYBOX_H

#include "drawable.h"

class Skybox : public Drawable {
public:
    Skybox();
    ~Skybox();
    void setTexture(QString textureFileName, int textureIndex);
    /** Initialize the skybox Vertex Array Object */
    void initializeVAO();
    /** Create the skybox transformation matrix */
    QMatrix4x4 world();
    /** Render the skybox */
    void draw();
private:
    QOpenGLTexture* m_texture[6];

};

#endif // SKYBOX_H
