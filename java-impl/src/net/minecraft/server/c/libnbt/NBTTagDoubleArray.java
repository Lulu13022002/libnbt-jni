package net.minecraft.server.c.libnbt;

public class NBTTagDoubleArray extends NBTTag {

    public final double[] value;

    public NBTTagDoubleArray(long addr, int type, double[] value) {
        super(addr, type);
        this.value = value;
    }

    @Override
    public double[] getValue() {
        return value;
    }
}
