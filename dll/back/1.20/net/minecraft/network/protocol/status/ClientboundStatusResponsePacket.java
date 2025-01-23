package net.minecraft.network.protocol.status;

import net.minecraft.network.FriendlyByteBuf;
import net.minecraft.network.protocol.Packet;

public record ClientboundStatusResponsePacket(ServerStatus status) implements Packet<ClientStatusPacketListener> {
   public ClientboundStatusResponsePacket(FriendlyByteBuf p_179834_) {
      this(p_179834_.readJsonWithCodec(ServerStatus.CODEC));
   }

   public void write(FriendlyByteBuf p_134899_) {
      p_134899_.writeJsonWithCodec(ServerStatus.CODEC, this.status);
   }

   public void handle(ClientStatusPacketListener p_134896_) {
      p_134896_.handleStatusResponse(this);
   }
}