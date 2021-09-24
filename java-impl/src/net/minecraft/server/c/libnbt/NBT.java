package net.minecraft.server.c.libnbt;

/**
 * <pre>
 * DllImport nbt_tag_t* nbt_parse(nbt_reader_t reader, int parse_flags);
 * DllImport void nbt_write(nbt_writer_t writer, nbt_tag_t* tag, int write_flags);
 *
 * DllImport nbt_tag_t* nbt_new_tag_byte(int8_t value);
 * DllImport nbt_tag_t* nbt_new_tag_short(int16_t value);
 * DllImport nbt_tag_t* nbt_new_tag_int(int32_t value);
 * DllImport nbt_tag_t* nbt_new_tag_long(int64_t value);
 * DllImport nbt_tag_t* nbt_new_tag_float(float value);
 * DllImport nbt_tag_t* nbt_new_tag_double(double value);
 * DllImport nbt_tag_t* nbt_new_tag_byte_array(int8_t* value, size_t size);
 * DllImport nbt_tag_t* nbt_new_tag_string(const char* value);
 * DllImport nbt_tag_t* nbt_new_tag_string0(const char* value, size_t size);
 * DllImport nbt_tag_t* nbt_new_tag_list(nbt_tag_type_t type);
 * DllImport nbt_tag_t* nbt_new_tag_compound(void);
 * DllImport nbt_tag_t* nbt_new_tag_int_array(int32_t* value, size_t size);
 * DllImport nbt_tag_t* nbt_new_tag_long_array(int64_t* value, size_t size);
 * DllImport nbt_tag_t* nbt_new_tag_short_array(int16_t* value, size_t size);
 * DllImport nbt_tag_t* nbt_new_tag_float_array(float* value, size_t size);
 * DllImport nbt_tag_t* nbt_new_tag_double_array(double* value, size_t size);
 * DllImport nbt_tag_t* nbt_new_tag_string_array(char** value, size_t size);
 *
 * DllImport void nbt_set_tag_name(nbt_tag_t* tag, const char* name);
 * DllImport void nbt_set_tag_name0(nbt_tag_t* tag, const char* name, size_t size);
 *
 * DllImport void nbt_tag_list_append(nbt_tag_t* list, nbt_tag_t* value);
 * DllImport nbt_tag_t* nbt_tag_list_get(nbt_tag_t* tag, size_t index);
 * DllImport void nbt_tag_compound_append(nbt_tag_t* compound, nbt_tag_t* value);
 * DllImport nbt_tag_t* nbt_tag_compound_get(nbt_tag_t* tag, const char* key);
 *
 * DllImport void nbt_free_tag(nbt_tag_t* tag);
 * </pre>
 */
public class NBT {
    public static native NBTTag nbt_parse(String path, int parse_flags);
    public static native void nbt_write(String path, long addr, int write_flags);

    public static native NBTTag nbt_new_tag_byte(byte value);
    public static native NBTTag nbt_new_tag_short(short value);
    public static native NBTTag nbt_new_tag_int(int value);
    public static native NBTTag nbt_new_tag_long(long value);
    public static native NBTTag nbt_new_tag_float(float value);
    public static native NBTTag nbt_new_tag_double(double value);
    public static native NBTTag nbt_new_tag_byte_array(byte[] value, long size);
    public static native NBTTag nbt_new_tag_string(String value);
    public static native NBTTag nbt_new_tag_string0(String value, long size);
    public static native NBTTag nbt_new_tag_list(int type);
    public static native NBTTag nbt_new_tag_compound();
    public static native NBTTag nbt_new_tag_int_array(int[] value, long size);
    public static native NBTTag nbt_new_tag_long_array(long[] value, long size);
    public static native NBTTag nbt_new_tag_short_array(short[] value, long size);
    public static native NBTTag nbt_new_tag_float_array(float[] value, long size);
    public static native NBTTag nbt_new_tag_double_array(double[] value, long size);
    public static native NBTTag nbt_new_tag_string_array(String[] value, long size);

    public static native void nbt_set_tag_name(NBTTag tag, String name);
    public static native void nbt_set_tag_name0(NBTTag tag, String name, long size);

    public static native void nbt_tag_list_append(NBTTag list, NBTTag value);
    public static native NBTTag nbt_tag_list_get(long addr, long index);
    public static native void nbt_tag_compound_append(NBTTag compound, NBTTag value);
    public static native NBTTag nbt_tag_compound_get(long addr, String key);

    public static native void nbt_free_tag(long addr);
}
