#ifndef MITFACTORY_PLUGIN_MACHO_ERROR_H
    #define MITFACTORY_PLUGIN_MACHO_ERROR_H

    #define PLUG_MACHO_ERROR_BASE 0x75920000

enum mitfactory_plugin_macho_error
{
    PLUG_MACHO_ERROR_SUCCESS           = 0,
    PLUG_MACHO_ERROR_NO_A_MACHO_BINARY = 1      | PLUG_MACHO_ERROR_BASE,
    
    /* non specified failure - end of error codes list */
    PLUG_MACHO_ERROR_FAILURE           = 0xffff | PLUG_MACHO_ERROR_BASE
};

#endif