package net.minecraft.server.c.libnbt;

public abstract class NBTTag {

    private String name;
    private final long addr;
    private final NBTTagType type;
    private long nameLen;

    protected NBTTag(long addr, int type) {
        this.addr = addr;
        this.type = NBTTagType.values()[type];
    }

    public long getCAddress() {
        return addr;
    }

    public String getName() {
        return name;
    }

    public NBTTagType getType() {
        return type;
    }

    public long getNameSize() {
        return nameLen;
    }

    public abstract Object getValue();
}
