#[cfg(target_pointer_width = "32")]
include!("VirtualizerSDK32.rs");

#[cfg(target_pointer_width = "32")]
include!("VirtualizerSDK32_CustomVMs.rs");

#[cfg(target_pointer_width = "64")]
include!("VirtualizerSDK64.rs");

#[cfg(target_pointer_width = "64")]
include!("VirtualizerSDK64_CustomVMs.rs");