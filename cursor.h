#ifndef CURSOR_H
#define CURSOR_H

#include <QOpenGLFunctions>


class Cursor
{
public:
    Cursor();
    Cursor(float x, float y, float depth);

    void draw();

    void setScale(float x);
    float x;
    float y;
    float depth;

    int layer;

    float getSizeX();
    float getSizeY();
    float getSizeZ();

    void setColor(float r, float g, float b);

private:

    float color[3] = {0, 1, 1};

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

#endif // CURSOR_H
