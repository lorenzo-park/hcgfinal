#ifndef BASICMATERIAL_H
#define BASICMATERIAL_H

#include <QOpenGLFunctions>

class BasicMaterial
{
public:
    BasicMaterial();
    BasicMaterial(float x, float y, float depth, int layer);

    void draw();
    void drawTranslucent(float alpha);

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

    GLfloat scale = 3.0f * 0.083f;
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


    float cellSizeX = 2 * scale;
    float cellSizeY = 2 * scale;
    float cellSizeZ = 1.0f;
};

#endif // BASICMATERIAL_H
