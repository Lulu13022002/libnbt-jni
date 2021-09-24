package net.minecraft.server.c.libnbt;

public class NBTTagDouble extends NBTTag {

    public final double value;

    public NBTTagDouble(long addr, int type, double value) {
        super(addr, type);
        this.value = value;
    }

    @Override
    public Double getValue() {
        return value;
    }
}
