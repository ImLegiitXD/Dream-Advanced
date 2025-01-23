package net.minecraft.network.protocol.handshake;

import net.minecraft.SharedConstants;
import net.minecraft.network.ConnectionProtocol;
import net.minecraft.network.FriendlyByteBuf;
import net.minecraft.network.protocol.Packet;

public class ClientIntentionPacket implements Packet<ServerHandshakePacketListener> {
   private static final int MAX_HOST_LENGTH = 255;
   private final int protocolVersion;
   private final String hostName;
   private final int port;
   private final ConnectionProtocol intention;

   public ClientIntentionPacket(String p_134726_, int p_134727_, ConnectionProtocol p_134728_) {
      this.protocolVersion = SharedConstants.getCurrentVersion().getProtocolVersion();
      this.hostName = p_134726_;
      this.port = p_134727_;
      this.intention = p_134728_;
   }

   public ClientIntentionPacket(FriendlyByteBuf p_179801_) {
      this.protocolVersion = p_179801_.readVarInt();
      this.hostName = p_179801_.readUtf(255);
      this.port = p_179801_.readUnsignedShort();
      this.intention = ConnectionProtocol.getById(p_179801_.readVarInt());
   }

   public void write(FriendlyByteBuf p_134737_) {
      p_134737_.writeVarInt(this.protocolVersion);
      p_134737_.writeUtf(this.hostName);
      p_134737_.writeShort(this.port);
      p_134737_.writeVarInt(this.intention.getId());
   }

   public void handle(ServerHandshakePacketListener p_134734_) {
      p_134734_.handleIntention(this);
   }

   public ConnectionProtocol getIntention() {
      return this.intention;
   }

   public int getProtocolVersion() {
      return this.protocolVersion;
   }

   public String getHostName() {
      return this.hostName;
   }

   public int getPort() {
      return this.port;
   }
}