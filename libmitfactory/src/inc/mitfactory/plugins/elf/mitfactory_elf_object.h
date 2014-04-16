#ifndef MITFACTORY_ELF_OBJECT_H
    #define MITFACTORY_ELF_OBJECT_H

    #include <stdio.h>
    #include <stdbool.h>

    #include <mitfactory/plugins/elf/mitfactory_plugin_elf_error.h>

struct mitfactory_elf_object
{
    const char* buffer;
    size_t      size;
};

bool
mitfactory_elf_object_is_valid_magic
(uint32_t magic);

#endif