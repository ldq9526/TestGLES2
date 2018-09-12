package com.example.testgles2;

public class GLUtils {
    static {
        System.loadLibrary("native-lib");
    }

    public static int ROTX = 0, ROTY = 1;

    public static native void initialize();
    public static native void reshape(int width, int height);
    public static native void display();
    public static native void update(float angle, int rotationAxis);
    public static native void reset();
}
