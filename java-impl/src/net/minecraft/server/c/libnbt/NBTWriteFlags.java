package net.minecraft.server.c.libnbt;

public enum NBTWriteFlags {
  NBT_WRITE_FLAG_NOTHING, // just like enum starts with one
  NBT_WRITE_FLAG_USE_GZIP,
  NBT_WRITE_FLAG_USE_ZLIB,
  NBT_WRITE_FLAG_USE_RAW;
}
