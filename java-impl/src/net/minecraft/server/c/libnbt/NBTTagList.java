package net.minecraft.server.c.libnbt;

import java.util.ArrayList;
import java.util.List;

public class NBTTagList extends NBTTag {

    public final List<NBTTag> value = new ArrayList<>();
    private final NBTTagType contentType;

    public NBTTagList(long addr, int type, int contentType) {
        super(addr, type);
        this.contentType = NBTTagType.values()[contentType];
    }

    @Override
    public List<NBTTag> getValue() {
        return value;
    }

    public NBTTagType getContentType() {
        return contentType;
    }
}
