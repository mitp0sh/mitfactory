#ifndef MITFACTORY_PLUGIN_PE_ERROR_H
    #define MITFACTORY_PLUGIN_PE_ERROR_H

    #define PLUG_PE_ERROR_BASE 0x75930000

enum mitfactory_plugin_pe_error
{
    PLUG_PE_ERROR_SUCCESS        = 0,
    PLUG_PE_ERROR_NO_A_PE_BINARY = 1      | PLUG_PE_ERROR_BASE,
    
    /* non specified failure - end of error codes list */
    PLUG_PE_ERROR_FAILURE        = 0xffff | PLUG_PE_ERROR_BASE
};

#endif