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
        vectorDrawables {
            useSupportLibrary = true
        }
    }

//    sourceSets {
//        main {
//            jniLibs.srcDirs += "src/main/jniLibs"
//        }
//    }
    signingConfigs {
        create("common") {

        }
    }
    buildTypes {
        release {
            signingConfig = signingConfigs.getByName("debug")
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
            outputFileName =
                "PvZTVTouch-${variant.buildType.name.uppercaseFirstChar()}-${variant.versionName}"
        }
        true
    }

    compileOptions {
        isCoreLibraryDesugaringEnabled = true

        sourceCompatibility = JavaVersion.VERSION_17
        targetCompatibility = JavaVersion.VERSION_17
    }

    externalNativeBuild {
        cmake {
            path = file("src/main/jni/CMakeLists.txt")
        }
    }

    buildFeatures {
        viewBinding = true
    }

    packaging {
        resources {
            excludes += "/META-INF/{AL2.0,LGPL2.1}"
        }
    }

    android {
        lint {
            baseline = file("lint-baseline.xml")
        }
    }
}

dependencies {
    implementation("com.squareup.moshi:moshi:1.15.1")
    implementation("androidx.core:core:1.13.1")
    implementation("androidx.appcompat:appcompat:1.7.0")
    implementation("androidx.fragment:fragment:1.8.1")
    implementation("androidx.recyclerview:recyclerview:1.3.2")
    implementation("androidx.constraintlayout:constraintlayout:2.1.4")
    implementation("androidx.annotation:annotation:1.8.0")
    implementation("com.google.android.material:material:1.12.0")
    implementation("androidx.lifecycle:lifecycle-runtime:2.8.3")
    implementation("androidx.constraintlayout:constraintlayout:2.1.4")
    implementation("androidx.lifecycle:lifecycle-livedata-ktx:2.8.3")
    implementation("androidx.lifecycle:lifecycle-viewmodel-ktx:2.8.2")
    implementation("androidx.activity:activity:1.9.0")
    coreLibraryDesugaring("com.android.tools:desugar_jdk_libs:2.0.4")

}