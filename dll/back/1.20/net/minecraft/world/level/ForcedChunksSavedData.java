package net.minecraft.world.level;

import it.unimi.dsi.fastutil.longs.LongOpenHashSet;
import it.unimi.dsi.fastutil.longs.LongSet;
import net.minecraft.nbt.CompoundTag;
import net.minecraft.world.level.saveddata.SavedData;

public class ForcedChunksSavedData extends SavedData {
   public static final String FILE_ID = "chunks";
   private static final String TAG_FORCED = "Forced";
   private final LongSet chunks;

   private ForcedChunksSavedData(LongSet p_151482_) {
      this.chunks = p_151482_;
   }

   public ForcedChunksSavedData() {
      this(new LongOpenHashSet());
   }

   public static ForcedChunksSavedData load(CompoundTag p_151484_) {
      return new ForcedChunksSavedData(new LongOpenHashSet(p_151484_.getLongArray("Forced")));
   }

   public CompoundTag save(CompoundTag p_46120_) {
      p_46120_.putLongArray("Forced", this.chunks.toLongArray());
      return p_46120_;
   }

   public LongSet getChunks() {
      return this.chunks;
   }
}