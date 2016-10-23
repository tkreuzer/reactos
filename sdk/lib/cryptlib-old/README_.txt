
DER
---
- file: gss_generic_token.c, gssapiP_generic.h,
- taken from: http://www.opensource.apple.com/source/Kerberos/Kerberos-47/KerberosFramework/Kerberos5/Sources/lib/gssapi/generic/
- alternative: ftp://ftp.psc.edu/pub/jwan/Lustre-2.1/2.1.54/CENTOS5/source/lustre-2.1.54_10092012/lustre/ptlrpc/gss/gss_generic_token.c
- alternative: http://lxr.free-electrons.com/source/net/sunrpc/auth_gss/gss_generic_token.c#L160
- Implements: der_length_size, der_write_length, der_read_length, g_token_size, g_make_token_header, g_verify_token_header,


MD4
---
- file: md4.c, md4.h
- taken from http://www.opensource.apple.com/source/freeradius/freeradius-11/freeradius/src/lib/md4.c
- Implements: MD4Init, MD4Update, MD4Final, MD4Transform
md4Finalize -> MD4Final
md4Initialize -> MD4Init
md4InitializeEx -> md4Initialize
md4Sum -> MD4Update

MD5
---
- file: md5.c
- taken from http://code.google.com/p/openjpeg/source/browse/trunk/OPJ_Validate/md5.c?r=547
- Implements: MD5Init, MD5Update, MD5Final
md25Finalize -> MD5Final
md25Finish -> x
md25InitializeEx -> MD5Init, MD5Update, CDLocateCSystem

RC4
---
file: rc4.c, rc4.h
- taken from http://www.opensource.apple.com/source/xnu/xnu-1456.1.26/bsd/crypto/rc4/
- alternative: http://www.zorinaq.com/papers/rc4-amd64.html
- Implements rc4 (rc4_crypt), rc4_key (rc4_init)
rc4Control -> rc4
rc4Decrypt -> rc4
rc4Encrypt -> rc4
rc4Finish -> -
rc4HashPassword -> CDLocateCheckSum
rc4HmacBaseInitialize
rc4HmacBaseInitializeOld
rc4HmacControl
rc4HmacControlOld
rc4HmacDecrypt
rc4HmacDecryptOld
rc4HmacEncrypt
rc4HmacEncryptOld
rc4HmacHashPassword
rc4HmacInitialize
rc4HmacInitializeOld
rc4HmacPlainBaseInitialize
rc4HmacPlainControl
rc4HmacPlainDecrypt
rc4HmacPlainEncrypt
rc4HmacRandomKey
rc4HmacRandomKeyOld
rc4Initialize
rc4LmHashPassword
rc4LmInitialize
rc4Md4HashPassword
rc4Md4Initialize
rc4Md4RandomKey
rc4Plain2Initialize
rc4PlainExpInitialize
rc4PlainExpInitializeOld
rc4PlainInitialize
rc4PlainInitializeOld
rc4RandomKey
rc4_key
rc4_safe -> rc4
rc4_safe_key -> rc4_key
rc4_safe_select -> -
rc4_safe_shutdown -> -
rc4_safe_startup -> -

SHA1
----
- sha1.c, sha1.h
- Taken from: http://source.colloquy.info/svn/trunk/Frameworks/Acid/3rdparty
- Implements: SHA1Transform, SHA1Init, SHA1Update, SHA1Final
A_SHAFinal, A_SHAFinalNS -> wine advapi32
A_SHAInit
A_SHAUpdate, A_SHAUpdateNS
ShaWrapFinalize -> A_SHAFinal
ShaWrapFinish
ShaWrapInitialize -> A_SHAInit
ShaWrapInitializeEx -> A_SHAInit
ShaWrapSum -> A_SHAUpdate

CRC32
-----
- Use Rtl
Crc32
Crc32Finalize
Crc32Initialize
Crc32InitializeEx
Crc32Sum

AES
---
- Taken from: http://enduser.subsignal.org/~trondah/tree/target/linux/generic/files/crypto/ocf/kirkwood/cesa/AES/mvAesAlg.c
- Alternative: http://www.opensource.apple.com/source/Security/Security-28/AppleCSP/AES/

rijndaelDecrypt128
rijndaelEncrypt128
rijndaelKeyEncToDec
rijndaelKeySched
aes128 -> rijndaelDecrypt128 / rijndaelEncrypt128
aeskey -> rijndaelKeySched / rijndaelKeyEncToDec /

DES
---
des
desCbcChecksum
desControl
desCrc32Initialize
desDecrypt
desEncrypt
desFixupKeyParity
desHashBuffer
desHashPassword
desInitialize
desIsWeakKey
desMac1510Finalize
desMac1510InitializeEx2
desMacFinalize
desMacGeneralInitializeEx
desMacInitialize
desMacInitializeEx
desMacKInitializeEx
desMacSum
desMd5Initialize
desPlainInitialize
desRandomKey
deskey
desx
desxkey
tripledes
tripledes3key




FIPS:
----




Wrappers
--------



alternatives:
- http://teal.gmu.edu/courses/Crypto_resources/web_resources/libraries.htm List of libs
- http://www.openssl.org/source/ : all implementations, but ugly

CDLocateCSystem

HMACMD5Final
HMACMD5Init
HMACMD5Update
md5Des1510Finalize -> desEncrypt
md5Des1510Finish -> md5HmacFinish
md5Des1510InitializeEx -> not implemented
md5Des1510InitializeEx2 -> desPlainInitialize, desEncrypt, MD5Init, MD5Update, CDGenerateRandomBits
md5DesFinalize -> MD5Final, desEncrypt
md5DesInitializeEx -> MD5Init, desPlainInitialize
md5DesSum -> MD5Update
md5Finalize -> MD5Final
md5Finish -> -
md5Hmac -> MD5Init, MD5Update, MD5Final
md5Hmac2InitializeEx -> md5Hmac, MD5Init, MD5Update
md5HmacFinalize -> MD5Final, md5Hmac
md5HmacFinish -> -
md5HmacInitializeEx -> MD5Init, MD5Update
md5HmacSum -> MD5Update
md5Initialize -> MD5Init
md5InitializeEx -> md5Initialize
md5Rc4Finalize -> MD5Final, rc4Encrypt
md5Rc4Finish -> rc4Finish
md5Rc4InitializeEx -> MD5Init, rc4Initialize
md5Sum -> MD5Update

