#include "com_example_testgles2_GLUtils.h"
#include "Renderer.h"

static Renderer renderer;

static GLfloat vertices[] = {
        -1.f, 1.f, 1.f,/* 3 */
        -1.f, -1.f, 1.f,/* 7 */
        1.f, -1.f, 1.f,/* 4 */
        1.f, -1.f, 1.f,/* 4 */
        1.f, 1.f, 1.f,/* 0 */
        -1.f, 1.f, 1.f,/* 3 */

        -1.f, 1.f, -1.f,/* 2 */
        -1.f, 1.f, 1.f,/* 3 */
        1.f, 1.f, 1.f,/* 0 */
        1.f, 1.f, 1.f,/* 0 */
        1.f, 1.f, -1.f,/* 1 */
        -1.f, 1.f, -1.f,/* 2 */

        1.f, 1.f, -1.f,/* 1 */
        1.f, -1.f, -1.f,/* 5 */
        -1.f, -1.f, -1.f,/* 6 */
        -1.f, -1.f, -1.f,/* 6 */
        -1.f, 1.f, -1.f,/* 2 */
        1.f, 1.f, -1.f,/* 1 */

        -1.f, -1.f, 1.f,/* 7 */
        -1.f, -1.f, -1.f,/* 6 */
        1.f, -1.f, -1.f,/* 5 */
        1.f, -1.f, -1.f,/* 5 */
        1.f, -1.f, 1.f,/* 4 */
        -1.f, -1.f, 1.f,/* 7 */

        1.f, 1.f, 1.f,/* 0 */
        1.f, -1.f, 1.f,/* 4 */
        1.f, -1.f, -1.f,/* 5 */
        1.f, -1.f, -1.f,/* 5 */
        1.f, 1.f, -1.f,/* 1 */
        1.f, 1.f, 1.f,/* 0 */

        -1.f, 1.f, -1.f,/* 2 */
        -1.f, -1.f, -1.f,/* 6 */
        -1.f, -1.f, 1.f,/* 7 */
        - 1.f, -1.f, 1.f,/* 7 */
        - 1.f, 1.f, 1.f,/* 3 */
        -1.f, 1.f, -1.f/* 2 */
};

static GLfloat texCoord[] = {
        0.f, 0.f,
        0.f, 1.f,
        1.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 0.f
};

extern unsigned char data0[];
extern unsigned char data1[];
extern unsigned char data2[];
extern unsigned char data3[];
extern unsigned char data4[];
extern unsigned char data5[];

JNIEXPORT void JNICALL Java_com_example_testgles2_GLUtils_initialize
        (JNIEnv *, jclass) {
    renderer.setVertices(vertices, 36);
    renderer.setTextureN(6);
    renderer.setTextureSize(128, 128);
    renderer.setTexCoord(texCoord);
    renderer.addTextureData(data0);
    renderer.addTextureData(data1);
    renderer.addTextureData(data2);
    renderer.addTextureData(data3);
    renderer.addTextureData(data4);
    renderer.addTextureData(data5);
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
        (JNIEnv *, jclass, jfloat angle, jint rotationAxis, jfloat translation) {
    renderer.update(angle, rotationAxis, translation);
}

JNIEXPORT void JNICALL Java_com_example_testgles2_GLUtils_reset
        (JNIEnv *, jclass) {
    renderer.reset();
}