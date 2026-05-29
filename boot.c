#include "efi.h"

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"SINIXr\n");
    EFI_STATUS Status;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem;
    EFI_GUID FileSystemGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    Status = SystemTable->BootServices->HandleProtocol(ImageHandle, &FileSystemGuid, (void**)&FileSystem);
    if (EFI_ERROR(Status)) {
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"!non kernel! boot panic\r\n");
    } else {
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"kf:)\r\n");
    }
    while(1);

    return Status;
}