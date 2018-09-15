#include "com_example_testgles2_GLUtils.h"
#include "Renderer.h"
#include <android/bitmap.h>
#include <opencv2/opencv.hpp>

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

JNIEXPORT void JNICALL Java_com_example_testgles2_GLUtils_setTextureNumber
        (JNIEnv *, jclass, jint n) {
    renderer.setTextureN(n);
}

JNIEXPORT void JNICALL Java_com_example_testgles2_GLUtils_addTexture
        (JNIEnv * env, jclass, jint index, jobject texture, jint width, jint height) {
    void *pixels;
    AndroidBitmap_lockPixels(env, texture, &pixels);
    cv::Mat image(height, width, CV_8UC4, pixels);
    cv::cvtColor(image, image, cv::COLOR_BGRA2BGR);
    renderer.addTextureData(index, image.data, width, height);
    AndroidBitmap_unlockPixels(env, texture);
}

JNIEXPORT void JNICALL Java_com_example_testgles2_GLUtils_initialize
        (JNIEnv *, jclass) {
    renderer.setVertices(vertices, 36);
    renderer.setTexCoord(texCoord);
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