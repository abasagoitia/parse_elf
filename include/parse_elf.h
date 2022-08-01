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


#endif