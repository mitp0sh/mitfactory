#ifndef MITFACTORY_ERROR_H
    #define MITFACTORY_ERROR_H

    #include <mitfactory/plugins/elf/mitfactory_plugin_elf_error.h>
    #include <mitfactory/plugins/macho/mitfactory_plugin_macho_error.h>
    #include <mitfactory/plugins/pe/mitfactory_plugin_pe_error.h>

    #define MITFACTORY_ERROR_BASE 0x75900000

enum mitfactory_factory_error
{
    MITFACTORY_ERROR_SUCCESS          = 0,
    MITFACTORY_ERROR_INVAL_PARAM      = 1      | MITFACTORY_ERROR_BASE,
    MITFACTORY_ERROR_FILE_ERROR       = 2      | MITFACTORY_ERROR_BASE,
    MITFACTORY_ERROR_PLUGINS_NOT_COMP = 3      | MITFACTORY_ERROR_BASE,
    MITFACTORY_ERROR_ALLOC_FAILED     = 4      | MITFACTORY_ERROR_BASE,
    MITFACTORY_ERROR_FILE_IO_ERROR    = 5      | MITFACTORY_ERROR_BASE,
    
    /* non specified failure - end of error codes list */
    MITFACTORY_ERROR_FAILURE          = 0xffff | MITFACTORY_ERROR_BASE
};

union mitfactory_error
{
    enum mitfactory_factory_error      factory_error;
    enum mitfactory_plugin_elf_error   plugin_elf_error;
    enum mitfactory_plugin_macho_error plugin_macho_error;
    enum mitfactory_plugin_pe_error    plugin_pe_error;
};

#endif