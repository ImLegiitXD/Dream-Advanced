package net.minecraft.nbt;

import com.google.common.annotations.VisibleForTesting;

public class NbtAccounter {
   public static final NbtAccounter UNLIMITED = new NbtAccounter(0L) {
      public void accountBytes(long p_128927_) {
      }
   };
   private final long quota;
   private long usage;

   public NbtAccounter(long p_128922_) {
      this.quota = p_128922_;
   }

   public void accountBytes(long p_263515_) {
      this.usage += p_263515_;
      if (this.usage > this.quota) {
         throw new RuntimeException("Tried to read NBT tag that was too big; tried to allocate: " + this.usage + "bytes where max allowed: " + this.quota);
      }
   }

   @VisibleForTesting
   public long getUsage() {
      return this.usage;
   }
}