-keep @androidx.annotation.Keep class *
-keepclassmembers class * {
    @androidx.annotation.Keep *;
}

-keep class com.android.** { *; }
-keep class com.transmension.** { *; }

