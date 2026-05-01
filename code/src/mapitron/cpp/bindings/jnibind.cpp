#include <jni.h>
#include <mapitron/mapitron.hpp>

extern "C" {

JNIEXPORT jstring JNICALL
Java_com_mapitron_Mapitron_build_type(JNIEnv* env, jobject)
{
    auto result = mapitron::build_type();
    return env->NewStringUTF(result.c_str());
}

JNIEXPORT jint JNICALL
Java_com_mapitron_Mapitron_add(JNIEnv*, jobject, jint lhs, jint rhs)
{
    return mapitron::add(lhs, rhs);
}

} // extern "C"
