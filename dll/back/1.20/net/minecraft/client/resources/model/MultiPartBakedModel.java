package net.minecraft.client.resources.model;

import com.google.common.collect.Lists;
import it.unimi.dsi.fastutil.objects.Object2ObjectOpenCustomHashMap;
import java.util.BitSet;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.function.Predicate;
import javax.annotation.Nullable;
import net.minecraft.Util;
import net.minecraft.client.renderer.block.model.BakedQuad;
import net.minecraft.client.renderer.block.model.ItemOverrides;
import net.minecraft.client.renderer.block.model.ItemTransforms;
import net.minecraft.client.renderer.texture.TextureAtlasSprite;
import net.minecraft.core.Direction;
import net.minecraft.util.RandomSource;
import net.minecraft.world.level.block.state.BlockState;
import net.minecraftforge.api.distmarker.Dist;
import net.minecraftforge.api.distmarker.OnlyIn;
import org.apache.commons.lang3.tuple.Pair;

@OnlyIn(Dist.CLIENT)
public class MultiPartBakedModel implements BakedModel {
   private final List<Pair<Predicate<BlockState>, BakedModel>> selectors;
   protected final boolean hasAmbientOcclusion;
   protected final boolean isGui3d;
   protected final boolean usesBlockLight;
   protected final TextureAtlasSprite particleIcon;
   protected final ItemTransforms transforms;
   protected final ItemOverrides overrides;
   private final Map<BlockState, BitSet> selectorCache = new Object2ObjectOpenCustomHashMap<>(Util.identityStrategy());

   public MultiPartBakedModel(List<Pair<Predicate<BlockState>, BakedModel>> p_119462_) {
      this.selectors = p_119462_;
      BakedModel bakedmodel = p_119462_.iterator().next().getRight();
      this.hasAmbientOcclusion = bakedmodel.useAmbientOcclusion();
      this.isGui3d = bakedmodel.isGui3d();
      this.usesBlockLight = bakedmodel.usesBlockLight();
      this.particleIcon = bakedmodel.getParticleIcon();
      this.transforms = bakedmodel.getTransforms();
      this.overrides = bakedmodel.getOverrides();
   }

   public List<BakedQuad> getQuads(@Nullable BlockState p_235050_, @Nullable Direction p_235051_, RandomSource p_235052_) {
      if (p_235050_ == null) {
         return Collections.emptyList();
      } else {
         BitSet bitset = this.selectorCache.get(p_235050_);
         if (bitset == null) {
            bitset = new BitSet();

            for(int i = 0; i < this.selectors.size(); ++i) {
               Pair<Predicate<BlockState>, BakedModel> pair = this.selectors.get(i);
               if (pair.getLeft().test(p_235050_)) {
                  bitset.set(i);
               }
            }

            this.selectorCache.put(p_235050_, bitset);
         }

         List<BakedQuad> list = Lists.newArrayList();
         long k = p_235052_.nextLong();

         for(int j = 0; j < bitset.length(); ++j) {
            if (bitset.get(j)) {
               list.addAll(this.selectors.get(j).getRight().getQuads(p_235050_, p_235051_, RandomSource.create(k)));
            }
         }

         return list;
      }
   }

   public boolean useAmbientOcclusion() {
      return this.hasAmbientOcclusion;
   }

   public boolean isGui3d() {
      return this.isGui3d;
   }

   public boolean usesBlockLight() {
      return this.usesBlockLight;
   }

   public boolean isCustomRenderer() {
      return false;
   }

   public TextureAtlasSprite getParticleIcon() {
      return this.particleIcon;
   }

   public ItemTransforms getTransforms() {
      return this.transforms;
   }

   public ItemOverrides getOverrides() {
      return this.overrides;
   }

   @OnlyIn(Dist.CLIENT)
   public static class Builder {
      private final List<Pair<Predicate<BlockState>, BakedModel>> selectors = Lists.newArrayList();

      public void add(Predicate<BlockState> p_119478_, BakedModel p_119479_) {
         this.selectors.add(Pair.of(p_119478_, p_119479_));
      }

      public BakedModel build() {
         return new MultiPartBakedModel(this.selectors);
      }
   }
}