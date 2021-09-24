package net.minecraft.server.c.libnbt;

public class NBTTagIntArray extends NBTTag {

    public final int[] value;

    public NBTTagIntArray(long addr, int type, int[] value) {
        super(addr, type);
        this.value = value;
    }

    @Override
    public int[] getValue() {
        return value;
    }
}
