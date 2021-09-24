#include "main.h"
#include <stdio.h>
#include <nbt.h>

void PrintLn(JNIEnv *env, char *message) { // temporary debug only remove it
    jclass systemClass = (*env)->FindClass(env, "java/lang/System");
    if (systemClass == NULL) return;

    jfieldID field = (*env)->GetStaticFieldID(env, systemClass, "out", "Ljava/io/PrintStream;");
    if (field == NULL) return;

    jobject printerObject = (*env)->GetStaticObjectField(env, systemClass, field);
    if (printerObject == NULL) return;

    jclass printerClass = (*env)->FindClass(env, "java/io/PrintStream"); // quite illogic part but well
    jmethodID println = (*env)->GetMethodID(env, printerClass, "println", "(Ljava/lang/String;)V");

    (*env)->CallVoidMethod(env, printerObject, println, (*env)->NewStringUTF(env, message));
}

static nbt_tag_t* get_tag_from_java(JNIEnv *env, jobject tag) {
    jclass tagClass = (*env)->GetObjectClass(env, tag);
    jfieldID afield = (*env)->GetFieldID(env, tagClass, "addr", "J");
    jlong addr = (*env)->GetLongField(env, tag, afield);

    return (nbt_tag_t*) addr;
}

static jobject get_tag_from_c(JNIEnv *env, nbt_tag_t* tag) {
    nbt_tag_type_t type = tag->type;

    jclass clazz;
    jmethodID constructor;
    jvalue args[type != NBT_TYPE_COMPOUND ? 3 : 2];
    args[0].j = (int64_t) tag;
    args[1].i = tag->type;

    switch(type) {
        case NBT_TYPE_BYTE:
            clazz = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagByte");
            constructor = (*env)->GetMethodID(env, clazz, "<init>", "(JIB)V");
            args[2].b = tag->tag_byte.value;
            break;
        case NBT_TYPE_SHORT:
            clazz = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagShort");
            constructor = (*env)->GetMethodID(env, clazz, "<init>", "(JIS)V");
            args[2].s = tag->tag_short.value;
            break;
        case NBT_TYPE_INT:
            clazz = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagInt");
            constructor = (*env)->GetMethodID(env, clazz, "<init>", "(JII)V");
            args[2].i = tag->tag_int.value;
            break;
        case NBT_TYPE_LONG:
            clazz = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagLong");
            constructor = (*env)->GetMethodID(env, clazz, "<init>", "(JIJ)V");
            args[2].j = tag->tag_long.value;
            break;
        case NBT_TYPE_FLOAT:
            clazz = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagFloat");
            constructor = (*env)->GetMethodID(env, clazz, "<init>", "(JIF)V");
            args[2].f = tag->tag_float.value;
            break;
        case NBT_TYPE_DOUBLE:
            clazz = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagDouble");
            constructor = (*env)->GetMethodID(env, clazz, "<init>", "(JID)V");
            args[2].d = tag->tag_double.value;
            break;
        case NBT_TYPE_STRING:
            clazz = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagString");
            constructor = (*env)->GetMethodID(env, clazz, "<init>", "(JILjava/lang/String;)V");
            jstring str = (*env)->NewStringUTF(env, tag->tag_string.value);
            args[2].l = str;
            (*env)->ReleaseStringUTFChars(env, str, tag->tag_string.value);
            break;
        case NBT_TYPE_LIST:
            clazz = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagList");
            constructor = (*env)->GetMethodID(env, clazz, "<init>", "(JII)V");
            args[2].i = tag->tag_list.type;
            break;
        case NBT_TYPE_COMPOUND:
            clazz = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagCompound");
            constructor = (*env)->GetMethodID(env, clazz, "<init>", "(JI)V");
            break;
        case NBT_TYPE_BYTE_ARRAY: {
            clazz = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagByteArray");
            constructor = (*env)->GetMethodID(env, clazz, "<init>", "(JI[B)V");
            size_t size = tag->tag_byte_array.size;
            jbyteArray array = (*env)->NewByteArray(env, size);
            (*env)->SetByteArrayRegion(env, array, 0, size, tag->tag_byte_array.value);
            args[2].l = array;
            (*env)->ReleaseByteArrayElements(env, array, tag->tag_byte_array.value, JNI_ABORT);
            break;
        }
        case NBT_TYPE_SHORT_ARRAY: {
            clazz = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagShortArray");
            constructor = (*env)->GetMethodID(env, clazz, "<init>", "(JI[S)V");
            size_t size = tag->tag_short_array.size;
            jshortArray array = (*env)->NewShortArray(env, size);
            (*env)->SetShortArrayRegion(env, array, 0, size, tag->tag_short_array.value);
            args[2].l = array;
            (*env)->ReleaseShortArrayElements(env, array, tag->tag_short_array.value, JNI_ABORT);
            break;
        }
        case NBT_TYPE_INT_ARRAY: {
            clazz = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagIntArray");
            constructor = (*env)->GetMethodID(env, clazz, "<init>", "(JI[I)V");
            size_t size = tag->tag_int_array.size;
            jintArray array = (*env)->NewIntArray(env, size);
            (*env)->SetIntArrayRegion(env, array, 0, size, tag->tag_int_array.value);
            args[2].l = array;
            (*env)->ReleaseIntArrayElements(env, array, tag->tag_int_array.value, JNI_ABORT);
            break;
        }
        case NBT_TYPE_LONG_ARRAY: {
            clazz = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagLongArray");
            constructor = (*env)->GetMethodID(env, clazz, "<init>", "(JI[J)V");
            size_t size = tag->tag_long_array.size;
            jlongArray array = (*env)->NewLongArray(env, size);
            (*env)->SetLongArrayRegion(env, array, 0, size, tag->tag_long_array.value);
            args[2].l = array;
            (*env)->ReleaseLongArrayElements(env, array, tag->tag_long_array.value, JNI_ABORT);
            break;
        }
        case NBT_TYPE_FLOAT_ARRAY: {
            clazz = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagFloatArray");
            constructor = (*env)->GetMethodID(env, clazz, "<init>", "(JI[F)V");
            size_t size = tag->tag_float_array.size;
            jfloatArray array = (*env)->NewFloatArray(env, size);
            (*env)->SetFloatArrayRegion(env, array, 0, size, tag->tag_float_array.value);
            args[2].l = array;
            (*env)->ReleaseFloatArrayElements(env, array, tag->tag_float_array.value, JNI_ABORT);
            break;
        }
        case NBT_TYPE_DOUBLE_ARRAY: {
            clazz = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagDoubleArray");
            constructor = (*env)->GetMethodID(env, clazz, "<init>", "(JI[D)V");
            size_t size = tag->tag_double_array.size;
            jdoubleArray array = (*env)->NewDoubleArray(env, size);
            (*env)->SetDoubleArrayRegion(env, array, 0, size, tag->tag_double_array.value);
            args[2].l = array;
            (*env)->ReleaseDoubleArrayElements(env, array, tag->tag_double_array.value, JNI_ABORT);
            break;
        }
        case NBT_TYPE_STRING_ARRAY: {
            // todo optimize ? with addAll call ?
            clazz = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagStringArray");
            constructor = (*env)->GetMethodID(env, clazz, "<init>", "(JI[Ljava/lang/String;)V");
            size_t size = tag->tag_string_array.size;

            const char* strc0 = tag->tag_string_array.value[0];
            jstring str0 = (*env)->NewStringUTF(env, strc0);

            jclass strClass = (*env)->FindClass(env, "java/lang/String");
            jobjectArray array = (*env)->NewObjectArray(env, size, strClass, str0);

            (*env)->ReleaseStringUTFChars(env, str0, strc0);

            for(size_t i = 1; i < size; i++) {
                const char* strc = tag->tag_string_array.value[i];
                jstring str = (*env)->NewStringUTF(env, strc);
                (*env)->SetObjectArrayElement(env, array, i, str);
                (*env)->ReleaseStringUTFChars(env, str, strc);
            }

            args[2].l = array;
            // release ???
            break;
        }
    }
    if (!constructor) return NULL;

    jobject result = (*env)->NewObjectA(env, clazz, constructor, args);

    // todo optimize ? with addAll call ?
    if(type == NBT_TYPE_COMPOUND || type == NBT_TYPE_LIST) {
        jclass tagClass = (*env)->GetObjectClass(env, result);
        jfieldID valueField = (*env)->GetFieldID(env, tagClass, "value", "Ljava/util/List;");

        jobject list = (*env)->GetObjectField(env, result, valueField);
        jclass listClass = (*env)->GetObjectClass(env, list);
        jmethodID addMethod = (*env)->GetMethodID(env, listClass, "add", "(Ljava/lang/Object;)Z");

        if(type == NBT_TYPE_COMPOUND) {
            jvalue args[1];
            for(size_t i = 0; i < tag->tag_compound.size; i++) {
                args[0].l = get_tag_from_c(env, tag->tag_compound.value[i]);
                (*env)->CallBooleanMethodA(env, list, addMethod, args);
            }
        } else if(type == NBT_TYPE_LIST) {
            jvalue args[1];
            for(size_t i = 0; i < tag->tag_list.size; i++) {
                args[0].l = get_tag_from_c(env, tag->tag_list.value[i]);
                (*env)->CallBooleanMethodA(env, list, addMethod, args);
            }
        }
    }

    if(tag->name) {
        jclass tagClass = (*env)->GetObjectClass(env, result);
        jfieldID nameField = (*env)->GetFieldID(env, tagClass, "name", "Ljava/lang/String;");

        jstring name = (*env)->NewStringUTF(env, tag->name);
        (*env)->SetObjectField(env, result, nameField, name);
        (*env)->ReleaseStringUTFChars(env, name, tag->name);

        jfieldID nameLenField = (*env)->GetFieldID(env, tagClass, "nameLen", "J");
        (*env)->SetLongField(env, result, nameLenField, tag->name_size);
    }

    return result;
}

static size_t reader_read(void* userdata, uint8_t* data, size_t size) {
  return fread(data, 1, size, userdata);
}

static size_t writer_write(void* userdata, uint8_t* data, size_t size) {
  return fwrite(data, 1, size, userdata);
}

static nbt_tag_t* read_nbt(const char* path, int flags) {

    FILE* file = fopen(path, "rb");

    nbt_reader_t reader;
    reader.read = reader_read;
    reader.userdata = file;

    nbt_tag_t* tag = nbt_parse(reader, flags);

    fclose(file);
    return tag;
}

static void write_nbt(const char* path, nbt_tag_t* tag, int flags) {
    FILE* file = fopen(path, "wb");

    nbt_writer_t writer;
    writer.write = writer_write;
    writer.userdata = file;

    nbt_write(writer, tag, flags);

    fclose(file);
}

JNIEXPORT jobject JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1parse(JNIEnv *env, jclass clazz, jstring path, jint parse_flags) {
    const char* pathc = (*env)->GetStringUTFChars(env, path, JNI_FALSE);
    nbt_tag_t* tag = read_nbt(pathc, parse_flags);
    (*env)->ReleaseStringUTFChars(env, path, pathc);
    return get_tag_from_c(env, tag);
}

JNIEXPORT void JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1write(JNIEnv *env, jclass clazz, jstring path, jlong tag, jint write_flags) {
    const char* pathc = (*env)->GetStringUTFChars(env, path, JNI_FALSE);
    write_nbt(pathc, (nbt_tag_t*) tag, write_flags);
    (*env)->ReleaseStringUTFChars(env, path, pathc);
}

JNIEXPORT jobject JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1new_1tag_1byte(JNIEnv *env, jclass clazz, jbyte value) {
    nbt_tag_t* tag =  nbt_new_tag_byte(value);

    jclass tagClass = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagByte");
    jmethodID constructor = (*env)->GetMethodID(env, tagClass, "<init>", "(JIB)V");

    if (!constructor) return NULL;

    jvalue args[2];
    args[0].j = (int64_t) tag;
    args[1].i = NBT_TYPE_BYTE;
    args[2].b = tag->tag_byte.value;

    return (*env)->NewObjectA(env, tagClass, constructor, args);
}

JNIEXPORT jobject JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1new_1tag_1short(JNIEnv *env, jclass clazz, jshort value) {
    nbt_tag_t* tag =  nbt_new_tag_short(value);

    jclass tagClass = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagShort");
    jmethodID constructor = (*env)->GetMethodID(env, tagClass, "<init>", "(JIS)V");

    if (!constructor) return NULL;

    jvalue args[2];
    args[0].j = (int64_t) tag;
    args[1].i = NBT_TYPE_SHORT;
    args[2].s = tag->tag_short.value;

    return (*env)->NewObjectA(env, tagClass, constructor, args);
}

JNIEXPORT jobject JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1new_1tag_1int(JNIEnv *env, jclass clazz, jint value) {
    nbt_tag_t* tag =  nbt_new_tag_int(value);

    jclass tagClass = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagInt");
    jmethodID constructor = (*env)->GetMethodID(env, tagClass, "<init>", "(JII)V");

    if (!constructor) return NULL;

    jvalue args[2];
    args[0].j = (int64_t) tag;
    args[1].i = NBT_TYPE_INT;
    args[2].i = tag->tag_int.value;

    return (*env)->NewObjectA(env, tagClass, constructor, args);
}

JNIEXPORT jobject JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1new_1tag_1long(JNIEnv *env, jclass clazz, jlong value) {
    nbt_tag_t* tag =  nbt_new_tag_long(value);

    jclass tagClass = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagLong");
    jmethodID constructor = (*env)->GetMethodID(env, tagClass, "<init>", "(JIJ)V");

    if (!constructor) return NULL;

    jvalue args[2];
    args[0].j = (int64_t) tag;
    args[1].i = NBT_TYPE_LONG;
    args[2].j = tag->tag_long.value;

    return (*env)->NewObjectA(env, tagClass, constructor, args);
}

JNIEXPORT jobject JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1new_1tag_1float(JNIEnv *env, jclass clazz, jfloat value) {
    nbt_tag_t* tag =  nbt_new_tag_float(value);

    jclass tagClass = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagFloat");
    jmethodID constructor = (*env)->GetMethodID(env, tagClass, "<init>", "(JIF)V");

    if (!constructor) return NULL;

    jvalue args[2];
    args[0].j = (int64_t) tag;
    args[1].i = NBT_TYPE_FLOAT;
    args[2].f = tag->tag_float.value;

    return (*env)->NewObjectA(env, tagClass, constructor, args);
}

JNIEXPORT jobject JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1new_1tag_1double(JNIEnv *env, jclass clazz, jdouble value) {
    nbt_tag_t* tag =  nbt_new_tag_double(value);

    jclass tagClass = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagDouble");
    jmethodID constructor = (*env)->GetMethodID(env, tagClass, "<init>", "(JID)V");

    if (!constructor) return NULL;

    jvalue args[2];
    args[0].j = (int64_t) tag;
    args[1].i = NBT_TYPE_DOUBLE;
    args[2].d = tag->tag_double.value;

    return (*env)->NewObjectA(env, tagClass, constructor, args);
}

JNIEXPORT jobject JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1new_1tag_1byte_1array(JNIEnv *env, jclass clazz, jbyteArray value, jlong size)
{
    jbyte* valuec = (*env)->GetByteArrayElements(env, value, JNI_FALSE);
    nbt_tag_t* tag = nbt_new_tag_byte_array(valuec, size);

    jclass tagClass = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagByteArray");
    jmethodID constructor = (*env)->GetMethodID(env, tagClass, "<init>", "(JI[B)V");

    if (!constructor) return NULL;

    jvalue args[2];
    args[0].j = (int64_t) tag;
    args[1].i = NBT_TYPE_BYTE_ARRAY;
    args[2].l = value;

    return (*env)->NewObjectA(env, tagClass, constructor, args);
}

JNIEXPORT jobject JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1new_1tag_1string(JNIEnv *env, jclass clazz, jstring value) {
    jsize size = (*env)->GetStringUTFLength(env, value);
    Java_net_minecraft_server_c_libnbt_NBT_nbt_1new_1tag_1string0(env, clazz, value, size);
}

JNIEXPORT jobject JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1new_1tag_1string0(JNIEnv *env, jclass clazz, jstring value, jlong size) {
    const char* valuec = (*env)->GetStringUTFChars(env, value, JNI_FALSE);
    nbt_tag_t* tag = nbt_new_tag_string0(valuec, size);

    jclass tagClass = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagString");
    jmethodID constructor = (*env)->GetMethodID(env, tagClass, "<init>", "(JILjava/lang/String;)V");

    if (!constructor) return NULL;

    jvalue args[2];
    args[0].j = (int64_t) tag;
    args[1].i = NBT_TYPE_STRING;
    args[2].l = value;

    return (*env)->NewObjectA(env, tagClass, constructor, args);
}

JNIEXPORT jobject JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1new_1tag_1list(JNIEnv *env, jclass clazz, jint type) {
    nbt_tag_t* tag = nbt_new_tag_list((nbt_tag_type_t) type);

    jclass tagClass = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagList");
    jmethodID constructor = (*env)->GetMethodID(env, tagClass, "<init>", "(JII)V");

    if (!constructor) return NULL;

    jvalue args[2];
    args[0].j = (int64_t) tag;
    args[1].i = NBT_TYPE_LIST;
    args[2].i = type;

    return (*env)->NewObjectA(env, tagClass, constructor, args);
}

JNIEXPORT jobject JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1new_1tag_1compound(JNIEnv *env, jclass clazz) {
    nbt_tag_t* tag = nbt_new_tag_compound();

    jclass tagClass = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagCompound");
    jmethodID constructor = (*env)->GetMethodID(env, tagClass, "<init>", "(JI)V");

    if (!constructor) return NULL;

    jvalue args[1];
    args[0].j = (int64_t) tag;
    args[1].i = NBT_TYPE_COMPOUND;

    return (*env)->NewObjectA(env, tagClass, constructor, args);
}

JNIEXPORT jobject JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1new_1tag_1int_1array(JNIEnv *env, jclass clazz, jintArray value, jlong size) {
    jint* valuec = (*env)->GetIntArrayElements(env, value, JNI_FALSE);
    nbt_tag_t* tag = nbt_new_tag_int_array(valuec, size);

    jclass tagClass = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagIntArray");
    jmethodID constructor = (*env)->GetMethodID(env, tagClass, "<init>", "(JI[I)V");

    if (!constructor) return NULL;

    jvalue args[2];
    args[0].j = (int64_t) tag;
    args[1].i = NBT_TYPE_INT_ARRAY;
    args[2].l = value;

    return (*env)->NewObjectA(env, tagClass, constructor, args);
}

JNIEXPORT jobject JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1new_1tag_1long_1array(JNIEnv *env, jclass clazz, jlongArray value, jlong size) {
    jlong* valuec = (*env)->GetLongArrayElements(env, value, JNI_FALSE);
    nbt_tag_t* tag = nbt_new_tag_long_array(valuec, size);

    jclass tagClass = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagLongArray");
    jmethodID constructor = (*env)->GetMethodID(env, tagClass, "<init>", "(JI[J)V");

    if (!constructor) return NULL;

    jvalue args[2];
    args[0].j = (int64_t) tag;
    args[1].i = NBT_TYPE_LONG_ARRAY;
    args[2].l = value;

    return (*env)->NewObjectA(env, tagClass, constructor, args);
}

JNIEXPORT jobject JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1new_1tag_1short_1array(JNIEnv *env, jclass clazz, jshortArray value, jlong size) {
    jshort* valuec = (*env)->GetShortArrayElements(env, value, JNI_FALSE);
    nbt_tag_t* tag = nbt_new_tag_short_array(valuec, size);

    jclass tagClass = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagShortArray");
    jmethodID constructor = (*env)->GetMethodID(env, tagClass, "<init>", "(JI[S)V");

    if (!constructor) return NULL;

    jvalue args[2];
    args[0].j = (int64_t) tag;
    args[1].i = NBT_TYPE_SHORT_ARRAY;
    args[2].l = value;

    return (*env)->NewObjectA(env, tagClass, constructor, args);
}

JNIEXPORT jobject JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1new_1tag_1float_1array(JNIEnv *env, jclass clazz, jfloatArray value, jlong size) {
    jfloat* valuec = (*env)->GetFloatArrayElements(env, value, JNI_FALSE);
    nbt_tag_t* tag = nbt_new_tag_float_array(valuec, size);

    jclass tagClass = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagFloatArray");
    jmethodID constructor = (*env)->GetMethodID(env, tagClass, "<init>", "(JI[F)V");

    if (!constructor) return NULL;

    jvalue args[2];
    args[0].j = (int64_t) tag;
    args[1].i = NBT_TYPE_FLOAT_ARRAY;
    args[2].l = value;

    return (*env)->NewObjectA(env, tagClass, constructor, args);
}

JNIEXPORT jobject JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1new_1tag_1double_1array(JNIEnv *env, jclass clazz, jdoubleArray value, jlong size) {
    jdouble* valuec = (*env)->GetDoubleArrayElements(env, value, JNI_FALSE);
    nbt_tag_t* tag = nbt_new_tag_double_array(valuec, size);

    jclass tagClass = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagDoubleArray");
    jmethodID constructor = (*env)->GetMethodID(env, tagClass, "<init>", "(JI[D)V");

    if (!constructor) return NULL;

    jvalue args[2];
    args[0].j = (int64_t) tag;
    args[1].i = NBT_TYPE_DOUBLE_ARRAY;
    args[2].l = value;

    return (*env)->NewObjectA(env, tagClass, constructor, args);
}

JNIEXPORT jobject JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1new_1tag_1string_1array(JNIEnv *env, jclass clazz, jobjectArray value, jlong size) {
    char** valuec = malloc(size * sizeof(char));
    for(size_t i = 0; i < size; i++) {
        jobject o = (*env)->GetObjectArrayElement(env, value, i);
        *(valuec + i) = (*env)->GetStringUTFChars(env, o, JNI_FALSE);
    }
    nbt_tag_t* tag = nbt_new_tag_string_array(valuec, size);
    free(valuec);

    jclass tagClass = (*env)->FindClass(env, "net/minecraft/server/c/libnbt/NBTTagStringArray");
    jmethodID constructor = (*env)->GetMethodID(env, tagClass, "<init>", "(JI[Ljava/lang/String;)V");

    if (!constructor) return NULL;

    jvalue args[2];
    args[0].j = (int64_t) tag;
    args[1].i = NBT_TYPE_STRING_ARRAY;
    args[2].l = value;

    return (*env)->NewObjectA(env, tagClass, constructor, args);
}


JNIEXPORT void JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1set_1tag_1name(JNIEnv *env, jclass clazz, jobject tag, jstring name) {
    jsize size = (*env)->GetStringUTFLength(env, name);
    Java_net_minecraft_server_c_libnbt_NBT_nbt_1set_1tag_1name0(env, clazz, tag, name, size);
}

JNIEXPORT void JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1set_1tag_1name0(JNIEnv *env, jclass clazz, jobject tag, jstring name, jlong size) {
    jclass tagClass = (*env)->GetObjectClass(env, tag);

    jfieldID nameField = (*env)->GetFieldID(env, tagClass, "name", "Ljava/lang/String;");
    (*env)->SetObjectField(env, tag, nameField, name);

    nbt_tag_t* tagc = get_tag_from_java(env, tag);

    jfieldID nameLenField = (*env)->GetFieldID(env, tagClass, "nameLen", "J");
    (*env)->SetLongField(env, tag, nameLenField, size);

    const char* namec = (*env)->GetStringUTFChars(env, name, JNI_FALSE);
    nbt_set_tag_name0(tagc, namec, size);
    (*env)->ReleaseStringUTFChars(env, name, namec);
}

JNIEXPORT void JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1tag_1list_1append(JNIEnv *env, jclass clazz, jobject list, jobject tag) {
    jclass tagClass = (*env)->GetObjectClass(env, list);
    jfieldID valueField = (*env)->GetFieldID(env, tagClass, "value", "Ljava/util/List;");

    jobject javaList = (*env)->GetObjectField(env, list, valueField);
    jclass listClass = (*env)->GetObjectClass(env, javaList);
    jmethodID addMethod = (*env)->GetMethodID(env, listClass, "add", "(Ljava/lang/Object;)Z");

    jvalue args[1];
    args[0].l = tag;

    if((*env)->CallBooleanMethodA(env, javaList, addMethod, args) == JNI_TRUE) {
        nbt_tag_list_append(get_tag_from_java(env, list), get_tag_from_java(env, tag));
    }
}

JNIEXPORT jobject JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1tag_1list_1get(JNIEnv *env, jclass clazz, jlong list, jlong index) {
    return get_tag_from_c(env, nbt_tag_list_get((nbt_tag_t*) list, index));
}

JNIEXPORT void JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1tag_1compound_1append(JNIEnv *env, jclass clazz, jobject compound, jobject tag) {
    jclass tagClass = (*env)->GetObjectClass(env, compound);
    jfieldID valueField = (*env)->GetFieldID(env, tagClass, "value", "Ljava/util/List;");

    jobject list = (*env)->GetObjectField(env, compound, valueField);
    jclass listClass = (*env)->GetObjectClass(env, list);
    jmethodID addMethod = (*env)->GetMethodID(env, listClass, "add", "(Ljava/lang/Object;)Z");

    jvalue args[1];
    args[0].l = tag;

    if((*env)->CallBooleanMethodA(env, list, addMethod, args) == JNI_TRUE) {
        nbt_tag_compound_append(get_tag_from_java(env, compound), get_tag_from_java(env, tag));
    }
}

JNIEXPORT jobject JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1tag_1compound_1get(JNIEnv *env, jclass clazz, jlong compound, jstring key) {
    const char* keyc = (*env)->GetStringUTFChars(env, key, JNI_FALSE);
    nbt_tag_t* tag = nbt_tag_compound_get((nbt_tag_t*) compound, keyc);
    (*env)->ReleaseStringUTFChars(env, key, keyc);
    return get_tag_from_c(env, tag);
}

JNIEXPORT void JNICALL Java_net_minecraft_server_c_libnbt_NBT_nbt_1free_1tag(JNIEnv *env, jclass clazz, jlong tag) {
    nbt_free_tag((nbt_tag_t*) tag);
}
