#include "Renderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer() {
    _angleX = _angleY = 0;
    _width = _height = 0;
    _programId = 0;
    _vertices = _colors = nullptr;
    _indices = nullptr;
    _count = 0;
}

Renderer::~Renderer() {}

void Renderer::setVertices(const GLfloat * const &vertices) {
    _vertices = (GLfloat *) vertices;
}

void Renderer::setColors(const GLfloat * const &colors) {
    _colors = (GLfloat *) colors;
}

void Renderer::setIndices(const GLubyte * const &indices, GLsizei count) {
    _indices = (GLubyte *) indices;
    _count = count;
}

void Renderer::initialize() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    const char * const vertexShaderSource =
            "attribute vec3 position;"
                    "attribute vec4 color;"
                    "varying vec4 vertexColor;"
                    "uniform mat4 Tcw;"
                    "void main() {"
                    "gl_Position=Tcw*vec4(position,1.0);"
                    "vertexColor=color;"
                    "}";
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShaderId);

    const char * const fragmentShaderSource =
            "precision mediump float;"
                    "varying vec4 vertexColor;"
                    "void main() {"
                    "gl_FragColor = vertexColor;"
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

    GLuint colorLocation = (GLuint)glGetAttribLocation(_programId, "color");
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, _colors);
    glEnableVertexAttribArray(colorLocation);
}

void Renderer::reshape(GLsizei width, GLsizei height) {
    glViewport(0, 0, _width = width, _height = height);
}

void Renderer::display() {
    if(_vertices == nullptr || _colors == nullptr || _indices == nullptr)
        return ;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 0.0f, -5.0f));
    glm::mat4 model = glm::rotate(glm::mat4(1.f), glm::radians(GLfloat(_angleX)), glm::vec3(0.f, 1.f, 0.f));
    model = glm::rotate(model, glm::radians(GLfloat(_angleY)), glm::vec3(1.f, 0.f, 0.f));
    glm::mat4 Tcw = glm::perspective(glm::radians(60.f), 1.f*_width/_height, 0.1f, 100.f);
    Tcw *= view;
    Tcw *= model;
    GLint TcwLocation = glGetUniformLocation(_programId, "Tcw");
    glUniformMatrix4fv(TcwLocation, 1, GL_FALSE, glm::value_ptr(Tcw));

    glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_BYTE, _indices);
}

void Renderer::update(GLfloat angle, int rotationAxis) {
    if(rotationAxis == 0)
        _angleY += GLint(angle);
    else
        _angleX += GLint(angle);
}

void Renderer::reset() {
    _angleX = _angleY = 0;
}