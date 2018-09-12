#ifndef TESTGLES3_RENDERER_H
#define TESTGLES3_RENDERER_H

#include <GLES2/gl2.h>

class Renderer {
private:
    GLint _angleX, _angleY;
    GLsizei _width, _height;
    GLuint _programId;
    GLfloat *_vertices, *_colors;
    GLubyte *_indices;
    GLsizei _count;
public:
    Renderer();
    ~Renderer();

    void setVertices(const GLfloat * const &vertices);
    void setColors(const GLfloat * const &colors);
    void setIndices(const GLubyte * const &indices, GLsizei count);

    void initialize();
    void reshape(GLsizei width, GLsizei height);
    void display();
    void update(GLfloat angle, int rotationAxis);
    void reset();
};


#endif
