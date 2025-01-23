package net.minecraft.world.item;

import net.minecraft.resources.ResourceLocation;

public class HorseArmorItem extends Item {
   private static final String TEX_FOLDER = "textures/entity/horse/";
   private final int protection;
   private final String texture;

   public HorseArmorItem(int p_41364_, String p_41365_, Item.Properties p_41366_) {
      super(p_41366_);
      this.protection = p_41364_;
      this.texture = "textures/entity/horse/armor/horse_armor_" + p_41365_ + ".png";
   }

   public ResourceLocation getTexture() {
      return new ResourceLocation(this.texture);
   }

   public int getProtection() {
      return this.protection;
   }
}