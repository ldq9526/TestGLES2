#ifndef TESTGLES3_RENDERER_H
#define TESTGLES3_RENDERER_H

#include <GLES2/gl2.h>

class Renderer {
private:
    GLuint *_textures;
    GLint _angleX, _angleY;
    GLfloat _translationZ;
    GLsizei _width, _height;
    GLuint _programId;
    GLfloat *_vertices, *_texCoord;
    GLsizei _vertexN, _textureN;
public:
    Renderer();
    ~Renderer();

    void setVertices(const GLfloat * const &vertices, GLsizei vertexN);
    void setTexCoord(const GLfloat * const &texCoord);
    void setTextureN(GLsizei textureN);
    void addTextureData(int index, unsigned char * data, int width, int height);

    void initialize();
    void reshape(GLsizei width, GLsizei height);
    void display();
    void update(GLfloat angle, int rotationAxis, GLfloat translation);
    void reset();
};


#endif
