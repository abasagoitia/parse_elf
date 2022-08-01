#ifndef DEV_ELF_h
#define DEV_ELF_h

#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stddef.h>

#define FAILURE -1
#define SUCCESS 0

#define ELF_IDENT_LEN 4
#define TEXT_FILE "tests/text_out"
#define TEXT_SECTION ".text"
#define TEXT_SECTION_LEN 6

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

typedef struct llist
{
    node_t *head;
} llist_t;


/**
@brief: Prints the elf header
**/
void print_elf_header_64(Elf64_Ehdr *header);

/**
@brief: Prints the e_ident member of the elf header
**/
void print_e_ident_64(Elf64_Ehdr *header);

/**
@brief: Prints the first bytes of the Elf header (error checking)
**/
void print_e_ident_bytes_64(Elf64_Ehdr *header);

/**
@brief: Prints individual sections of elf header e_ident member
**/
void print_e_shstrndx_64(Elf64_Ehdr *header);
void print_e_shnum_64(Elf64_Ehdr *header);
void print_e_shentsize_64(Elf64_Ehdr *header);
void print_e_phnum_64(Elf64_Ehdr *header);
void print_e_phentsize_64(Elf64_Ehdr *header);
void print_e_ehsize_64(Elf64_Ehdr *header);
void print_e_flags_64(Elf64_Ehdr *header);
void print_e_shoff_64(Elf64_Ehdr *header);
void print_e_phoff_64(Elf64_Ehdr *header);
void print_e_entry_64(Elf64_Ehdr *header);
void print_e_machine_64(Elf64_Ehdr *header);
void print_e_type_64(Elf64_Ehdr *header);

/** 
@brief: prints the individual members of the Elf header
**/
void print_EI_NIDENT_64(Elf64_Ehdr *header);
void print_EI_PAD_64(Elf64_Ehdr *header);
void print_EI_ABIVERSION_64(Elf64_Ehdr *header);
void print_EI_OSABI_64(Elf64_Ehdr *header);
void print_EI_DATA_64(Elf64_Ehdr *header);
void print_EI_CLASS_64(Elf64_Ehdr *header);

/** 
@brief: prints the individual members of a program header
**/
void print_p_type_64(Elf64_Phdr *phdr);
void print_p_offset_64(Elf64_Phdr *phdr);
void print_p_vaddr_64(Elf64_Phdr *phdr);
void print_p_paddr_64(Elf64_Phdr *phdr);
void print_p_filesz_64(Elf64_Phdr *phdr);
void print_p_memsz_64(Elf64_Phdr *phdr);
void print_p_flags_64(Elf64_Phdr *phdr);
void print_p_align_64(Elf64_Phdr *phdr);

/** 
@brief: prints the individual members of a section header
**/
void print_sh_name_64(Elf64_Shdr *shdr, char *shdr_str);
void print_sh_type_64(Elf64_Shdr *shdr);
void print_sh_flags_64(Elf64_Shdr *shdr);
void print_sh_addr_64(Elf64_Shdr *shdr);
void print_sh_offset_64(Elf64_Shdr *shdr);
void print_sh_size_64(Elf64_Shdr *shdr);
void print_sh_link_64(Elf64_Shdr *shdr);
void print_sh_info_64(Elf64_Shdr *shdr);
void print_sh_addralign_64(Elf64_Shdr *shdr);
void print_sh_entsize_64(Elf64_Shdr *shdr);

/**
@brief: Prints the information associated with the program and section headers
from the ELF header
**/
void print_section_header_info_64(Elf64_Ehdr *header);
void print_program_header_info_64(Elf64_Ehdr *header);

/**
@brief: Prints all information associated with each header type
**/
void print_elf_program_header_64(Elf64_Phdr *phdr);
void print_elf_section_header_64(Elf64_Shdr *shdr, char * shdr_str);
void print_elf_all_program_headers_64(llist_t *llist);
void print_elf_all_section_headers_64(llist_t *shdr_list, char *shdr_str);

/**
@brief: Initializes a linked list
@return: llist || NULL
**/
llist_t *llist_create();

/**
@brief: Creates a node containing (data)
@param: data - void pointer to some allocated data
@return: SUCCESS (0) || FAILURE (-1)
**/
node_t *node_create(void *data);

/**
@brief: Adds a node to a linked list
@param: llist - llist_t that may contain a head
@param: node - node_t containing some data
@return: SUCCESS (0) || FAILURE (-1)
**/
int llist_add_node(llist_t *llist, node_t *node);

/**
@brief: Creates a node and adds it to a llist
@param: llist - llist_t that may contain a head
@param: data - void pointer to some allocated data
@return: SUCCESS (0) || FAILURE (-1)
**/
int llist_add_data(llist_t *llist, void *data);

/**
@brief: Free's a llist_t and all nodes
@param: llist - llist_t that may contain a head
@param: free_node_func - function pointer to a free function
@return: SUCCESS (0) || FAILURE (-1)
**/
int free_llist(llist_t *llist, void (*free_node_func)());

/**
@brief: Determines if valid ELF Header
@param: hdr64 - Elf64 header
@return: SUCCESS (0) || FAILURE (-1)
**/
int is_ELF64(Elf64_Ehdr *hdr64);

/**
@brief: Parses ELF header from file
@param: fd - file descriptor of ELF file
@return: ELF64_Ehdr || NULL
**/
Elf64_Ehdr *get_elf_header_64(int32_t fd);

/**
@brief: Parses the ELF program header table and saves those tables
@param: fd - file descriptor of ELF file
@param: elf_header - Elf64_Ehdr of file
@return: llist_t - linked list of nodes containing program headers || NULL
**/
llist_t *get_elf_program_header_table_64(int32_t fd, Elf64_Ehdr *elf_header);

/**
@brief: Parses the ELF section header table and saves those tables
@param: fd - file descriptor of ELF file
@param: elf_header - Elf64_Ehdr of file
@return: llist_t - linked list of nodes containing section headers || NULL
**/
llist_t *get_elf_section_header_table_64(int32_t fd, Elf64_Ehdr *elf_header);

/**
@brief: Parses the ELF section header string
@param: fd - file descriptor of ELF file
@param: shdr_list - llist of section headers
@param: shstrndx - uint16_t index of section header string (Found in Elf64_Ehdr)
@return: char* - section header string
**/
char *get_elf_section_header_str_64(int fd, llist_t *shdr_list, uint16_t shstrndx);

/**
@brief: Parses the ELF .text section string
@param: fd - file descriptor of ELF file
@param: list_shdr - llist of section headers
@param: write_file - if greater than 0 will create file (text_out) containing .text 
@return: char* - section header string
**/
char *get_elf_text_section_64(int fd, char *shdr_str, llist_t *list_shdr, int write_file);

#endif