package com.fairy.tv.floating.widget;

import android.view.MotionEvent;
import android.view.View;

import com.fairy.tv.floating.FloatingController;

public class FloatingDraggableAreas {
    private static final long MIN_DRAG_DURATION_MS = 115;

    public static void makeDraggable(View view, FloatingController floatingController) {
        view.setOnTouchListener(new View.OnTouchListener() {

            private long lastTouchTime;
            private float lastTouchX;
            private float lastTouchY;

            @Override
            public boolean onTouch(View v, MotionEvent event) {
                long currentTime = System.currentTimeMillis();
                long elapsedTime = currentTime - lastTouchTime;

                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        lastTouchTime = currentTime;
                        lastTouchX = event.getRawX();
                        lastTouchY = event.getRawY();
                        return true;

                    case MotionEvent.ACTION_MOVE:
                        if (elapsedTime > MIN_DRAG_DURATION_MS) {
                            int offsetX = Math.round(event.getRawX() - lastTouchX);
                            int offsetY = Math.round(event.getRawY() - lastTouchY);

                            floatingController.offset(offsetX, offsetY);
                            lastTouchX = event.getRawX();
                            lastTouchY = event.getRawY();
                        }
                        return true;

                    case MotionEvent.ACTION_UP:
                        if (elapsedTime < MIN_DRAG_DURATION_MS) {
                            view.performClick();
                        }
                        return true;

                    default:
                        return false;
                }
            }
        });
    }
}
