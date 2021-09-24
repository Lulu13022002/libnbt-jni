package net.minecraft.server.c.libnbt;

public class NBTTagFloatArray extends NBTTag {

    public final float[] value;

    public NBTTagFloatArray(long addr, int type, float[] value) {
        super(addr, type);
        this.value = value;
    }

    @Override
    public float[] getValue() {
        return value;
    }
}
