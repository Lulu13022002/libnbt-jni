package net.minecraft.server.c.libnbt;

public class NBTTagLongArray extends NBTTag {

    public final long[] value;

    public NBTTagLongArray(long addr, int type, long[] value) {
        super(addr, type);
        this.value = value;
    }

    @Override
    public long[] getValue() {
        return value;
    }
}
