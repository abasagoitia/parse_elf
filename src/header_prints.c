#include <dev_elf.h>

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