package net.minecraft.server.c.libnbt;

public class NBTTagStringArray extends NBTTag {

    public final String[] value;

    public NBTTagStringArray(long addr, int type, String[] value) {
        super(addr, type);
        this.value = value;
    }

    @Override
    public String[] getValue() {
        return value;
    }
}
