import org.gradle.kotlin.dsl.support.uppercaseFirstChar

plugins {
    id("com.android.application")
}

android {
    namespace = "com.trans.pvztv"
    compileSdk = 34

    defaultConfig {
        minSdk = 21
        targetSdk = 34
        versionCode = 1
        versionName = "1.1.5"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
        ndk {
            //noinspection ChromeOsAbiSupport
            abiFilters += "armeabi-v7a"
        }
    }

//    sourceSets {
//        main {
//            jniLibs.srcDirs += "src/main/jniLibs"
//        }
//    }
    signingConfigs {
//        release {
//            storeFile = file('D:\\key.keystore') // Keystore文件的路径
//            storePassword 'wewewe' // Keystore密码
//            keyAlias 'key0' // Key别名
//            keyPassword 'wewewe' // Key密码
//        }
    }
    buildTypes {
        release {
            isShrinkResources = false
            isMinifyEnabled = true
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )

        }


    }

    applicationVariants.all { variant ->
        buildOutputs.all {
            this as com.android.build.gradle.internal.api.BaseVariantOutputImpl
            outputFileName = "PvZTVTouch-${variant.buildType.name.uppercaseFirstChar()}-${variant.versionName}"
        }
        true
    }

    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_17
        targetCompatibility = JavaVersion.VERSION_17
    }
    externalNativeBuild {
        cmake {
            path = file("src/main/jni/CMakeLists.txt")
        }
    }
    buildFeatures {
        viewBinding = false
    }

}

dependencies {
    implementation("androidx.annotation:annotation-jvm:1.8.0")
    coreLibraryDesugaring("com.android.tools:desugar_jdk_libs:2.0.4")
}