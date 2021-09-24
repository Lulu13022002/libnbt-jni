package net.minecraft.server.c.libnbt;

public class NBTTagInt extends NBTTag {

    public final int value;

    public NBTTagInt(long addr, int type, int value) {
        super(addr, type);
        this.value = value;
    }

    @Override
    public Integer getValue() {
        return value;
    }
}
