#include "Renderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer() {
    _textures = nullptr;
    _angleX = _angleY = 0;
    _translationZ = -5.f;
    _width = _height = 0;
    _programId = 0;
    _vertices = _colors = _texCoord = nullptr;
    _indices = nullptr;
    _count = _vertexN = 0;
}

Renderer::~Renderer() {
    _textureData.clear();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(_textureN, _textures);
    delete [] _textures;
    _textures = nullptr;
}

void Renderer::setVertices(const GLfloat * const &vertices, GLsizei vertexN) {
    _vertices = (GLfloat *) vertices;
    _vertexN = vertexN;
}

void Renderer::setTexCoord(const GLfloat *const &texCoord) {
    _texCoord = (GLfloat *)texCoord;
}

void Renderer::setColors(const GLfloat * const &colors) {
    _colors = (GLfloat *) colors;
}

void Renderer::setIndices(const GLubyte * const &indices, GLsizei count) {
    _indices = (GLubyte *) indices;
    _count = count;
}

void Renderer::setTextureN(GLsizei textureN) {
    _textureN = textureN;
}

void Renderer::setTextureSize(int width, int height) {
    _textureWidth = width;
    _textureHeight = height;
}

void Renderer::addTextureData(unsigned char * data) {
    _textureData.push_back(data);
}

void Renderer::initialize() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    const char * const vertexShaderSource =
            "attribute vec3 position;"
                    "attribute vec2 texCoord;"
                    "varying vec2 vertexTex;"
                    "uniform mat4 Tcw;"
                    "void main() {"
                    "gl_Position=Tcw*vec4(position,1.0);"
                    "vertexTex=texCoord;"
                    "}";
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShaderId);

    const char * const fragmentShaderSource =
            "precision mediump float;"
                    "varying vec2 vertexTex;"
                    "uniform sampler2D sampler;"
                    "void main() {"
                    "gl_FragColor = texture2D(sampler,vertexTex);"
                    "}";
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShaderId);

    _programId = glCreateProgram();
    glAttachShader(_programId, vertexShaderId);
    glAttachShader(_programId, fragmentShaderId);
    glLinkProgram(_programId);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    glUseProgram(_programId);

    GLuint positionLocation = (GLuint)glGetAttribLocation(_programId, "position");
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, _vertices);
    glEnableVertexAttribArray(positionLocation);

    GLuint textureLocation = (GLuint)glGetAttribLocation(_programId, "texCoord");
    glVertexAttribPointer(textureLocation, 2, GL_FLOAT, GL_FALSE, 0, _texCoord);
    glEnableVertexAttribArray(textureLocation);

    if(_textures != nullptr)
        delete [] _textures;
    _textures = new GLuint [_textureN];
    glGenTextures(_textureN, _textures);
    for(int i = 0; i < _textureN; i++) {
        glBindTexture(GL_TEXTURE_2D, _textures[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _textureWidth, _textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, _textureData[i]);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::reshape(GLsizei width, GLsizei height) {
    glViewport(0, 0, _width = width, _height = height);
}

void Renderer::display() {
    if(_vertices == nullptr)
        return ;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, _translationZ));
    glm::mat4 model = glm::rotate(glm::mat4(1.f), glm::radians(GLfloat(_angleX)), glm::vec3(0.f, 1.f, 0.f));
    model = glm::rotate(model, glm::radians(GLfloat(_angleY)), glm::vec3(1.f, 0.f, 0.f));
    glm::mat4 Tcw = glm::perspective(glm::radians(60.f), 1.f*_width/_height, 0.1f, 100.f);
    Tcw *= view;
    Tcw *= model;
    GLint TcwLocation = glGetUniformLocation(_programId, "Tcw");
    glUniformMatrix4fv(TcwLocation, 1, GL_FALSE, glm::value_ptr(Tcw));
    for(int i = 0; i < _textureN; i++) {
        glBindTexture(GL_TEXTURE_2D, _textures[i]);
        glDrawArrays(GL_TRIANGLES, i*6, 6);
    }
}

void Renderer::update(GLfloat angle, int rotationAxis, GLfloat translation) {
    if(rotationAxis == 0)
        _angleY += GLint(angle);
    else if(rotationAxis == 1)
        _angleX += GLint(angle);
    else if(_translationZ + translation < -1.5f)
        _translationZ += translation;
}

void Renderer::reset() {
    _angleX = _angleY = 0;
    _translationZ = -5.f;
}