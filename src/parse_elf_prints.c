#include <parse_elf.h>

void print_EI_CLASS_64(Elf64_Ehdr *header)
{
    printf("EI_CLASS:\t");
    switch(header->e_ident[EI_CLASS])
    {
        case ELFCLASSNONE:
            printf("No architecture specified\n");
            break;

        case ELFCLASS32:
            printf("32-bit\n");
            break;

        case ELFCLASS64:
            printf("64-bit\n");
            break;

        default:
            printf("ERROR: Unspecified Class type\n");
            break;
    }
}

void print_EI_DATA_64(Elf64_Ehdr *header)
{
    printf("EI_DATA:\t");
    switch(header->e_ident[EI_DATA])
    {
        case ELFDATANONE:
            printf("Unknown data format.\n");
            break;

        case ELFDATA2LSB:
            printf("Two's complement, little-endian.\n");
            break;

        case ELFDATA2MSB:
            printf("Two's complement, big-endian.\n");
            break;

        default:
            printf("ERROR: Unspecified data type\n");
            break;
    }
}

void print_EI_OSABI_64(Elf64_Ehdr *header)
{
    printf("EI_OSABI:\t");
	switch(header->e_ident[EI_OSABI])
	{
		case ELFOSABI_SYSV:
			printf("UNIX System V ABI\n");
			break;

		case ELFOSABI_HPUX:
			printf("HP-UX\n");
			break;

		case ELFOSABI_NETBSD:
			printf("NetBSD\n");
			break;

		case ELFOSABI_LINUX:
			printf("Linux\n");
			break;

		case ELFOSABI_SOLARIS:
			printf("Sun Solaris\n");
			break;

		case ELFOSABI_AIX:
			printf("IBM AIX\n");
			break;

		case ELFOSABI_IRIX:
			printf("SGI Irix\n");
			break;

		case ELFOSABI_FREEBSD:
			printf("FreeBSD\n");
			break;

		case ELFOSABI_TRU64:
			printf("Compaq TRU64 UNIX\n");
			break;

		case ELFOSABI_MODESTO:
			printf("Novell Modesto\n");
			break;

		case ELFOSABI_OPENBSD:
			printf("OpenBSD\n");
			break;

		case ELFOSABI_ARM_AEABI:
			printf("ARM EABI\n");
			break;

		case ELFOSABI_ARM:
			printf("ARM\n");
			break;

		case ELFOSABI_STANDALONE:
			printf("Standalone (embedded) app\n");
			break;

		default:
			printf("Unknown (0x%x)\n", header->e_ident[EI_OSABI]);
			break;
	}
}

void print_EI_ABIVERSION_64(Elf64_Ehdr *header)
{
    printf("EI_ABIVERSION:\t%02x\n", header->e_ident[EI_ABIVERSION]);
}

void print_EI_PAD_64(Elf64_Ehdr *header)
{
    printf("EI_PADDING:\t%d Bytes of Padding\n", EI_NIDENT-EI_ABIVERSION);
}

void print_EI_NIDENT_64(Elf64_Ehdr *header)
{
    printf("EI_NIDENT:\t%d Bytes\n", EI_NIDENT);
}

void print_e_ident_bytes_64(Elf64_Ehdr *header)
{
    printf("e_ident:\t");
    for (int i = 0; i < EI_NIDENT; i++)
    {
        printf("%02x ", header->e_ident[i]);
    }
    printf("\n");
}

void print_e_ident_64(Elf64_Ehdr *header)
{
    printf("\nheader->e_ident:\n");
    print_e_ident_bytes_64(header);
    print_EI_CLASS_64(header);
    print_EI_DATA_64(header);
    print_EI_OSABI_64(header);
    print_EI_ABIVERSION_64(header);
    print_EI_PAD_64(header);
    print_EI_NIDENT_64(header);
}

void print_e_type_64(Elf64_Ehdr *header)
{
    printf("\nheader->e_type:\t");
    switch(header->e_type)
    {
        case ET_NONE:
			printf("Unknown Type\n");
			break;

		case ET_REL:
			printf("Relocatable\n");
			break;

		case ET_EXEC:
			printf("Executable\n");
			break;

		case ET_DYN:
			printf("Shared Object\n");
			break;
		default:
			printf("Invalid Type\n");
			break;
    }
}

void print_e_version_64(Elf64_Ehdr *header)
{
    printf("header->e_version:\t%d\n", header->e_version);
}

void print_e_machine_64(Elf64_Ehdr *header)
{
    printf("header->e_machine:\t");
    switch(header->e_machine)
	{
		case EM_NONE:
			printf("None (0x0)\n");
			break;

		case EM_386:
			printf("INTEL x86 (0x%x)\n", EM_386);
			break;

		case EM_X86_64:
			printf("AMD x86_64 (0x%x)\n", EM_X86_64);
			break;

		case EM_AARCH64:
			printf("AARCH64 (0x%x)\n", EM_AARCH64);
			break;

		default:
			printf(" 0x%x\n", header->e_machine);
			break;
	}
}

void print_e_entry_64(Elf64_Ehdr *header)
{
    printf("header->e_entry:\t0x%08lx\n", header->e_entry);
}

void print_e_phoff_64(Elf64_Ehdr *header)
{
    printf("header->e_phoff:\t0x%08lx\n", header->e_phoff);
}

void print_e_shoff_64(Elf64_Ehdr *header)
{
    printf("header->e_shoff:\t0x%08lx\n", header->e_shoff);
}

void print_e_flags_64(Elf64_Ehdr *header)
{
    printf("header->e_flags:\t0x%08x\n", header->e_flags);
}

void print_e_ehsize_64(Elf64_Ehdr *header)
{
    printf("header->e_ehsize:\t%d Bytes\n", header->e_ehsize);
}

void print_e_phentsize_64(Elf64_Ehdr *header)
{
    printf("header->e_phentsize:\t%d Bytes\n", header->e_phentsize);
}

void print_e_phnum_64(Elf64_Ehdr *header)
{
    printf("header->e_phnum:\t%d Entries\n", header->e_phnum);
}

void print_e_shentsize_64(Elf64_Ehdr *header)
{
    printf("header->e_shentsize:\t%d Bytes\n", header->e_shentsize);
}

void print_e_shnum_64(Elf64_Ehdr *header)
{
    printf("header->e_shnum:\t%d Entries\n", header->e_shnum);
}

void print_e_shstrndx_64(Elf64_Ehdr *header)
{
    printf("header->e_shstrndx:\t0x%08x\n", header->e_shstrndx);
}

void print_program_header_info_64(Elf64_Ehdr *header)
{
    printf("\nProgram Header Info:\n");
    print_e_phoff_64(header);
    print_e_phentsize_64(header);
    print_e_phnum_64(header);
}

void print_section_header_info_64(Elf64_Ehdr *header)
{
    printf("\nSection Header Info:\n");
    {
        print_e_shoff_64(header);
        print_e_shentsize_64(header);
        print_e_shnum_64(header);
    }
}

void print_p_type_64(Elf64_Phdr *phdr)
{
    printf("phdr->p_type:\t");
    switch (phdr->p_type) {
        case PT_NULL:
            printf("PT_NULL\n");
            break;
        case PT_LOAD:
            printf("PT_LOAD\n");
            break;
        case PT_DYNAMIC:
            printf("PT_DYNAMIC\n");
            break;
        case PT_INTERP:
            printf("PT_INTERP\n");
            break;
        case PT_NOTE:
            printf("PT_NOTE\n");
            break;
        case PT_SHLIB:
            printf("PT_SHLIB\n");
            break;
        case PT_PHDR:
            printf("PT_PHDR\n");
            break;
        case PT_LOPROC:
            printf("PT_LOPROC\n");
            break;
        case PT_HIPROC:
            printf("PT_HIPROC\n");
            break;
        case PT_GNU_STACK:
            printf("PT_GNU_STACK\n");
            break;
        case PT_GNU_EH_FRAME:
            printf("PT_GNU_EH_FRAME\n");
            break;
        case PT_GNU_PROPERTY:
            printf("PT_GNU_PROPERTY\n");
            break;
        case PT_GNU_RELRO:
            printf("PT_GNU_RELRO\n");
            break;
        default:
            printf("Unrecognized type: %08x\n", phdr->p_type);        
    }
}

void print_p_offset_64(Elf64_Phdr *phdr)
{
    printf("phdr->p_offset:\t%08lx\n", phdr->p_offset);
}

void print_p_vaddr_64(Elf64_Phdr *phdr)
{
    printf("phdr->p_vaddr:\t%08lx\n", phdr->p_vaddr);
}

void print_p_paddr_64(Elf64_Phdr *phdr)
{
    printf("phdr->p_paddr:\t%08lx\n", phdr->p_paddr);
}

void print_p_filesz_64(Elf64_Phdr *phdr)
{
    printf("phdr->p_filesz:\t%ld\n", phdr->p_filesz);
}

void print_p_memsz_64(Elf64_Phdr *phdr)
{
    printf("phdr->p_memsz:\t%ld\n", phdr->p_memsz);
}

void print_p_flags_64(Elf64_Phdr *phdr)
{
    printf("phdr->p_flags:\n");
    if (phdr->p_flags & PF_X)
    {
        printf("\tPF_X\n");
    }
    if (phdr->p_flags & PF_W)
    {
        printf("\tPF_W\n");
    }
    if (phdr->p_flags & PF_R)
    {
        printf("\tPF_R\n");
    }
    if (0 == phdr->p_flags)
    {
        printf("\tNo flags set\n");
    }
}

void print_p_align_64(Elf64_Phdr *phdr)
{
    printf("phdr->p_align: %08lx\n", phdr->p_align);
}

void print_elf_program_header_64(Elf64_Phdr *phdr)
{
    printf("\nProgram Header:\n");
    print_p_type_64(phdr);
    print_p_offset_64(phdr);
    print_p_vaddr_64(phdr);
    print_p_paddr_64(phdr);
    print_p_filesz_64(phdr);
    print_p_memsz_64(phdr);
    print_p_flags_64(phdr);
    print_p_align_64(phdr);
}

void print_elf_all_program_headers_64(llist_t *llist)
{
    node_t *node = llist->head;

    while(NULL != node)
    {
        print_elf_program_header_64((Elf64_Phdr *) node->data);
        node = node->next;
    }
}

void print_sh_name_64(Elf64_Shdr *shdr, char *shdr_str)
{
    printf("shdr->name:\t\t%s\n", shdr_str + shdr->sh_name);
}

void print_sh_type_64(Elf64_Shdr *shdr)
{
    printf("shdr->sh_type:\t\t");
    switch (shdr->sh_type) {
        case SHT_NULL:
            printf("SHT_NULL\n");
            break;
        case SHT_PROGBITS:
            printf("SHT_PROGBITS\n");
            break;
        case SHT_SYMTAB:
            printf("SHT_SYMTAB\n");
            break;
        case SHT_STRTAB:
            printf("SHT_STRTAB\n");
            break;
        case SHT_RELA:
            printf("SHT_RELA\n");
            break;
        case SHT_HASH:
            printf("SHT_HASH\n");
            break;
        case SHT_DYNAMIC:
            printf("SHT_DYNAMIC\n");
            break;
        case SHT_NOTE:
            printf("SHT_NOTE\n");
            break;
        case SHT_NOBITS:
            printf("SHT_NOBITS\n");
            break;
        case SHT_REL:
            printf("SHT_REL\n");
            break;
        case SHT_SHLIB:
            printf("SHT_SHLIB\n");
            break;
        case SHT_DYNSYM:
            printf("SHT_DYNSYM\n");
            break;
        case SHT_LOPROC:
            printf("SHT_LOPROC\n");
            break;
        case SHT_HIPROC:
            printf("SHT_HIPROC\n");
            break;
        case SHT_LOUSER:
            printf("SHT_LOUSER\n");
            break;
        case SHT_HIUSER:
            printf("SHT_NULL\n");
            break;
        default:
            printf("\n\tUnrecognized type:\t%d\n", shdr->sh_type);
            break;
    }
}

void print_sh_flags_64(Elf64_Shdr *shdr)
{
    printf("shdr->sh_flags:\n");
    if (shdr->sh_flags & SHF_WRITE)
    {
        printf("\tHF_WRITE\n");
    }
    if (shdr->sh_flags & SHF_ALLOC)
    {
        printf("\tHF_ALLOC\n");
    }
    if (shdr->sh_flags & SHF_EXECINSTR)
    {
        printf("\tHF_EXECINSTR\n");
    }
    if (shdr->sh_flags & SHF_MASKPROC)
    {
        printf("\tHF_MASKPROC\n");
    }
    if (0 == shdr->sh_flags)
    {
        printf("\tNo flags set\n");
    }
}

void print_sh_addr_64(Elf64_Shdr *shdr)
{
    printf("shdr->sh_addr:\t\t%08lx\n", shdr->sh_addr);
}

void print_sh_offset_64(Elf64_Shdr *shdr)
{
    printf("shdr->sh_offset:\t%08lx\n", shdr->sh_offset);
}

void print_sh_size_64(Elf64_Shdr *shdr)
{
    printf("shdr->sh_size:\t\t%ld\n", shdr->sh_size);
}

void print_sh_link_64(Elf64_Shdr *shdr)
{
    printf("shdr->sh_link:\t\t%d\n", shdr->sh_link);
}

void print_sh_info_64(Elf64_Shdr *shdr)
{
    printf("shdr->sh_info:\t\t%08x\n", shdr->sh_info);
}

void print_sh_addralign_64(Elf64_Shdr *shdr)
{
    printf("shdr->sh_addralign:\t%08lx\n", shdr->sh_addralign);
}

void print_sh_entsize_64(Elf64_Shdr *shdr)
{
    printf("shdr->sh_entsize:\t%ld\n", shdr->sh_entsize);
}

void print_elf_section_header_64(Elf64_Shdr *shdr, char * shdr_str)
{
    printf("\nSection Header:\n");
    print_sh_name_64(shdr, shdr_str);
    print_sh_type_64(shdr);
    print_sh_flags_64(shdr);
    print_sh_addr_64(shdr);
    print_sh_offset_64(shdr);
    print_sh_size_64(shdr);
    print_sh_link_64(shdr);
    print_sh_info_64(shdr);
    print_sh_addralign_64(shdr);
    print_sh_entsize_64(shdr);
}

void print_elf_all_section_headers_64(llist_t *shdr_list, char* shdr_str)
{
    node_t *node = shdr_list->head;

    while (NULL != node)
    {
        print_elf_section_header_64((Elf64_Shdr *) node->data, shdr_str);
        node = node->next;
    }
}

void print_elf_header_64(Elf64_Ehdr *header)
{
    printf("\n\nELF Header 64: \n");
    print_e_ident_64(header);
    print_e_type_64(header);
    print_e_version_64(header);
    print_e_machine_64(header);
    print_e_entry_64(header);
    print_e_phoff_64(header);
    print_e_shoff_64(header);
    print_e_flags_64(header);
    print_e_ehsize_64(header);
    print_e_phentsize_64(header);
    print_e_phnum_64(header);
    print_e_shentsize_64(header);
    print_e_shnum_64(header);
    print_e_shstrndx_64(header);
}