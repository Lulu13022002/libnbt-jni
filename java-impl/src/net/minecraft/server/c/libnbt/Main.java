package net.minecraft.server.c.libnbt;

import java.util.Arrays;

public class Main {

    static {
        String ext = "so"; // consider linux as default
        String os = System.getProperty("os.name");
        if (os.startsWith("Win")) ext = "dll";
        else if (os.contains("OS X")) ext = "dylib";

        Runtime.getRuntime().load("[YOUR PATH]\\libnbt-jni\\bin\\Debug\\libnbt-jni." + ext);
    }

    private static void print_nbt_tree(NBTTag tag, int indentation) {
        for (int i = 0; i < indentation; i++) {
            System.out.print(' ');
        }

        if (tag.getName() != null) {
            System.out.printf("%s: ", tag.getName());
        }

        switch (tag.getType()) {
            case NBT_TYPE_BYTE:
                System.out.print(((NBTTagByte) tag).getValue());
                break;
            case NBT_TYPE_SHORT:
                System.out.print(((NBTTagShort) tag).getValue());
                break;
            case NBT_TYPE_INT:
                System.out.print(((NBTTagInt) tag).getValue());
                break;
            case NBT_TYPE_LONG:
                System.out.print(((NBTTagLong) tag).getValue());
                break;
            case NBT_TYPE_FLOAT:
                System.out.print(((NBTTagFloat) tag).getValue());
                break;
            case NBT_TYPE_DOUBLE:
                System.out.print(((NBTTagDouble) tag).getValue());
                break;
            case NBT_TYPE_BYTE_ARRAY:
                System.out.print(Arrays.toString(((NBTTagByteArray) tag).getValue()));
                break;
            case NBT_TYPE_STRING:
                System.out.print(((NBTTagString) tag).getValue());
                break;
            case NBT_TYPE_LIST: {
                System.out.println();
                NBTTagList list = (NBTTagList) tag;
                for (int i = 0, len = list.getValue().size(); i < len; i++) {
                    print_nbt_tree(list.getValue().get(i), (int) (indentation + tag.getNameSize() + 2));
                }
                break;
            }
            case NBT_TYPE_COMPOUND: {
                System.out.println();
                NBTTagCompound compound = (NBTTagCompound) tag;
                for (int i = 0, len = compound.getValue().size(); i < len; i++) {
                    print_nbt_tree(compound.getValue().get(i), (int) (indentation + tag.getNameSize() + 2));
                }
                break;
            }
            case NBT_TYPE_INT_ARRAY:
                System.out.print(Arrays.toString(((NBTTagIntArray) tag).getValue()));
                break;
            case NBT_TYPE_LONG_ARRAY:
                System.out.print(Arrays.toString(((NBTTagLongArray) tag).getValue()));
                break;
            case NBT_TYPE_SHORT_ARRAY:
                System.out.print(Arrays.toString(((NBTTagShortArray) tag).getValue()));
                break;
            case NBT_TYPE_FLOAT_ARRAY:
                System.out.print(Arrays.toString(((NBTTagFloatArray) tag).getValue()));
                break;
            case NBT_TYPE_DOUBLE_ARRAY:
                System.out.print(Arrays.toString(((NBTTagDoubleArray) tag).getValue()));
                break;
            case NBT_TYPE_STRING_ARRAY:
                System.out.print(Arrays.toString(((NBTTagStringArray) tag).getValue()));
                break;
            default:
                System.out.print("error");
                break;
        }

        System.out.println();
    }

    public static void main(String[] args) {

        NBTTag tag = NBT.nbt_new_tag_compound();
        NBT.nbt_set_tag_name(tag, "MySuperName");

        NBTTag version = NBT.nbt_new_tag_int(5);
        NBT.nbt_set_tag_name(version, "Version");

        NBT.nbt_tag_compound_append(tag, version);
        NBT.nbt_write("test_gzip.nbt", tag.getCAddress(), NBTWriteFlags.NBT_WRITE_FLAG_USE_GZIP.ordinal());
        NBT.nbt_free_tag(tag.getCAddress());

        NBTTag tag2 = NBT.nbt_parse("bigtest_gzip.nbt", NBTParseFlags.NBT_PARSE_FLAG_USE_GZIP.ordinal());
        print_nbt_tree(tag2, 2);
        System.out.println("D");
        NBT.nbt_free_tag(tag2.getCAddress());
        System.out.println("D");

        /*NBTTag tag = NBT.nbt_new_tag_compound();

        NBT.nbt_set_tag_name(tag, "ChunkX");

        NBTTag data = NBT.nbt_new_tag_byte((byte) 5);
        NBT.nbt_set_tag_name(data, "ChunkX2");

        NBT.nbt_tag_compound_append(tag, data);
        System.out.println(tag.getName());
        System.out.println(tag.getNameSize());
        System.out.println(tag.getType());
        System.out.println(((NBTTagByte)((NBTTagCompound) tag).getValue().get(0)).getValue());
        System.out.println(data.getName());

        NBT.nbt_free_tag(tag.getCAddress());*/
    }
}
