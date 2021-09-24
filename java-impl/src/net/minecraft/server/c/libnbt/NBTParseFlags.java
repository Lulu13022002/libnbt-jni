package net.minecraft.server.c.libnbt;

public enum NBTParseFlags {
    NBT_PARSE_FLAG_NOTHING, // just like enum starts with one
    NBT_PARSE_FLAG_USE_GZIP,
    NBT_PARSE_FLAG_USE_ZLIB,
    NBT_PARSE_FLAG_USE_RAW,
}
