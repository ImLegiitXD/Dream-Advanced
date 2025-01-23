package net.minecraft.world.food;

import com.google.common.collect.Lists;
import com.mojang.datafixers.util.Pair;
import java.util.List;
import net.minecraft.world.effect.MobEffectInstance;

public class FoodProperties {
   private final int nutrition;
   private final float saturationModifier;
   private final boolean isMeat;
   private final boolean canAlwaysEat;
   private final boolean fastFood;
   private final List<Pair<MobEffectInstance, Float>> effects;

   FoodProperties(int p_38730_, float p_38731_, boolean p_38732_, boolean p_38733_, boolean p_38734_, List<Pair<MobEffectInstance, Float>> p_38735_) {
      this.nutrition = p_38730_;
      this.saturationModifier = p_38731_;
      this.isMeat = p_38732_;
      this.canAlwaysEat = p_38733_;
      this.fastFood = p_38734_;
      this.effects = p_38735_;
   }

   public int getNutrition() {
      return this.nutrition;
   }

   public float getSaturationModifier() {
      return this.saturationModifier;
   }

   public boolean isMeat() {
      return this.isMeat;
   }

   public boolean canAlwaysEat() {
      return this.canAlwaysEat;
   }

   public boolean isFastFood() {
      return this.fastFood;
   }

   public List<Pair<MobEffectInstance, Float>> getEffects() {
      return this.effects;
   }

   public static class Builder {
      private int nutrition;
      private float saturationModifier;
      private boolean isMeat;
      private boolean canAlwaysEat;
      private boolean fastFood;
      private final List<Pair<MobEffectInstance, Float>> effects = Lists.newArrayList();

      public FoodProperties.Builder nutrition(int p_38761_) {
         this.nutrition = p_38761_;
         return this;
      }

      public FoodProperties.Builder saturationMod(float p_38759_) {
         this.saturationModifier = p_38759_;
         return this;
      }

      public FoodProperties.Builder meat() {
         this.isMeat = true;
         return this;
      }

      public FoodProperties.Builder alwaysEat() {
         this.canAlwaysEat = true;
         return this;
      }

      public FoodProperties.Builder fast() {
         this.fastFood = true;
         return this;
      }

      public FoodProperties.Builder effect(MobEffectInstance p_38763_, float p_38764_) {
         this.effects.add(Pair.of(p_38763_, p_38764_));
         return this;
      }

      public FoodProperties build() {
         return new FoodProperties(this.nutrition, this.saturationModifier, this.isMeat, this.canAlwaysEat, this.fastFood, this.effects);
      }
   }
}