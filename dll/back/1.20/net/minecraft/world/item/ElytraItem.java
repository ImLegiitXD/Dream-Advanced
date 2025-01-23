package net.minecraft.world.item;

import net.minecraft.sounds.SoundEvent;
import net.minecraft.sounds.SoundEvents;
import net.minecraft.world.InteractionHand;
import net.minecraft.world.InteractionResultHolder;
import net.minecraft.world.entity.EquipmentSlot;
import net.minecraft.world.entity.player.Player;
import net.minecraft.world.level.Level;
import net.minecraft.world.level.block.DispenserBlock;

public class ElytraItem extends Item implements Equipable {
   public ElytraItem(Item.Properties p_41132_) {
      super(p_41132_);
      DispenserBlock.registerBehavior(this, ArmorItem.DISPENSE_ITEM_BEHAVIOR);
   }

   public static boolean isFlyEnabled(ItemStack p_41141_) {
      return p_41141_.getDamageValue() < p_41141_.getMaxDamage() - 1;
   }

   public boolean isValidRepairItem(ItemStack p_41134_, ItemStack p_41135_) {
      return p_41135_.is(Items.PHANTOM_MEMBRANE);
   }

   public InteractionResultHolder<ItemStack> use(Level p_41137_, Player p_41138_, InteractionHand p_41139_) {
      return this.swapWithEquipmentSlot(this, p_41137_, p_41138_, p_41139_);
   }

   public SoundEvent getEquipSound() {
      return SoundEvents.ARMOR_EQUIP_ELYTRA;
   }

   public EquipmentSlot getEquipmentSlot() {
      return EquipmentSlot.CHEST;
   }
}