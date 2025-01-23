package net.minecraft.client;

import com.mojang.authlib.GameProfile;
import com.mojang.util.UUIDTypeAdapter;
import java.util.Arrays;
import java.util.Locale;
import java.util.Map;
import java.util.Optional;
import java.util.UUID;
import java.util.function.Function;
import java.util.stream.Collectors;
import javax.annotation.Nullable;
import net.minecraftforge.api.distmarker.Dist;
import net.minecraftforge.api.distmarker.OnlyIn;

@OnlyIn(Dist.CLIENT)
public class User {
   private final String name;
   private final String uuid;
   private final String accessToken;
   private final Optional<String> xuid;
   private final Optional<String> clientId;
   private final User.Type type;

   public User(String p_193799_, String p_193800_, String p_193801_, Optional<String> p_193802_, Optional<String> p_193803_, User.Type p_193804_) {
      this.name = p_193799_;
      this.uuid = p_193800_;
      this.accessToken = p_193801_;
      this.xuid = p_193802_;
      this.clientId = p_193803_;
      this.type = p_193804_;
   }

   public String getSessionId() {
      return "token:" + this.accessToken + ":" + this.uuid;
   }

   public String getUuid() {
      return this.uuid;
   }

   public String getName() {
      return this.name;
   }

   public String getAccessToken() {
      return this.accessToken;
   }

   public Optional<String> getClientId() {
      return this.clientId;
   }

   public Optional<String> getXuid() {
      return this.xuid;
   }

   @Nullable
   public UUID getProfileId() {
      try {
         return UUIDTypeAdapter.fromString(this.getUuid());
      } catch (IllegalArgumentException illegalargumentexception) {
         return null;
      }
   }

   public GameProfile getGameProfile() {
      return new GameProfile(this.getProfileId(), this.getName());
   }

   public User.Type getType() {
      return this.type;
   }

   @OnlyIn(Dist.CLIENT)
   public static enum Type {
      LEGACY("legacy"),
      MOJANG("mojang"),
      MSA("msa");

      private static final Map<String, User.Type> BY_NAME = Arrays.stream(values()).collect(Collectors.toMap((p_92560_) -> {
         return p_92560_.name;
      }, Function.identity()));
      private final String name;

      private Type(String p_92558_) {
         this.name = p_92558_;
      }

      @Nullable
      public static User.Type byName(String p_92562_) {
         return BY_NAME.get(p_92562_.toLowerCase(Locale.ROOT));
      }

      public String getName() {
         return this.name;
      }
   }
}