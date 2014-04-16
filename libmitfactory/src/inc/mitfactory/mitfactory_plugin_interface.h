#ifndef MITFACTORY_PLUGIN_INTERFACE_H
    #define MITFACTORY_PLUGIN_INTERFACE_H

    #include <stdio.h>
    #include <stdbool.h>

    #include <mitfactory/plugins/elf/mitfactory_plugin_elf.h>
    #include <mitfactory/plugins/macho/mitfactory_plugin_macho.h>
    #include <mitfactory/plugins/pe/mitfactory_plugin_pe.h>

struct mitfactory_context;

typedef
void*
(*mitfactory_plugin_release_context_decl)
(void);

typedef
bool
(*mitfactory_plugin_can_read_file_decl)
(const char* file_name);

typedef
bool
(*mitfactory_plugin_can_read_buffer_decl)
(
    const char*                 buffer,
    size_t                      size
);

typedef
union mitfactory_error
(*mitfactory_plugin_read_file_decl)
(
    const char*                 file_name,
    struct mitfactory_context** context
);

typedef
union mitfactory_error
(*mitfactory_plugin_read_buffer_decl)
(
    const char*                 buffer,
    size_t                      size,
    struct mitfactory_context** context
);

struct mitfactory_plugin_interface
{
    mitfactory_plugin_release_context_decl release_context;
    mitfactory_plugin_can_read_file_decl   can_read_file;
    mitfactory_plugin_can_read_buffer_decl can_read_buffer;
    mitfactory_plugin_read_file_decl       read_file;
    mitfactory_plugin_read_buffer_decl     read_buffer;
    void*                                  format_spec_iface;
};

#endif