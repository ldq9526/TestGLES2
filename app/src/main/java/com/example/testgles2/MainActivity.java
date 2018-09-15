package com.example.testgles2;

import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.MotionEvent;
import android.view.View;

import java.io.InputStream;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainActivity extends AppCompatActivity implements View.OnTouchListener {

    private GLSurfaceView glSurfaceView;
    private float oldX, oldY;
    private double oldDistance;
    private int hits = 0;

    private double distance(MotionEvent event) {
        float dx = event.getX(0) - event.getX(1);
        float dy = event.getY(0) - event.getY(1);
        return Math.sqrt(dx*dx + dy*dy);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.layout);
        glSurfaceView = (GLSurfaceView)findViewById(R.id.gl_surface_view);
        glSurfaceView.setEGLContextClientVersion(2);
        glSurfaceView.setRenderer(new GLSurfaceView.Renderer() {
            @Override
            public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
                AssetManager assetManager = getAssets();
                String [] textureFileNames = {"asuna.png", "chtholly.jpg", "hinata.png", "kirino.jpg", "mikoto.jpg", "sagiri.jpg"};
                GLUtils.setTextureNumber(textureFileNames.length);
                try {
                    for(int i = 0; i < textureFileNames.length; i++) {
                        InputStream inputStream = assetManager.open(textureFileNames[i]);
                        Bitmap texture = BitmapFactory.decodeStream(inputStream);
                        GLUtils.addTexture(i, texture, texture.getWidth(), texture.getHeight());
                        inputStream.close();
                    }
                } catch (Exception ignored) {}
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
        int action = event.getAction() & MotionEvent.ACTION_MASK;
        if(MotionEvent.ACTION_DOWN == action) {
            hits = 1;
            oldX = event.getX();
            oldY = event.getY();
        } else if(MotionEvent.ACTION_UP == action) {
            hits = 0;
        } else if(MotionEvent.ACTION_POINTER_DOWN == action) {
            hits += 1;
            oldDistance = distance(event);
        } else if(MotionEvent.ACTION_MOVE == action) {
            if(hits >= 2) {
                double newDistance = distance(event);
                if(Math.abs(newDistance - oldDistance) > 5) {
                    if(newDistance > oldDistance)
                        GLUtils.update(0, GLUtils.ROTNULL, .1f);
                    else
                        GLUtils.update(0, GLUtils.ROTNULL, -.1f);
                    glSurfaceView.requestRender();
                    oldDistance = newDistance;
                }
            } else {
                float dx = event.getX() - oldX, dy = event.getY() - oldY;
                float adx = Math.abs(dx), ady = Math.abs(dy);
                if(adx > ady)
                    GLUtils.update(dx/adx, GLUtils.ROTY, 0);
                else
                    GLUtils.update(dy/ady, GLUtils.ROTX, 0);
                glSurfaceView.requestRender();
                oldX += dx;
                oldY += dy;
            }
        } else if(MotionEvent.ACTION_POINTER_UP == action) {
            hits -= 1;
        } else {
            GLUtils.reset();
            glSurfaceView.requestRender();
        }
        return true;
    }
}
