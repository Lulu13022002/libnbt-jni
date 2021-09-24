package net.minecraft.server.c.libnbt;

public class NBTTagLong extends NBTTag {

    public final long value;

    public NBTTagLong(long addr, int type, long value) {
        super(addr, type);
        this.value = value;
    }

    @Override
    public Long getValue() {
        return value;
    }
}
