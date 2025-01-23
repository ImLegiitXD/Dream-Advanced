package net.minecraft.client.renderer.entity.layers;

import com.google.common.collect.Maps;
import com.mojang.blaze3d.vertex.PoseStack;
import com.mojang.blaze3d.vertex.VertexConsumer;
import java.util.Map;
import javax.annotation.Nullable;
import net.minecraft.client.model.HumanoidModel;
import net.minecraft.client.renderer.MultiBufferSource;
import net.minecraft.client.renderer.RenderType;
import net.minecraft.client.renderer.Sheets;
import net.minecraft.client.renderer.entity.RenderLayerParent;
import net.minecraft.client.renderer.texture.OverlayTexture;
import net.minecraft.client.renderer.texture.TextureAtlas;
import net.minecraft.client.renderer.texture.TextureAtlasSprite;
import net.minecraft.client.resources.model.ModelManager;
import net.minecraft.resources.ResourceLocation;
import net.minecraft.world.entity.EquipmentSlot;
import net.minecraft.world.entity.LivingEntity;
import net.minecraft.world.item.ArmorItem;
import net.minecraft.world.item.ArmorMaterial;
import net.minecraft.world.item.DyeableArmorItem;
import net.minecraft.world.item.Item;
import net.minecraft.world.item.ItemStack;
import net.minecraft.world.item.armortrim.ArmorTrim;
import net.minecraftforge.api.distmarker.Dist;
import net.minecraftforge.api.distmarker.OnlyIn;

@OnlyIn(Dist.CLIENT)
public class HumanoidArmorLayer<T extends LivingEntity, M extends HumanoidModel<T>, A extends HumanoidModel<T>> extends RenderLayer<T, M> {
   private static final Map<String, ResourceLocation> ARMOR_LOCATION_CACHE = Maps.newHashMap();
   private final A innerModel;
   private final A outerModel;
   private final TextureAtlas armorTrimAtlas;

   public HumanoidArmorLayer(RenderLayerParent<T, M> p_267286_, A p_267110_, A p_267150_, ModelManager p_267238_) {
      super(p_267286_);
      this.innerModel = p_267110_;
      this.outerModel = p_267150_;
      this.armorTrimAtlas = p_267238_.getAtlas(Sheets.ARMOR_TRIMS_SHEET);
   }

   public void render(PoseStack p_117096_, MultiBufferSource p_117097_, int p_117098_, T p_117099_, float p_117100_, float p_117101_, float p_117102_, float p_117103_, float p_117104_, float p_117105_) {
      this.renderArmorPiece(p_117096_, p_117097_, p_117099_, EquipmentSlot.CHEST, p_117098_, this.getArmorModel(EquipmentSlot.CHEST));
      this.renderArmorPiece(p_117096_, p_117097_, p_117099_, EquipmentSlot.LEGS, p_117098_, this.getArmorModel(EquipmentSlot.LEGS));
      this.renderArmorPiece(p_117096_, p_117097_, p_117099_, EquipmentSlot.FEET, p_117098_, this.getArmorModel(EquipmentSlot.FEET));
      this.renderArmorPiece(p_117096_, p_117097_, p_117099_, EquipmentSlot.HEAD, p_117098_, this.getArmorModel(EquipmentSlot.HEAD));
   }

   private void renderArmorPiece(PoseStack p_117119_, MultiBufferSource p_117120_, T p_117121_, EquipmentSlot p_117122_, int p_117123_, A p_117124_) {
      ItemStack itemstack = p_117121_.getItemBySlot(p_117122_);
      Item $$9 = itemstack.getItem();
      if ($$9 instanceof ArmorItem armoritem) {
         if (armoritem.getEquipmentSlot() == p_117122_) {
            this.getParentModel().copyPropertiesTo(p_117124_);
            this.setPartVisibility(p_117124_, p_117122_);
            boolean flag = this.usesInnerModel(p_117122_);
            if (armoritem instanceof DyeableArmorItem) {
               DyeableArmorItem dyeablearmoritem = (DyeableArmorItem)armoritem;
               int i = dyeablearmoritem.getColor(itemstack);
               float f = (float)(i >> 16 & 255) / 255.0F;
               float f1 = (float)(i >> 8 & 255) / 255.0F;
               float f2 = (float)(i & 255) / 255.0F;
               this.renderModel(p_117119_, p_117120_, p_117123_, armoritem, p_117124_, flag, f, f1, f2, (String)null);
               this.renderModel(p_117119_, p_117120_, p_117123_, armoritem, p_117124_, flag, 1.0F, 1.0F, 1.0F, "overlay");
            } else {
               this.renderModel(p_117119_, p_117120_, p_117123_, armoritem, p_117124_, flag, 1.0F, 1.0F, 1.0F, (String)null);
            }

            ArmorTrim.getTrim(p_117121_.level().registryAccess(), itemstack).ifPresent((p_289638_) -> {
               this.renderTrim(armoritem.getMaterial(), p_117119_, p_117120_, p_117123_, p_289638_, p_117124_, flag);
            });
            if (itemstack.hasFoil()) {
               this.renderGlint(p_117119_, p_117120_, p_117123_, p_117124_);
            }

         }
      }
   }

   protected void setPartVisibility(A p_117126_, EquipmentSlot p_117127_) {
      p_117126_.setAllVisible(false);
      switch (p_117127_) {
         case HEAD:
            p_117126_.head.visible = true;
            p_117126_.hat.visible = true;
            break;
         case CHEST:
            p_117126_.body.visible = true;
            p_117126_.rightArm.visible = true;
            p_117126_.leftArm.visible = true;
            break;
         case LEGS:
            p_117126_.body.visible = true;
            p_117126_.rightLeg.visible = true;
            p_117126_.leftLeg.visible = true;
            break;
         case FEET:
            p_117126_.rightLeg.visible = true;
            p_117126_.leftLeg.visible = true;
      }

   }

   private void renderModel(PoseStack p_289664_, MultiBufferSource p_289689_, int p_289681_, ArmorItem p_289650_, A p_289658_, boolean p_289668_, float p_289678_, float p_289674_, float p_289693_, @Nullable String p_289682_) {
      VertexConsumer vertexconsumer = p_289689_.getBuffer(RenderType.armorCutoutNoCull(this.getArmorLocation(p_289650_, p_289668_, p_289682_)));
      p_289658_.renderToBuffer(p_289664_, vertexconsumer, p_289681_, OverlayTexture.NO_OVERLAY, p_289678_, p_289674_, p_289693_, 1.0F);
   }

   private void renderTrim(ArmorMaterial p_289690_, PoseStack p_289687_, MultiBufferSource p_289643_, int p_289683_, ArmorTrim p_289692_, A p_289663_, boolean p_289651_) {
      TextureAtlasSprite textureatlassprite = this.armorTrimAtlas.getSprite(p_289651_ ? p_289692_.innerTexture(p_289690_) : p_289692_.outerTexture(p_289690_));
      VertexConsumer vertexconsumer = textureatlassprite.wrap(p_289643_.getBuffer(Sheets.armorTrimsSheet()));
      p_289663_.renderToBuffer(p_289687_, vertexconsumer, p_289683_, OverlayTexture.NO_OVERLAY, 1.0F, 1.0F, 1.0F, 1.0F);
   }

   private void renderGlint(PoseStack p_289673_, MultiBufferSource p_289654_, int p_289649_, A p_289659_) {
      p_289659_.renderToBuffer(p_289673_, p_289654_.getBuffer(RenderType.armorEntityGlint()), p_289649_, OverlayTexture.NO_OVERLAY, 1.0F, 1.0F, 1.0F, 1.0F);
   }

   private A getArmorModel(EquipmentSlot p_117079_) {
      return (A)(this.usesInnerModel(p_117079_) ? this.innerModel : this.outerModel);
   }

   private boolean usesInnerModel(EquipmentSlot p_117129_) {
      return p_117129_ == EquipmentSlot.LEGS;
   }

   private ResourceLocation getArmorLocation(ArmorItem p_117081_, boolean p_117082_, @Nullable String p_117083_) {
      String s = "textures/models/armor/" + p_117081_.getMaterial().getName() + "_layer_" + (p_117082_ ? 2 : 1) + (p_117083_ == null ? "" : "_" + p_117083_) + ".png";
      return ARMOR_LOCATION_CACHE.computeIfAbsent(s, ResourceLocation::new);
   }
}