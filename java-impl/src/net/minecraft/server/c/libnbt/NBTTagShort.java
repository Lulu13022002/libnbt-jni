package net.minecraft.server.c.libnbt;

public class NBTTagShort extends NBTTag {

    public final short value;

    public NBTTagShort(long addr, int type, short value) {
        super(addr, type);
        this.value = value;
    }

    @Override
    public Short getValue() {
        return value;
    }
}
