#ifndef MITFACTORY_PE_OBJECT_H
    #define MITFACTORY_PE_OBJECT_H

    #include <stdio.h>
    #include <stdbool.h>

    #include <mitfactory/plugins/pe/mitfactory_plugin_pe_error.h>

struct mitfactory_pe_object
{
    const char* buffer;
    size_t      size;
};

bool
mitfactory_pe_object_is_valid_magic
(uint32_t magic);

#endif