package com.example.testgles2;

import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.MotionEvent;
import android.view.View;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainActivity extends AppCompatActivity implements View.OnTouchListener {

    private GLSurfaceView glSurfaceView;
    private float oldX, oldY;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.layout);
        glSurfaceView = (GLSurfaceView)findViewById(R.id.gl_surface_view);
        glSurfaceView.setEGLContextClientVersion(2);
        glSurfaceView.setRenderer(new GLSurfaceView.Renderer() {
            @Override
            public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
                GLUtils.initialize();
            }

            @Override
            public void onSurfaceChanged(GL10 gl10, int width, int height) {
                GLUtils.reshape(width, height);
            }

            @Override
            public void onDrawFrame(GL10 gl10) {
                GLUtils.display();
            }
        });
        glSurfaceView.setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
        glSurfaceView.setOnTouchListener(this);
    }

    @Override
    protected void onResume() {
        super.onResume();
        glSurfaceView.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
        glSurfaceView.onPause();
    }

    @Override
    public boolean onTouch(View view, MotionEvent event) {
        int action = event.getAction();
        if(MotionEvent.ACTION_DOWN == action) {
            oldX = event.getX();
            oldY = event.getY();
        } else if(MotionEvent.ACTION_MOVE == action) {
            float dx = event.getX() - oldX, dy = event.getY() - oldY;
            float adx = Math.abs(dx), ady = Math.abs(dy);
            if(adx > ady)
                GLUtils.update(dx/adx, GLUtils.ROTY);
            else
                GLUtils.update(dy/ady, GLUtils.ROTX);
            glSurfaceView.requestRender();
            oldX += dx;
            oldY += dy;
        } else if(MotionEvent.ACTION_UP != action) {
            GLUtils.reset();
            glSurfaceView.requestRender();
        }
        return true;
    }
}
