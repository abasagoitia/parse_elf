#include <parse_elf.h>
#include <elf.h>
#include <stdint.h>
#include <unistd.h>

int is_ELF64(Elf64_Ehdr *hdr64)
{
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

llist_t *get_elf_program_header_table_64(int32_t fd, Elf64_Ehdr *elf_header)
{
    if (0 > fd || NULL == elf_header)
    {
        printf("Error:\n\tfd: %d\n\telf_header: %p\n", fd, elf_header);
        return NULL;
    }
    
    if (0 == elf_header->e_phnum)
    {
        printf("Error: There are not any entries in the program header table\n");
        return NULL;
    }

    llist_t *phdr_list = llist_create();
    if (NULL == phdr_list)
    {
        printf("Error: %p\n", phdr_list);
        return NULL;
    }

    int offset = elf_header->e_phoff;
    if (offset != lseek(fd, offset, SEEK_SET))
    {
        printf("Cannot seek set\n");
        free_llist(phdr_list, &free);
        return NULL;
    }

    for (int i = 0; i < elf_header->e_phnum; i++)
    {
        Elf64_Phdr *phdr = malloc(sizeof(Elf64_Phdr));
        if (NULL == phdr)
        {
            printf("Error: phdr: %p\n", phdr);
            free_llist(phdr_list, &free);
            return NULL;
        }

        if (elf_header->e_phentsize != read(fd, phdr, elf_header->e_phentsize))
        {
            printf("Error: Failed read\n");
            free_llist(phdr_list, &free);
            return NULL;
        }

        if (FAILURE == llist_add_data(phdr_list, phdr))
        {
            printf("Error: Failed to add phdr to list\n");
            free_llist(phdr_list, &free);
            return NULL;
        }

        offset += (i * elf_header->e_phentsize);
        if (offset != lseek(fd, offset, SEEK_SET))
        {
            printf("Error: Cannot seek set\n");
            free_llist(phdr_list, &free);
            return NULL;
        }
    }

    return phdr_list;
}

llist_t *get_elf_section_header_table_64(int32_t fd, Elf64_Ehdr *elf_header)
{
    if (0 > fd || NULL == elf_header)
    {
        printf("Error:\n\tfd: %d\n\telf_header: %p\n", fd, elf_header);
        return NULL;
    }
    
    if (0 == elf_header->e_shnum)
    {
        printf("Error: There are not any entries in the program header table\n");
        return NULL;
    }

    llist_t *shdr_list = llist_create();
    if (NULL == shdr_list)
    {
        printf("Error: Cannot make list\n");
        return NULL;
    }

    int offset = elf_header->e_shoff;
    if (offset != lseek(fd, offset, SEEK_SET))
    {
        printf("Cannot seek set\n");
        free_llist(shdr_list, &free);
        return NULL;
    }

    for (int i = 0; i < elf_header->e_shnum; i++)
    {
        Elf64_Shdr *shdr = malloc(elf_header->e_shentsize);
        if (NULL == shdr)
        {
            printf("Error: shdr: %p\n", shdr);
            free_llist(shdr_list, &free);
            return NULL;
        }

        if (elf_header->e_shentsize != read(fd, shdr, elf_header->e_shentsize))
        {
            printf("Error: Failed read\n");
            free_llist(shdr_list, &free);
            return NULL;
        }

        if (FAILURE == llist_add_data(shdr_list, shdr))
        {
            printf("Error: Failed to add shdr to list\n");
            free_llist(shdr_list, &free);
            return NULL;
        }

        offset += elf_header->e_shentsize;
        if (offset != lseek(fd, offset, SEEK_SET))
        {
            printf("Error: Cannot seek set\n");
            free_llist(shdr_list, &free);
            return NULL;
        }
    }

    return shdr_list;
}

char *get_elf_section_header_str_64(int fd, llist_t *shdr_list, uint16_t shstrndx)
{
    if (0 > fd || NULL == shdr_list)
    {
        printf("Error:\n\tfd: %d\n\tshdr: %p\n", fd, shdr_list);
        return NULL;
    }

    int i = 0;
    node_t *node = shdr_list->head;
    while (i < shstrndx && NULL != node)
    {
        node = node->next;
        i++;
    }

    if (i != shstrndx || node == NULL)
    {
        printf("Error: Could not get section\n");
        return NULL;
    }

    Elf64_Shdr *shdr = node->data;
    if (shdr->sh_offset != lseek(fd, shdr->sh_offset, SEEK_SET))
    {
        printf("Error: Failed to seek\n");
        return NULL;
    }

    char *str = calloc(shdr->sh_size, sizeof(char));
    if (NULL == str)
    {
        printf("Error: Failed Alloc\n");
        return NULL;
    }

    if (shdr->sh_size != read(fd, str, shdr->sh_size))
    {
        printf("Error: Failed Read\n");
        free(str);
        str = NULL;
        return NULL;
    }
    return str;
}

char *get_elf_text_section_64(int fd, char *shdr_str, llist_t *list_shdr, int write_file)
{
    if (0 > fd || NULL == shdr_str || NULL == list_shdr || NULL == list_shdr->head)
    {
        printf("Error:\n\tfd: %d\n\tshdr_str: %p\n\t\
                                    list_shdr: %p\n\t\
                                    list_shdr->head: %p\n", 
                                    fd, shdr_str, list_shdr, list_shdr->head);
        return NULL;
    }

    char *text = NULL;
    node_t *node = list_shdr->head;
    Elf64_Shdr *shdr = NULL;

    while(NULL != node)
    {
        shdr = (Elf64_Shdr *) node->data;
        if(0 == strncmp(TEXT_SECTION, (shdr_str + shdr->sh_name), TEXT_SECTION_LEN))
        {
            break;
        }
        node = node->next;
    }

    if (NULL == node)
    {
        printf("Unable to find .text\n");
        return NULL;
    }

    if (shdr->sh_offset != lseek(fd, shdr->sh_offset, SEEK_SET))
    {
        printf("Error: Failed seek\n");
        return NULL;
    }

    text = malloc(shdr->sh_size);
    if (NULL == text)
    {
        printf("Error: text: %p\n", text);
        return NULL;
    }

    if (shdr->sh_size != read(fd, text, shdr->sh_size))
    {
        printf("Error: Failed Read\n");
        free(text);
        text = NULL;
        return NULL;
    }

    if (0 < write_file)
    {
        int out_fd = open(TEXT_FILE, O_WRONLY | O_CREAT);
        if (0 > out_fd)
        {
            printf("Error: Failed to open file\n");
            free(text);
            text = NULL;
            return NULL;
        }

        if (shdr->sh_size != write(out_fd, text, shdr->sh_size))
        {
            printf("Error: Failed to write file\n");
            free(text);
            text = NULL;
            return NULL;
        }
        fsync(out_fd);
    }
    return text;
}


int main(int argc, char **argv)
{
    Elf64_Ehdr *header_64 = NULL;
    llist_t *phdr_list_64 = NULL;
    llist_t* shdr_list_64 = NULL;
    char* text = NULL;

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
    print_program_header_info_64(header_64);
    print_section_header_info_64(header_64);

    phdr_list_64 = get_elf_program_header_table_64(fd, header_64);
    if (NULL == phdr_list_64)
    {
        printf("Unable to get program header\n");
        return FAILURE;
    }

    print_elf_all_program_headers_64(phdr_list_64);

    shdr_list_64 = get_elf_section_header_table_64(fd, header_64);
    if (NULL == shdr_list_64)
    {
        printf("Unable to get section header\n");
        return FAILURE;
    }

    char *shdr_str = get_elf_section_header_str_64(fd, shdr_list_64, header_64->e_shstrndx);
    if (NULL == shdr_str)
    {
        printf("Error: Failed to get shdr_str\n");
        return FAILURE;
    }

    print_elf_all_section_headers_64(shdr_list_64, shdr_str);

    text = get_elf_text_section_64(fd, shdr_str, shdr_list_64, 1);
    


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

    if (text)
    {
        free(text);
        text = NULL;
    }
    return SUCCESS;
}