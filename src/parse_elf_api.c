#include <parse_elf.h>
#include <elf.h>
#include <stdint.h>
#include <unistd.h>

int is_ELF64(Elf64_Ehdr *hdr64)
{
    // Check if the first 4 bytes match the ELF magic bytes
    if (0 != memcmp(hdr64->e_ident, "\x7f" "ELF", ELF_IDENT_LEN))
    {
        printf("Not an elf file got: \n\t");
        
        int i = 0;
            while (i < ELF_IDENT_LEN)
            {
                printf("%02x ", hdr64->e_ident[i]);
                i++;
            }
        printf("\n");
     
        return FAILURE;
    }

    return SUCCESS;
}

Elf64_Ehdr *get_elf_header_64(int32_t fd)
{
    if (0 > fd)
    {
        printf("Error: fd: %d\n", fd);
    }

    // There is only one ELF header
    Elf64_Ehdr *hdr64 = calloc(1, sizeof(Elf64_Ehdr));
    if (NULL == hdr64)
    {
        printf("Error: hdr64: %p\n", hdr64);
        return NULL;
    }

    if (sizeof(Elf64_Ehdr) != read(fd, hdr64, sizeof(Elf64_Ehdr)))
    {
        printf("Error: Unable to read ELF 64 Header\n");
        free(hdr64);
        hdr64 = NULL;
        return NULL;
    }

    return hdr64; 
}

int main(int argc, char **argv)
{
    Elf64_Ehdr *header_64 = NULL;

    if (2 != argc)
    {
        printf("Usage: ./%s <elf_file_path>\n", argv[0]);
        return FAILURE;
    }

    int32_t fd = open(argv[1], O_RDONLY);  
    if (0 > fd)
    {
        printf("Unable to open: <%s>\n", argv[1]);
        return FAILURE;
    }

    header_64 = get_elf_header_64(fd);
    
    if (FAILURE == is_ELF64(header_64))
    {
        printf("This ELF is not valid\n");
        goto exit;
    }
    
    printf("This is a valid ELF\n");
    print_elf_header_64(header_64);   


exit:
    if (header_64)
    {
        free(header_64);
        header_64 = NULL;
    }

    return SUCCESS;
}