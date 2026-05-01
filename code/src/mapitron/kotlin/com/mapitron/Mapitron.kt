package com.mapitron

object Mapitron {
    init {
        System.loadLibrary("mapitron-jni")
    }

    external fun build_type(): String
    external fun add(lhs: Int, rhs: Int): Int
}
