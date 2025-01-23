package net.minecraft.client.resources.model;

import javax.annotation.Nullable;
import net.minecraft.resources.ResourceLocation;
import net.minecraftforge.api.distmarker.Dist;
import net.minecraftforge.api.distmarker.OnlyIn;

@OnlyIn(Dist.CLIENT)
public interface ModelBaker {
   UnbakedModel getModel(ResourceLocation p_252194_);

   @Nullable
   BakedModel bake(ResourceLocation p_250776_, ModelState p_251280_);
}