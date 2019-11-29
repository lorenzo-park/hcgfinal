#ifndef BASE_H
#define BASE_H

#include <QOpenGLFunctions>

class CircuitBase
{
public:
    CircuitBase();

    void draw();

    void setScale(float x);

private:
    GLfloat scale = 3.0f;
    GLfloat coords[6] [4] [3] = {
            { { +1.0f * scale, -1.0f * scale, +1.0f * scale }, { +1.0f * scale, -1.0f * scale, -1.0f * scale },
            { +1.0f * scale, +1.0f * scale, -1.0f * scale }, { +1.0f * scale, +1.0f * scale, +1.0f * scale } },
            { { -1.0f * scale, -1.0f * scale, -1.0f * scale }, { -1.0f * scale, -1.0f * scale, +1.0f * scale },
            { -1.0f * scale, +1.0f * scale, +1.0f * scale }, { -1.0f * scale, +1.0f * scale, -1.0f * scale } },
            { { +1.0f * scale, -1.0f * scale, -1.0f * scale }, { -1.0f * scale, -1.0f * scale, -1.0f * scale },
            { -1.0f * scale, +1.0f * scale, -1.0f * scale }, { +1.0f * scale, +1.0f * scale, -1.0f * scale } },
            { { -1.0f * scale, -1.0f * scale, +1.0f * scale }, { +1.0f * scale, -1.0f * scale, +1.0f * scale },
            { +1.0f * scale, +1.0f * scale, +1.0f * scale }, { -1.0f * scale, +1.0f * scale, +1.0f * scale } },
            { { -1.0f * scale, -1.0f * scale, -1.0f * scale }, { +1.0f * scale, -1.0f * scale, -1.0f * scale },
            { +1.0f * scale, -1.0f * scale, +1.0f * scale }, { -1.0f * scale, -1.0f * scale, +1.0f * scale } },
            { { -1.0f * scale, +1.0f * scale, +1.0f * scale }, { +1.0f * scale, +1.0f * scale, +1.0f * scale },
            { +1.0f * scale, +1.0f * scale, -1.0f * scale }, { -1.0f * scale, +1.0f * scale, -1.0f * scale } }
        };
};

#endif // BASE_H
