package com.fairy.tv;

import android.app.Application;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.trans.pvztv.databinding.CrashHandlerBinding;

import java.io.PrintWriter;
import java.io.StringWriter;

public class CrashHandler {
    public static void applyToApplication(Application application) {
        Thread.setDefaultUncaughtExceptionHandler((thread, throwable) -> {
            Log.e("CrashHandler", "", throwable);
            var intent = new Intent(application, HandlerActivity.class);
            intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            var stringWriter = new StringWriter();
            var printWriter = new PrintWriter(stringWriter);
            throwable.printStackTrace(printWriter);
            intent.putExtra("stacktrace", stringWriter.toString());
            application.getApplicationContext().startActivity(intent);
        });
        var handler = new Handler(Looper.getMainLooper());
        handler.postAtFrontOfQueue(() -> {
            try {
                Looper.loop();
            } catch (Exception e) {
                Log.e("CrashHandler", "", e);
                Toast.makeText(application.getApplicationContext(), e.getMessage(), Toast.LENGTH_LONG).show();
            }
        });
    }

    public static class HandlerActivity extends AppCompatActivity {
        private CrashHandlerBinding binding;
        @Override
        protected void onCreate(@Nullable Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            EdgeToEdge.enable(this);
            binding = CrashHandlerBinding.inflate(getLayoutInflater());
            setContentView(binding.getRoot());
            var stacktrace = getIntent().getStringExtra("stacktrace");
            binding.stacktraceContent.setText(stacktrace);
        }

        @Override
        protected void onDestroy() {
            super.onDestroy();
            binding = null;
        }
    }
}
