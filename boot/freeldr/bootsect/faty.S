/*
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS Bootsector
 * FILE:            boot/freeldr/bootsect/faty.S
 * PURPOSE:         Combined FAT12, FAT16 and FAT32 boot sector
 * PROGRAMMERS:     Brian Palmer
 *                  Timo Kreuzer
 */

/*
 * Memory layout:
 *
 * 00000000 - 000003FF Real mode interrupt vector table
 * 00000400 - 000004FF BIOS Data Area
 * 00000500 - 00000FFF Free
 * 00001000 - 00004FFF FAT Entry buffer (16 KiB)
 * 00005000 - 00007BDF Bootsector stack
 * 00007BE0 - 00007BFF Bootsector data area
 * 00007C00 - 00007DFF Bootsector code
 * 00007E00 - 0000F7FF Free (ca 30 KiB)
 * 0000F800 - 00087FFF Reserved for FreeLoader code (482 KiB)
 * 00088000 - 0008FFFF Directory buffer (32 KiB)
 * 00090000 - 0009FFFF Possibly free
 * 000A0000 - 000FFFFF Video memory and ROM
 *
 * Layout of a FAT volume:
 *
 * |------------------------------------------------------------|
 * | * BootSector                         |                     |
 * | * FS Information Sector (FAT32 only) |   ReservedSectors   |
 * | * ... more reserved sectors ...      |                     |
 * |------------------------------------------------------------|
 * | * FAT 1                              |    NumberOfFats     |
 * | * FAT 2                              |         *           |
 * | * [more FATs]                        |    SectorsPerFat    |
 * |------------------------------------------------------------|
 * | * Root Directory (FAT12/FAT16 only)  | MaxRootEntries / 16 |
 * |------------------------------------------------------------|
 * | * File data                          |                     |
 * | ....                                 |                     |
 * |------------------------------------------------------------|
 */

/* INCLUDES ******************************************************************/

#include <asm.inc>
#include <freeldr/include/arch/pc/x86common.h>

#define ADDRESS_FOR_FATENTRIES HEX(1000) // 16 KiB
#define ADDRESS_FOR_DIRENTRIES HEX(88000) // 32 KiB

SizeOfDataArea        = 32

/* Put the stack below the data area */
BootSectorStackTop    = (HEX(7c00) - SizeOfDataArea)

/* Data area offsets for uninitialized data */
DataAreaStart         = BootSectorStackTop + 0  /* dword */
BiosCHSDriveSize      = BootSectorStackTop + 8  /* dword */

/* Macro for bp relative memory access to reduce code size */
#define BP_REL(x) ss:[bp + x - BootSectorStackTop]

/* The code starts at 0x7c00 */
// org 7c00h

.code16

/******************************************************************************
 *                      BIOS Parameter Block (BPB)                            *
 ******************************************************************************/
/* We have 3 bytes at the entry point to jump over the data area */
start:
    jmp short main // FIXME: When compiling FAT32, assembler will complain
                   // that the label is too far... Need investigation!
    nop

/* Here starts the BIOS Parameter Block (BPB) data.
   The real data will be copied during install */
OEMName:
    .ascii "FrLdr1.0"
BytesPerSector:
    .word 512
SectorsPerCluster:
    .byte 0
ReservedSectors:
    .word 32
NumberOfFats:
    .byte 2
MaxRootEntries:
    .word 0            // Always zero for FAT32 volumes
TotalSectors:
    .word 0            // Always zero for FAT32 volumes
MediaDescriptor:
    .byte HEX(0f8)
SectorsPerFat:
    .word 0            // Always zero for FAT32 volumes
SectorsPerTrack:
    .word 0
NumberOfHeads:
    .word 0
HiddenSectors:
    .long 0
TotalSectorsBig:
    .long 0

/* Extra data for FAT32 volumes */
#ifdef FAT32
SectorsPerFatBig:
    .long    0
ExtendedFlags:
    .word    0
FSVersion:
    .word    0
RootDirStartCluster:
    .long    0
FSInfoSector:
    .word    0
BackupBootSector:
    .word    6
Reserved1:
    .space 12, 0
#endif // FAT32

BootDrive:
    .byte 0
Reserved:
    .byte 0
ExtendSig:
    .byte HEX(29)
SerialNumber:
    .long 0
VolumeLabel:
    .ascii "NO NAME    "
FileSystem:
#ifdef FAT32
    .ascii "FAT32   "
#else
    .ascii "FAT     "
#endif


/******************************************************************************
 *                           Main code entry                                  *
 * Input: DL = Boot drive                                                     *
 ******************************************************************************/
main:

    /* First setup the segment registers */
    xor ax, ax
    mov ds, ax
    mov ss, ax

    /* Load the stack pointer */
    mov sp, BootSectorStackTop

    /* Load bp for relative memory access, which saves us some bytes of code
       size, when used with 32 bit instructions */
    mov bp, sp

    /* Save the bootdrive in the BPB */
    mov byte ptr ds:[BootDrive], dl

#if 0
/******************************************************************************
 *                        Get drive parameters                                *
 ******************************************************************************/

    /* Call INT 13 to get the drive parameters:
       AH = 08h
       DL = drive (bit 7 set for hard disk)
       ES:DI = 0000h:0000h to guard against BIOS bugs */
    xor di, di
    mov ah, 8
    int HEX(13)

    /* Return from INT 13h/08h:
        CF set on error -> AH = status (07h)
        CF clear if successful -> AH = 00h
        AL = 00h on at least some BIOSes
        BL = drive type (AT/PS2 floppies only)
        CH = low eight bits of maximum cylinder number
        CL = bits 0:5 maximum sector number, bits 7:8 high two bits of maximum cylinder number
        DH = maximum head number
        DL = number of drives
        ES:DI -> drive parameter table (floppies only) */

    /* Check for failure */
    jc BootFailure


/******************************************************************************
 *                         Calculate drive size                               *
 ******************************************************************************/

    movzx ebx, ch           // Put the low 8-bits of the cylinder count into EBX
    mov bh, cl              // Put the high 2-bits in BH
    shr bh, 6               // Shift them into position, now BX contains the cylinder count

    and cl, HEX(3f)         // Mask off cylinder bits from sector count
    movzx ecx, cl           // Move the sectors per track into ECX

    movzx eax, dh           // Move the heads into EAX

    inc eax                 // Make it one based because the bios returns it zero based
    inc ebx                 // Make the cylinder count one based also
    mul ecx                 // Multiply heads with the sectors per track, result in edx:eax
    mul ebx                 // Multiply the cylinders with (heads * sectors) [stored in edx:eax already]

    /* We now have the total number of sectors as reported
       by the bios in eax, so store it in our variable */
    mov dword ptr BP_REL(BiosCHSDriveSize), eax
#endif

/******************************************************************************
 *                 Get root directory / data area start                       *
 ******************************************************************************/

    /* Load the number of first sector of the FAT into ebx */
    movzx ebx, word ptr BP_REL(ReservedSectors)
    add ebx, dword ptr BP_REL(HiddenSectors)

    /* Load sector count into ecx */
#ifdef FAT32
    mov ecx, dword ptr BP_REL(SectorsPerFatBig)
#else
    movzx ecx, word ptr BP_REL(SectorsPerFat)
#endif

    /* Calculate (NumberOfFats * SectorsPerFat) */
    movzx eax, byte ptr BP_REL(NumberOfFats)
    mul ecx

    /* Add reserved sectors and hidden sectors */
    add eax, ebx

#ifdef FAT32
    mov dword ptr BP_REL(DataAreaStart), eax

    /* On FAT32 volumes the root dir start cluster is stored in the BPB */
    mov eax, dword ptr BP_REL(RootDirStartCluster)
#else
    /* Save the starting sector of the root directory */
    //mov dword ptr BP_REL(RootDirStartSector), eax

    /* Calculate number of sectors for the root dir:
       sectors = MaxRootEntries * 32 / 512 (rounded up!) */
    movzx ebx, word ptr BP_REL(MaxRootEntries)
    add ebx, 15
    shr ebx, 4

    /* Add the root dir start sector and save it as DataAreaStart */
    add ebx, eax
    mov dword ptr BP_REL(DataAreaStart), ebx
#endif


/******************************************************************************
 *                 Search the root directory for freeldr                      *
 ******************************************************************************/
.SearchForFreeldr:

    /* Load ES and DI with the segment where we put the dir entries */
    mov di, ADDRESS_FOR_DIRENTRIES / 16
    mov es, di

#ifdef FAT32
    /* Read the dir cluster. This loads the next cluster into EAX */
    call ReadCluster

    /* Calculate the number of dir entries in this cluster:
       dx = SectorsPerCluster * 512 / 32 */
    movzx dx, byte ptr ds:[SectorsPerCluster]
    shl dx, 4
#else
    /* Set the number of sectors to read to 1 */
    xor cx, cx
    inc cx

    /* Read the sector */
    call ReadSectors

    /* Set entry count to entries per sector */
    mov dx, (512 / 32)
#endif

    /* Load the start offset of the dir entries into edi */
    xor di, di

.CheckDirEntry:

    /* If the first byte of the entry is 0 then we have reached the end */
    cmp byte ptr es:[di], ch
    jz BootFailure

    /* Compare with freeldr file name */
    mov si, offset filename
    mov cx, 11
    repe cmpsb

    /* Check if we found the file */
    jz .FoundFreeLoader

    /* File didn't match, go to next entry */
    or di, 31
    inc di

    /* Decrement entry count and check if we reached the end */
    dec dx
    jnz .CheckDirEntry

#ifdef FAT32
    /* Check to see if this was the last cluster in the chain */
    cmp eax, HEX(0ffffff8)
    jnb BootFailure
#endif

    /* Repeat the search process with the next sector / cluster.
       EAX is already adjusted in ReadSectors / ReadCluster */
    jmp .SearchForFreeldr


/******************************************************************************
 *                            Load freeldr                                    *
 ******************************************************************************/
.FoundFreeLoader:

    /* Load the cluster number of freeldr into eax */
#ifdef FAT32
    mov eax, dword ptr es:[di - 11 + HEX(12)]
    mov ax, word ptr es:[di - 11 + HEX(1A)]
#else
    movzx eax, word ptr es:[di - 11 + HEX(1A)]
#endif

    /* Load DI with the freeldr base segment address */
    mov di, FREELDR_BASE / 16

.LoadNextCluster:

    /* Load the cluster to the current address. EAX is adjusted to the next
       cluster and DI is adjusted for the next read */
    call ReadCluster

    /* Check if this is the last cluster in the chain */
#if defined(FAT32)
    cmp eax, HEX(0ffffff8)
#elif defined(FAT12)
    cmp ax, HEX(0ff8)
#else
    cmp ax, HEX(0fff8)
#endif
    jb .LoadNextCluster

    /* Load boot drive into DL, boot partition into DH */
    mov  dl, byte ptr ds:[BootDrive]
    mov  dh, byte ptr ds:[BootPartition]

    /* Now the complete freeldr image is loaded.
       Jump to the realmode entry point. */
    ljmp16 0, FREELDR_BASE



BootFailure:
    mov si, offset msgBootFailure
    jmp short Reboot2

Reboot:
    /* Output "Press any key to reboot" message */
    mov si, offset msgAnyKey

Reboot2:
    call PutChars

    /* Wait for a keypress */
    xor ax, ax
    int HEX(16)

    /* Reboot */
    int HEX(19)


/******************************************************************************
 * PROCEDURE ReadCluster                                                      *
 * Input: EAX = Cluster number, DI = Target segment address                   *
 * Modifies: EAX (next cluster), EBX, ECX, EDX (undefined), DI (adjusted)     *
 ******************************************************************************/
ReadCluster:

    /* Copy the cluster number to EBX */
    mov ebx, eax

    // StartSector = ((Cluster - 2) * SectorsPerCluster) + SectorsForFat + ReservedSectors + HiddenSectors
    // StartSector = ((Cluster - 2) * SectorsPerCluster) + DataAreaStart

    /* Subtract 2 */
    dec eax
    dec eax

    /* Multiply with SectorsPerCluster */
    movzx ecx, byte ptr BP_REL(SectorsPerCluster)
    mul ecx

    /* Add DataAreaStart */
    add eax, dword ptr BP_REL(DataAreaStart)

    /* Read the cluster. EAX = SectorNumber, ECX = SectorsPerCluster */
    call ReadSectors

    /* Adjust DI to point to the next cluster's target segment address */
    shl cx, 5
    add di, cx

/******************************************************************************
 * Read the FAT range for this cluster into the FAT buffer (if required)      *
 ******************************************************************************/

    /* Restore the cluster number in EAX */
    mov eax, ebx

    /* Calculate the index for a 16 KiB range of FAT entries: */
#ifdef FAT32
    /* 16 KiB = 4096 FAT32 entries = 2 ^ 12 FAT32 entries */
    shr eax, 12
#else
    /* 16 KiB = 8192 FAT16 entries = 2 ^ 13 FAT16 entries */
    shr eax, 13
#endif

    /* Check if the requested cluster is already in the FAT buffer.
       Note: this value always fits into 16 bits. */
    cmp ax, word ptr ds:[FirstLoadedFatEntry]
    je .FatIsLoaded

    /* Save the start cluster of the new FAT entry range */
    mov word ptr ds:[FirstLoadedFatEntry], ax

    /* Save registers */
    pushad

    /* Calculate sector offset for the 16 KiB range */
    shl eax, 5

    /* Load the number of the first sector of the FAT into ECX */
    movzx ecx, word ptr BP_REL(ReservedSectors)
    add ecx, dword ptr BP_REL(HiddenSectors)

    /* Calculate the first sector of the FAT entry range in EAX */
    add eax, ecx

    /* Put segment address of the FAT buffer into DI */
    mov di, ADDRESS_FOR_FATENTRIES / 16

    /* Put sector count (for 16 KiB) into ecx */
    mov cx, HEX(4000) / 512

    /* Read the sectors */
    call ReadSectors

    /* Restore registers */
    popad

.FatIsLoaded:

#ifdef FAT32
    /* EBX contains the cluster number, calculate the index into the FAT range */
    and bx, HEX(FFF)
    shl bx, 2

    /* Put the content of the FAT entry into EAX */
    mov eax, dword ptr ds:[ADDRESS_FOR_FATENTRIES + bx]
#else
    /* EBX contains the cluster number, calculate the index into the FAT range */
    and bx, HEX(1FFF)
    add bx, bx

    /* Put the content of the FAT entry into EAX */
    movzx eax, word ptr ds:[ADDRESS_FOR_FATENTRIES + bx]
#endif

    /* Return */
    ret


/******************************************************************************
 * PROCEDURE ReadSectors                                                      *
 * Input: EAX = Sector start number, CX = number of sectors, DI = Target seg  *
 * Modifies: EAX (incremented by sector count)                                *
 *                                                                            *
 ******************************************************************************/
ReadSectors:
    /* We could possibly also implement CHS, but it's currently unimplemented */

ReadSectorsLBA:

    /* Since the LBA calls only support 0x7F sectors at a time,
       we will limit ourselves to 64 */
    cmp cx, 64
    ja BootFailure

    /* Save logical sector number & sector count */
    pushad

    /* Setup the disk address packet on the stack */
    .byte HEX(66) // size overwrite prefix for next push
    push 0    // Put 64-bit logical block address (high part) on stack
    push eax  // Put 64-bit logical block address (low part) on stack
    push di   // Put transfer segment on stack
    push 0    // Put transfer offset on stack
    push cx   // Set transfer count
    push 16   // Set size of packet to 16

    /* Point si to the disk address packet on stack */
    mov si, sp

    /* Set the drive number */
    mov dl, byte ptr ds:[BootDrive]

    /* Call INT 13h, AH = 42h - Extended Read
       Input: ...
       Modifies: ... */
    mov ah, HEX(42)
    int HEX(13)

    /* Check for failure */
    jc BootFailure

    /* Remove disk address packet from stack */
    add sp, 16

    /* Restore sector count & logical sector number */
    popad

    /* Adjust the sector number to the next sector we need to read
       by adding the number of sectors that we read */
    add eax, ecx

    /* return */
    ret



/******************************************************************************
 * PROCEDURE PutChars                                                         *
 * Input: ESI = Points to string to be printed                                *
 * Modifies: AL, AH, SI                                                       *
 ******************************************************************************/
PutChars2:
    mov ah, HEX(0e)
    mov bx, 7
    int HEX(10)
PutChars:
    lodsb
    or al, al
    jnz short PutChars2
    ret


/******************************************************************************
 *                             String data                                    *
 ******************************************************************************/

filename:
    .ascii "FREELDR SYS"

msgBootFailure:
    .ascii "Load failed!", CR, LF

msgAnyKey:
    .ascii "Press key to reboot...", NUL

FirstLoadedFatEntry:
    .word -1

/******************************************************************************
 *               Padding and boot sector signature                            *
 ******************************************************************************/
    /* Pad to 509 bytes */
    .org 509

BootPartition:
    .byte 0

BootSignature:
    .word HEX(0aa55)   // BootSector signature

.endcode16

END
