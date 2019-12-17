#ifndef BASICMATERIAL_H
#define BASICMATERIAL_H

#include <QOpenGLFunctions>

class BasicMaterial
{
public:
    BasicMaterial();
    BasicMaterial(float x, float y, float depth, float height);

    void draw();

    void setScale(float x);
    float x;
    float y;
    float depth;

    int layer;

    float getSizeX();
    float getSizeY();
    float getSizeZ();

private:

    float color[3] = {1, 0, 0};

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


    float cellSizeX = 0.1f;
    float cellSizeY = 0.1f;
    float cellSizeZ = 0.01f;
};

#endif // BASICMATERIAL_H
