#ifndef __UNIATA_SATA__H__
#define __UNIATA_SATA__H__

UCHAR
NTAPI
UniataSataConnect(
    IN PVOID HwDeviceExtension,
    IN ULONG lChannel          // logical channel
    );

UCHAR
NTAPI
UniataSataPhyEnable(
    IN PVOID HwDeviceExtension,
    IN ULONG lChannel          // logical channel
    );

#define UNIATA_SATA_DO_CONNECT        TRUE
#define UNIATA_SATA_IGNORE_CONNECT    FALSE

BOOLEAN
NTAPI
UniataSataClearErr(
    IN PVOID HwDeviceExtension,
    IN ULONG lChannel,          // logical channel
    IN BOOLEAN do_connect
    );

#define UNIATA_SATA_EVENT_ATTACH      0x01
#define UNIATA_SATA_EVENT_DETACH      0x02

BOOLEAN
NTAPI
UniataSataEvent(
    IN PVOID HwDeviceExtension,
    IN ULONG lChannel,          // logical channel
    IN ULONG Action
    );

#define UniataIsSATARangeAvailable(deviceExtension, lChannel) \
    ((deviceExtension->BaseIoAddressSATA_0.Addr || \
      deviceExtension->BaseIoAHCI_0.Addr) && \
        (deviceExtension->chan[lChannel].RegTranslation[IDX_SATA_SStatus].Addr))

BOOLEAN
NTAPI
UniataAhciInit(
    IN PVOID HwDeviceExtension
    );

UCHAR
NTAPI
UniataAhciStatus(
    IN PVOID HwDeviceExtension,
    IN ULONG lChannel
    );

ULONG
NTAPI
UniataAhciSetupFIS(
    IN PHW_DEVICE_EXTENSION deviceExtension,
    IN ULONG DeviceNumber,
    IN ULONG lChannel,
   OUT PUCHAR fis,
    IN UCHAR command,
    IN ULONGLONG lba,
    IN USHORT count,
    IN USHORT feature,
    IN ULONG flags
    );

#endif //__UNIATA_SATA__H__