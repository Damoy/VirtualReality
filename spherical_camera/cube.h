// FORNALI Damien
// Master 2 - IFI, Nice-Sophia-Antipolis University, 2019
// -------------

#ifndef CUBE_H
#define CUBE_H

#include "drawable.h"

class Cube : public Drawable {
    public:
        Cube();
        /** Initialize the cube Vertex Array Object */
        void initializeVAO();
        /** Render the cube */
        void draw();
        /** Create the cube transformation matrix */
        QMatrix4x4 world();
};

#endif // CUBE_H
