#ifndef MITFACTORY_PLUGIN_ELF_ERROR_H
    #define MITFACTORY_PLUGIN_ELF_ERROR_H

    #define PLUG_ELF_ERROR_BASE 0x75910000

enum mitfactory_plugin_elf_error
{
    PLUG_ELF_ERROR_SUCCESS         = 0,
    PLUG_ELF_ERROR_NO_A_ELF_BINARY = 1      | PLUG_ELF_ERROR_BASE,
    
    /* non specified failure - end of error codes list */
    PLUG_ELF_ERROR_FAILURE         = 0xffff | PLUG_ELF_ERROR_BASE
};

#endif