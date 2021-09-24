package net.minecraft.server.c.libnbt;

public class NBTTagByte extends NBTTag {

    public final byte value;

    public NBTTagByte(long addr, int type, byte value) {
        super(addr, type);
        this.value = value;
    }

    @Override
    public Byte getValue() {
        return value;
    }
}
