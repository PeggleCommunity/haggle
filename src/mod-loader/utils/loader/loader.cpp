#include "loader.hpp"
#include "utils/logger/logger.hpp"

bool has_tls = false;
unsigned long entry_point = 0;

#undef min
#undef max

#pragma comment(linker, "/base:0x400000")
#pragma comment(linker, "/merge:.data=.cld")
#pragma comment(linker, "/merge:.rdata=.clr")
#pragma comment(linker, "/merge:.cl=.main")
#pragma comment(linker, "/merge:.text=.main")
#pragma comment(linker, "/section:.main,re")

#pragma bss_seg(".payload")
//Max we can load without crashing, maybe look into automatic data size
char payload_data[0x70FFFFFF];

#pragma data_seg(".main")
char main_data[0x1000] = { 1 };

#pragma optimize( "", off )
__declspec(thread) char tls_data[0x10000];
#pragma optimize( "", on )

void load_section(const HMODULE target, const HMODULE source, IMAGE_SECTION_HEADER* section)
{
    void* target_ptr = reinterpret_cast<void*>(reinterpret_cast<std::uint32_t>(target) + section->VirtualAddress);
    const void* source_ptr = reinterpret_cast<void*>(reinterpret_cast<std::uint32_t>(source) + section->PointerToRawData);

    if (section->SizeOfRawData > 0)
    {
        const auto size_of_data = std::min(section->SizeOfRawData, section->Misc.VirtualSize);

        DWORD old_protect;
        VirtualProtect(target_ptr, size_of_data, PAGE_EXECUTE_READWRITE, &old_protect);

        std::memmove(target_ptr, source_ptr, size_of_data);
    }

    if (!strcmp((char*)(section->Name), ".tls"))
    {
        has_tls = true;
    }
}

void load_sections(const HMODULE target, const HMODULE source)
{
    const auto dos_header = reinterpret_cast<IMAGE_DOS_HEADER*>(source);
    const auto nt_headers = reinterpret_cast<IMAGE_NT_HEADERS*>(reinterpret_cast<std::uint32_t>(source) + dos_header->e_lfanew);

    auto section = IMAGE_FIRST_SECTION(nt_headers);

    for (auto i = 0u; i < nt_headers->FileHeader.NumberOfSections; ++i, ++section)
    {
        if (section)
        {
            load_section(target, source, section);
        }
    }
}

HMODULE find_library(LPCSTR library)
{
    auto handle = GetModuleHandleA(library);

    if (!handle)
    {
        handle = LoadLibraryA(library);
    }

    return handle;
}

void load_imports(const HMODULE target, const HMODULE source)
{
    const auto dos_header = reinterpret_cast<IMAGE_DOS_HEADER*>(source);
    const auto nt_headers = reinterpret_cast<IMAGE_NT_HEADERS*>(reinterpret_cast<std::uint32_t>(source) + dos_header->e_lfanew);

    const auto import_directory = &nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    auto descriptor = PIMAGE_IMPORT_DESCRIPTOR(reinterpret_cast<std::uint32_t>(target) + import_directory->VirtualAddress);

    while (descriptor->Name)
    {
        std::string library_name = LPSTR(reinterpret_cast<std::uint32_t>(target) + descriptor->Name);

        auto name_table_entry = reinterpret_cast<uintptr_t*>(reinterpret_cast<std::uint32_t>(target) + descriptor->OriginalFirstThunk);
        auto address_table_entry = reinterpret_cast<uintptr_t*>(reinterpret_cast<std::uint32_t>(target) + descriptor->FirstThunk);

        if (!descriptor->OriginalFirstThunk)
        {
            name_table_entry = reinterpret_cast<uintptr_t*>(reinterpret_cast<std::uint32_t>(target) + descriptor->FirstThunk);
        }

        while (*name_table_entry)
        {
            FARPROC function = nullptr;

            if (IMAGE_SNAP_BY_ORDINAL(*name_table_entry))
            {
                auto module = find_library(library_name.data());
                if (module)
                {
                    function = GetProcAddress(module, MAKEINTRESOURCEA(IMAGE_ORDINAL(*name_table_entry)));
                }
            }
            else
            {
                auto import = PIMAGE_IMPORT_BY_NAME(reinterpret_cast<std::uint32_t>(target) + *name_table_entry);

                auto module = find_library(library_name.data());
                if (module)
                {
                    function = GetProcAddress(module, import->Name);
                }
            }

            if (!function)
            {
                throw std::runtime_error("unresolved import!");
            }

            *address_table_entry = reinterpret_cast<uintptr_t>(function);

            name_table_entry++;
            address_table_entry++;
        }

        descriptor++;
    }
}

void verify_tls()
{
    const auto self = GetModuleHandleA(nullptr);
    const auto dos_header = reinterpret_cast<IMAGE_DOS_HEADER*>(self);
    const auto nt_headers = reinterpret_cast<IMAGE_NT_HEADERS*>(reinterpret_cast<std::uint32_t>(self) + dos_header->e_lfanew);

    const auto self_tls = reinterpret_cast<PIMAGE_TLS_DIRECTORY>(reinterpret_cast<std::uint32_t>(self) + nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress);

    const auto ref = std::uintptr_t(&tls_data);
    const auto tls_index = *reinterpret_cast<std::uintptr_t*>(self_tls->AddressOfIndex);

    const auto tls_vector = *reinterpret_cast<std::uintptr_t*>(__readfsdword(0x2C) + 4 * tls_index);

    const auto offset = ref - tls_vector;

    if (offset != 0 && offset != (sizeof(std::uintptr_t) * 2))
    {
        throw std::runtime_error("TLS mapping is wrong!");
    }
}

void loader::load(const char* bin_name)
{
    memset(tls_data, 0, sizeof tls_data);

    std::ifstream bin(bin_name, std::ifstream::binary);

    if (!bin.is_open())
    {
        return;
    }

    bin.seekg(0, bin.end);
    auto binary_size = bin.tellg();
    bin.seekg(0, bin.beg);

    std::vector<std::uint8_t> executable_buffer;
    executable_buffer.resize(binary_size);

    bin.read(reinterpret_cast<char*>(&executable_buffer[0]), binary_size);

    const auto module = GetModuleHandleA(nullptr);
    const auto module_dos_header = reinterpret_cast<IMAGE_DOS_HEADER*>(module);
    const auto module_nt_headers = reinterpret_cast<IMAGE_NT_HEADERS*>(reinterpret_cast<uint32_t>(module) + module_dos_header->e_lfanew);

    const auto source = reinterpret_cast<HMODULE>(&executable_buffer[0]);
    const auto source_dos_header = reinterpret_cast<IMAGE_DOS_HEADER*>(source);
    const auto source_nt_headers = reinterpret_cast<IMAGE_NT_HEADERS*>(reinterpret_cast<uint32_t>(source) + source_dos_header->e_lfanew);

    if (source_nt_headers->FileHeader.Machine == IMAGE_FILE_MACHINE_AMD64)
    {
        MessageBoxA(nullptr, "This binary is x64, this loader only supports x86 binaires!", "Loader", 0);
        exit(0);
    }

    load_sections(module, source);
    load_imports(module, source);

    if (source_nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].Size)
    {
        if (!module_nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress)
        {
            __debugbreak();
        }


        const auto target_tls = reinterpret_cast<PIMAGE_TLS_DIRECTORY>(reinterpret_cast<uint32_t>(module) + module_nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress);
        const auto source_tls = reinterpret_cast<PIMAGE_TLS_DIRECTORY>(reinterpret_cast<uint32_t>(module) + source_nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress);

        const auto source_tls_size = source_tls->EndAddressOfRawData - source_tls->StartAddressOfRawData;
        const auto target_tls_size = target_tls->EndAddressOfRawData - target_tls->StartAddressOfRawData;

        const auto target_tls_index = *reinterpret_cast<DWORD*>(target_tls->AddressOfIndex);
        const auto source_tls_index = *reinterpret_cast<DWORD*>(source_tls->AddressOfIndex);
        *reinterpret_cast<DWORD*>(target_tls->AddressOfIndex) += source_tls_index;

        DWORD old_protect;
        VirtualProtect(PVOID(target_tls->StartAddressOfRawData), source_tls_size, PAGE_READWRITE, &old_protect);

        const auto tls_base = *reinterpret_cast<LPVOID*>(__readfsdword(0x2C) + (sizeof(std::uintptr_t) * source_tls_index) + (sizeof(std::uintptr_t) * target_tls_index));
        std::memmove(tls_base, PVOID(source_tls->StartAddressOfRawData), source_tls_size);
        std::memmove(PVOID(target_tls->StartAddressOfRawData), PVOID(source_tls->StartAddressOfRawData), source_tls_size);
    }

    entry_point = (source_nt_headers->OptionalHeader.ImageBase + source_nt_headers->OptionalHeader.AddressOfEntryPoint);

    DWORD old_protect;
    VirtualProtect(module_nt_headers, 0x1000, PAGE_EXECUTE_READWRITE, &old_protect);

    module_nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT] = source_nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    std::memmove(module_nt_headers, source_nt_headers, sizeof(IMAGE_NT_HEADERS) + (module_nt_headers->FileHeader.NumberOfSections * (sizeof(IMAGE_SECTION_HEADER))));

    if (has_tls)
    {
        verify_tls();
    }
}

template <typename T> inline std::function<T> call(std::uintptr_t callback)
{
	return std::function<T>(reinterpret_cast<T*>(callback));
}

int loader::run(int argc, char* argv[])
{
	return call<int(int, char**)>(entry_point)(argc, argv);
}
