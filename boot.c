#include "efi.h" // IS A PNU-EFI NOT A GNU, PNU IS NOT GNU PLEASE DON'T BE CONFUSED

#ifndef EFI_FILE_MODE_READ
#define EFI_FILE_MODE_READ 0x0000000000000001ULL
#endif

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"SINIXr\n");
    
    EFI_STATUS Status;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem;
    EFI_GUID FileSystemGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    EFI_FILE_PROTOCOL *RootDir = NULL;
    EFI_FILE_PROTOCOL *KernelFile = NULL;
    Status = SystemTable->BootServices->HandleProtocol(ImageHandle, &FileSystemGuid, (void**)&FileSystem);
    if (EFI_ERROR(Status)) {
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"!non kernel! boot panic\r\n");
        while(1); //panic boot
    } else {
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"kf:)\r\n");
    }
    Status = FileSystem->OpenVolume(FileSystem, &RootDir);
    if (EFI_ERROR(Status)) {
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Error: Cannot open root volume!\r\n");
        while(1);
    }
    Status = RootDir->Open(
        RootDir, 
        &KernelFile, 
        L"kernel.efi", 
        EFI_FILE_MODE_READ, 
        0
    );

    if (EFI_ERROR(Status)) {
       SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Error: kernel.efi not found!\r\n");
       while(1); 
    } else {
       SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Success: kernel.efi found!\r\n");
       //there will be a kernel boot here

    }
    while (1) {
        #if defined(__x86_64__) || defined(__i386__)
        __asm__ __volatile__("hlt");
        #endif
    }

    return Status;
}