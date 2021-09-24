package net.minecraft.server.c.libnbt;

public class NBTTagShortArray extends NBTTag {

    public final short[] value;

    public NBTTagShortArray(long addr, int type, short[] value) {
        super(addr, type);
        this.value = value;
    }

    @Override
    public short[] getValue() {
        return value;
    }
}
