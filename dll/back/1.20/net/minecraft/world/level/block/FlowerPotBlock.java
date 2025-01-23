package net.minecraft.world.level.block;

import com.google.common.collect.Maps;
import java.util.Map;
import net.minecraft.core.BlockPos;
import net.minecraft.core.Direction;
import net.minecraft.stats.Stats;
import net.minecraft.world.InteractionHand;
import net.minecraft.world.InteractionResult;
import net.minecraft.world.entity.player.Player;
import net.minecraft.world.item.BlockItem;
import net.minecraft.world.item.Item;
import net.minecraft.world.item.ItemStack;
import net.minecraft.world.level.BlockGetter;
import net.minecraft.world.level.Level;
import net.minecraft.world.level.LevelAccessor;
import net.minecraft.world.level.block.state.BlockBehaviour;
import net.minecraft.world.level.block.state.BlockState;
import net.minecraft.world.level.gameevent.GameEvent;
import net.minecraft.world.level.pathfinder.PathComputationType;
import net.minecraft.world.phys.BlockHitResult;
import net.minecraft.world.phys.shapes.CollisionContext;
import net.minecraft.world.phys.shapes.VoxelShape;

public class FlowerPotBlock extends Block {
   private static final Map<Block, Block> POTTED_BY_CONTENT = Maps.newHashMap();
   public static final float AABB_SIZE = 3.0F;
   protected static final VoxelShape SHAPE = Block.box(5.0D, 0.0D, 5.0D, 11.0D, 6.0D, 11.0D);
   private final Block content;

   public FlowerPotBlock(Block p_53528_, BlockBehaviour.Properties p_53529_) {
      super(p_53529_);
      this.content = p_53528_;
      POTTED_BY_CONTENT.put(p_53528_, this);
   }

   public VoxelShape getShape(BlockState p_53556_, BlockGetter p_53557_, BlockPos p_53558_, CollisionContext p_53559_) {
      return SHAPE;
   }

   public RenderShape getRenderShape(BlockState p_53554_) {
      return RenderShape.MODEL;
   }

   public InteractionResult use(BlockState p_53540_, Level p_53541_, BlockPos p_53542_, Player p_53543_, InteractionHand p_53544_, BlockHitResult p_53545_) {
      ItemStack itemstack = p_53543_.getItemInHand(p_53544_);
      Item item = itemstack.getItem();
      BlockState blockstate = (item instanceof BlockItem ? POTTED_BY_CONTENT.getOrDefault(((BlockItem)item).getBlock(), Blocks.AIR) : Blocks.AIR).defaultBlockState();
      boolean flag = blockstate.is(Blocks.AIR);
      boolean flag1 = this.isEmpty();
      if (flag != flag1) {
         if (flag1) {
            p_53541_.setBlock(p_53542_, blockstate, 3);
            p_53543_.awardStat(Stats.POT_FLOWER);
            if (!p_53543_.getAbilities().instabuild) {
               itemstack.shrink(1);
            }
         } else {
            ItemStack itemstack1 = new ItemStack(this.content);
            if (itemstack.isEmpty()) {
               p_53543_.setItemInHand(p_53544_, itemstack1);
            } else if (!p_53543_.addItem(itemstack1)) {
               p_53543_.drop(itemstack1, false);
            }

            p_53541_.setBlock(p_53542_, Blocks.FLOWER_POT.defaultBlockState(), 3);
         }

         p_53541_.gameEvent(p_53543_, GameEvent.BLOCK_CHANGE, p_53542_);
         return InteractionResult.sidedSuccess(p_53541_.isClientSide);
      } else {
         return InteractionResult.CONSUME;
      }
   }

   public ItemStack getCloneItemStack(BlockGetter p_53531_, BlockPos p_53532_, BlockState p_53533_) {
      return this.isEmpty() ? super.getCloneItemStack(p_53531_, p_53532_, p_53533_) : new ItemStack(this.content);
   }

   private boolean isEmpty() {
      return this.content == Blocks.AIR;
   }

   public BlockState updateShape(BlockState p_53547_, Direction p_53548_, BlockState p_53549_, LevelAccessor p_53550_, BlockPos p_53551_, BlockPos p_53552_) {
      return p_53548_ == Direction.DOWN && !p_53547_.canSurvive(p_53550_, p_53551_) ? Blocks.AIR.defaultBlockState() : super.updateShape(p_53547_, p_53548_, p_53549_, p_53550_, p_53551_, p_53552_);
   }

   public Block getContent() {
      return this.content;
   }

   public boolean isPathfindable(BlockState p_53535_, BlockGetter p_53536_, BlockPos p_53537_, PathComputationType p_53538_) {
      return false;
   }
}