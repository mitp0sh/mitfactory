#ifndef MITFACTORY_MACHO_OBJECT_H
    #define MITFACTORY_MACHO_OBJECT_H

    #include <stdio.h>
    #include <stdbool.h>

    #include <mitfactory/plugins/macho/mitfactory_plugin_macho_error.h>

struct mitfactory_macho_object
{
    const char* buffer;
    size_t      size;
};

bool
mitfactory_macho_object_is_valid_magic
(uint32_t magic);

#endif
