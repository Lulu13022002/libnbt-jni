package net.minecraft.server.c.libnbt;

import java.util.ArrayList;
import java.util.List;

public class NBTTagCompound extends NBTTag {

    public final List<NBTTag> value = new ArrayList<>();

    public NBTTagCompound(long addr, int type) {
        super(addr, type);
    }

    @Override
    public List<NBTTag> getValue() {
        return value;
    }
}
