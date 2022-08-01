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

void print_elf_header_64(Elf64_Ehdr *header);
void print_section_header_info_64(Elf64_Ehdr *header);
void print_program_header_info_64(Elf64_Ehdr *header);
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
void print_e_ident_64(Elf64_Ehdr *header);
void print_e_ident_bytes_64(Elf64_Ehdr *header);
void print_EI_NIDENT_64(Elf64_Ehdr *header);
void print_EI_PAD_64(Elf64_Ehdr *header);
void print_EI_ABIVERSION_64(Elf64_Ehdr *header);
void print_EI_OSABI_64(Elf64_Ehdr *header);
void print_EI_DATA_64(Elf64_Ehdr *header);
void print_EI_CLASS_64(Elf64_Ehdr *header);

void print_elf_program_header_64(Elf64_Phdr *phdr);
void print_elf_all_program_headers_64(llist_t *llist);
void print_elf_all_section_headers_64(llist_t *shdr_list, char *shdr_str);

llist_t *llist_create();
node_t *node_create(void *data);
int llist_add_node(llist_t *llist, node_t *node);
int llist_add_data(llist_t *llist, void *data);
int free_llist(llist_t *llist, void (*free_node_func)());

#endif