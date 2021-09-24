package net.minecraft.server.c.libnbt;

public class NBTTagByteArray extends NBTTag {

    public final byte[] value;

    public NBTTagByteArray(long addr, int type, byte[] value) {
        super(addr, type);
        this.value = value;
    }

    @Override
    public byte[] getValue() {
        return value;
    }
}
