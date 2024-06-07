package com.fairy.tv.floating.weight;

import android.util.Log;
import android.view.MotionEvent;
import android.view.View;

import com.fairy.tv.floating.FloatingController;

public class FloatingDraggableAreas {
    private static final long REQUIRE_TIME_DRAG = 150;
    public static void asFloatingDraggableArea(View view, FloatingController floatingController) {
        view.setOnTouchListener(new View.OnTouchListener() {

            private long lastDownTime;
            private float lastX;
            private float lastY;

            @Override
            public boolean onTouch(View v, MotionEvent event) {
                var currentTimeMillis = System.currentTimeMillis();
                var downTime = currentTimeMillis - lastDownTime;

                return switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN -> {
                        lastDownTime = currentTimeMillis;
                        yield true;
                    }
                    case MotionEvent.ACTION_MOVE -> {
                        if (downTime > REQUIRE_TIME_DRAG) {
                            var offsetX = Math.round(event.getRawX() - lastX);
                            var offsetY = Math.round(event.getRawY() - lastY);

                            floatingController.offset(offsetX, offsetY);
                        }
                        lastX = event.getRawX();
                        lastY = event.getRawY();
                        yield true;
                    }
                    case MotionEvent.ACTION_UP -> {
                        if (downTime < REQUIRE_TIME_DRAG) {
                            view.performClick();
                        }
                        yield true;
                    }
                    default -> false;
                };
            }
        });
    }

}
