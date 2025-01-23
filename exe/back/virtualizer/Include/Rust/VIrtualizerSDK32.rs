#[allow(dead_code)]
#[link(name="VirtualizerSDK32", kind="dylib")]
extern {
	#[link_name = "VirtualizerStart"]
    fn VIRTUALIZER_START();

    #[link_name = "VirtualizerEnd"]
    fn VIRTUALIZER_END();

    #[link_name = "VirtualizerStrEncryptStart"]
    fn VIRTUALIZER_STR_ENCRYPT_START();

    #[link_name = "VirtualizerStrEncryptEnd"]
    fn VIRTUALIZER_STR_ENCRYPT_END();

    #[link_name = "VirtualizerStrEncryptWStart"]
    fn VIRTUALIZER_STR_ENCRYPTW_START();

    #[link_name = "VirtualizerStrEncryptWEnd"]
    fn VIRTUALIZER_STR_ENCRYPTW_END();

    #[link_name = "VirtualizerUnprotectedStart"]
    fn VIRTUALIZER_UNPROTECTED_START();

    #[link_name = "VirtualizerUnprotectedEnd"]
    fn VIRTUALIZER_UNPROTECTED_END();
}
