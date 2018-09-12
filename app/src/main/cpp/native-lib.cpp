#include "com_example_testgles2_GLUtils.h"
#include "Renderer.h"

static Renderer renderer;

static GLfloat vertices[] = {
        1.f, 1.f, 1.f,/* 0 */
        1.f, 1.f, -1.f,/* 1 */
        -1.f, 1.f, -1.f,/* 2 */
        -1.f, 1.f, 1.f,/* 3 */
        1.f, -1.f, 1.f,/* 4 */
        1.f, -1.f, -1.f,/* 5 */
        -1.f, -1.f, -1.f,/* 6 */
        -1.f, -1.f, 1.f/* 7 */
};

static GLfloat colors[] = {
        1.f, 0.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 0.f, 1.f, 1.f,
        1.f, 1.f, 0.f, 1.f,
        1.f, 0.f, 1.f, 1.f,
        0.f, 1.f, 1.f, 1.f,
        1.f, .5f, 0.f, 1.f,
        .5f, .5f, .5f, 1.f
};

static GLubyte indices[] = {
        0,1,2, 0,2,3,
        0,3,7, 0,7,4,
        0,4,5, 0,5,1,
        7,6,5, 7,5,4,
        1,5,6, 1,6,2,
        2,6,7, 2,7,3
};

JNIEXPORT void JNICALL Java_com_example_testgles2_GLUtils_initialize
        (JNIEnv *, jclass) {
    renderer.setVertices(vertices);
    renderer.setColors(colors);
    renderer.setIndices(indices, 36);
    renderer.initialize();
}

JNIEXPORT void JNICALL Java_com_example_testgles2_GLUtils_reshape
        (JNIEnv *, jclass, jint width, jint height) {
    renderer.reshape(width, height);
}

JNIEXPORT void JNICALL Java_com_example_testgles2_GLUtils_display
        (JNIEnv *, jclass) {
    renderer.display();
}

JNIEXPORT void JNICALL Java_com_example_testgles2_GLUtils_update
        (JNIEnv *, jclass, jfloat angle, jint rotationAxis) {
    renderer.update(angle, rotationAxis);
}

JNIEXPORT void JNICALL Java_com_example_testgles2_GLUtils_reset
        (JNIEnv *, jclass) {
    renderer.reset();
}