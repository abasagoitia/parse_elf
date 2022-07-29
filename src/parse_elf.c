#include <dev_elf.h>
#include <elf.h>

int32_t args_open_elf(int argc, char **argv)
{
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

    return fd;
}

void print_hex_buf(uint8_t *buf, int length)
{
    int i = 0;
    while (i < length)
        {
            printf("%02x ", buf[i]);
            i++;
        }
        printf("\n");
}

int is_ELF64(Elf64_Ehdr *hdr64)
{
    if (0 != memcmp(hdr64->e_ident, "\x7f" "ELF", ELF_IDENT_LEN))
    {
        printf("Not an elf file got: \n\t");
        print_hex_buf((uint8_t *) hdr64->e_ident, ELF_IDENT_LEN);
     
        return FAILURE;
    }

    return SUCCESS;
}

Elf64_Ehdr *get_elf_header_64(int32_t fd)
{
    if (0 > fd)
    {
        printf("Invalid fd\n");
    }

    // There is only one ELF header
    Elf64_Ehdr *hdr64 = calloc(1, sizeof(Elf64_Ehdr));
    if (NULL == hdr64)
    {
        printf("Unable to alloc memory\n");
        return NULL;
    }

    size_t bytes_read = read(fd, hdr64, sizeof(Elf64_Ehdr));

    off_t offset = 0;

    if (offset != lseek(fd, offset, SEEK_SET))
    {
        printf("Unable to set fp back to start of file\n");
        free(hdr64);
        hdr64 = NULL;
        return NULL;
    }

    if (bytes_read != sizeof(Elf64_Ehdr))
    {
        printf("Unable to read ELF 64 Header\n");
        free(hdr64);
        hdr64 = NULL;

        return NULL;
    }

    return hdr64; 
}

llist_t *get_elf_program_header_table_64(int32_t fd, Elf64_Ehdr *elf_header)
{
    if (0 > fd || NULL == elf_header)
    {
        printf("Invalid Inputs:\n\tfd: %d\n\telf_header: %p\n", fd, elf_header);
        return NULL;
    }
    
    if (0 == elf_header->e_phnum)
    {
        printf("There are not any entries in the program header table\n");
        return NULL;
    }

    llist_t *phdr_list = malloc(sizeof(llist_t));
    if (NULL == phdr_list)
    {
        printf("Cannot make list\n");
        return NULL;
    }

    int offset = elf_header->e_phoff;
    if (offset != lseek(fd, offset, SEEK_SET))
    {
        printf("Cannot seek set\n");
        return NULL;
    }

    for (int i = 0; i < elf_header->e_phnum; i++)
    {
        Elf64_Phdr *phdr = malloc(sizeof(Elf64_Phdr));
        if (NULL == phdr)
        {
            printf("Failed to alloc\n");
            return NULL;
        }

        if (elf_header->e_phentsize != read(fd, phdr, elf_header->e_phentsize))
        {
            printf("Failed read\n");
            return NULL;
        }

        if (FAILURE == llist_add_data(phdr_list, phdr))
        {
            printf("Failed to add phdr to list\n");
            return NULL;
        }

        offset += (i * elf_header->e_phentsize);
        if (offset != lseek(fd, offset, SEEK_SET))
        {
            printf("Cannot seek set\n");
            return NULL;
        }
    }

    return phdr_list;
}

llist_t *get_elf_section_header_table_64(int32_t fd, Elf64_Ehdr *elf_header)
{
    if (0 > fd || NULL == elf_header)
    {
        printf("Invalid Inputs:\n\tfd: %d\n\telf_header: %p\n", fd, elf_header);
        return NULL;
    }
    
    if (0 == elf_header->e_shnum)
    {
        printf("There are not any entries in the program header table\n");
        return NULL;
    }

    llist_t *shdr_list = malloc(sizeof(llist_t));
    if (NULL == shdr_list)
    {
        printf("Cannot make list\n");
        return NULL;
    }

    int offset = elf_header->e_shoff;
    if (offset != lseek(fd, offset, SEEK_SET))
    {
        printf("Cannot seek set\n");
        return NULL;
    }

    for (int i = 0; i < elf_header->e_shnum; i++)
    {
        Elf64_Shdr *shdr = malloc(elf_header->e_shentsize);
        if (NULL == shdr)
        {
            printf("Failed to alloc\n");
            return NULL;
        }

        if (elf_header->e_shentsize != read(fd, shdr, elf_header->e_shentsize))
        {
            printf("Failed read\n");
            return NULL;
        }

        if (FAILURE == llist_add_data(shdr_list, shdr))
        {
            printf("Failed to add shdr to list\n");
            return NULL;
        }

        offset += elf_header->e_shentsize;
        if (offset != lseek(fd, offset, SEEK_SET))
        {
            printf("Cannot seek set\n");
            return NULL;
        }
    }

    return shdr_list;
}

int main(int argc, char **argv)
{
    Elf64_Ehdr *header_64 = NULL;
    llist_t *phdr_list_64 = NULL;
    llist_t* shdr_list_64 = NULL;

    int32_t fd = args_open_elf(argc, argv);
    if (FAILURE == fd)
    {
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
    print_program_header_info_64(header_64);
    print_section_header_info_64(header_64);

    phdr_list_64 = get_elf_program_header_table_64(fd, header_64);
    if (NULL == phdr_list_64)
    {
        printf("Unable to get program header\n");
        return FAILURE;
    }

    shdr_list_64 = get_elf_section_header_table_64(fd, header_64);
    if (NULL == shdr_list_64)
    {
        printf("Unable to get section header\n");
        return FAILURE;
    }
    


exit:
    if (header_64)
    {
        free(header_64);
        header_64 = NULL;
    }
    
    if (phdr_list_64)
    {
        free_llist(phdr_list_64, &free);
        phdr_list_64 = NULL;
    }
    
    if (shdr_list_64)
    {
        free_llist(shdr_list_64, &free);
        shdr_list_64 = NULL;
    }
    return SUCCESS;
}