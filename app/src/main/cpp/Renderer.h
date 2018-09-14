#ifndef TESTGLES3_RENDERER_H
#define TESTGLES3_RENDERER_H

#include <GLES2/gl2.h>
#include <vector>

class Renderer {
private:
    GLuint *_textures;
    GLint _angleX, _angleY;
    GLfloat _translationZ;
    GLsizei _width, _height;
    GLuint _programId;
    GLfloat *_vertices, *_colors, *_texCoord;
    GLubyte *_indices;
    GLsizei _count, _vertexN, _textureN;
    int _textureWidth, _textureHeight;
    std::vector<unsigned char *> _textureData;
public:
    Renderer();
    ~Renderer();

    void setVertices(const GLfloat * const &vertices, GLsizei vertexN);
    void setTexCoord(const GLfloat * const &texCoord);
    void setColors(const GLfloat * const &colors);
    void setIndices(const GLubyte * const &indices, GLsizei count);
    void setTextureN(GLsizei textureN);
    void setTextureSize(int width, int height);
    void addTextureData(unsigned char * data);

    void initialize();
    void reshape(GLsizei width, GLsizei height);
    void display();
    void update(GLfloat angle, int rotationAxis, GLfloat translation);
    void reset();
};


#endif
