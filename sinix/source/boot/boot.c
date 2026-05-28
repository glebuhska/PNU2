typedef unsigned long long UTNTN;
typedef unsigned short CHAR16;
typedef void* EFI_HANGLE;
typedef UTNTN EFI_STATUS;

#define EFI_SUCCESS 0

typedef struct boot
{
    UTNTN Revision; 
    EFI_STATUS (*OutputString)(
        void *This,
        CHAR16 *String
    );
    void *InternalContext; 
    EFI_HANGLE DeviceHandle; 
} STOP;

typedef struct {
    char Signature[8];          // 0-7 байты
    unsigned int Revision;      // 8-11
    unsigned int HeaderSize;    // 12-15
    unsigned int CRC32;         // 16-19
    unsigned int Reserved;      // 20-23
    
    // После заголовка идут важные поля
    void *FirmwareVendor;       // 24-31
    unsigned int FirmwareRevision; // 32-35
    void *ConsoleInHandle;      // 40-47
    void *ConIn;                // 48-55
    void *ConsoleOutHandle;     // 56-63
    
    // И только здесь, на 64-м байте (в 64-битной системе), находится ConOut
    STOP *ConOut;               
} EST;

EFI_STATUS efi_main(
    EFI_HANGLE ImageHandle,
    EST *SystemTable
)
{
    SystemTable->ConOut->OutputString(
        SystemTable->ConOut,
        L"Hello"
    );

    while (1)
    {
        
    }

    return EFI_SUCCESS;
    
}
