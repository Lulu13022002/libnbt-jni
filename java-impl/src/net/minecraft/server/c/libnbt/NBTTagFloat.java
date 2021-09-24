package net.minecraft.server.c.libnbt;

public class NBTTagFloat extends NBTTag {

    public final float value;

    public NBTTagFloat(long addr, int type, float value) {
        super(addr, type);
        this.value = value;
    }

    @Override
    public Float getValue() {
        return value;
    }
}
