#ifndef MITFACTORY_PLUGIN_MACHO_H
    #define MITFACTORY_PLUGIN_MACHO_H

    #include <stdio.h>
    #include <stdbool.h>

    #include <mitfactory/plugins/macho/mitfactory_plugin_macho_error.h>
    #include <mitfactory/plugins/macho/mitfactory_macho_spec.h>
    #include <mitfactory/plugins/macho/mitfactory_macho_object.h>

struct mitfactory_macho_iface
{
    void* test;
};

struct mitfactory_macho_iface      macho_iface;
struct mitfactory_plugin_interface macho_plugin_iface;

struct mitfactory_macho_context
{
    /* custom macho functions */
    struct mitfactory_plugin_interface* iface;
    
    /* list of macho object in context */
    size_t                              num_objects;
    struct mitfactory_macho_object**    objects;
    
    /* meta information */
    bool                                reversed_byte_order;
};

void*
mitfactory_plugin_macho_release_context
(void);

bool
mitfactory_plugin_macho_can_read_file
(const char* file_name);

bool
mitfactory_plugin_macho_can_read_buffer
(
    const char* buffer,
    size_t      size
);

enum mitfactory_plugin_macho_error
mitfactory_plugin_macho_read_file
(
    const char*                 file_name,
    struct mitfactory_context** context
);

enum mitfactory_plugin_macho_error
mitfactory_plugin_macho_read_buffer
(
    const char*                 buffer,
    size_t                      size,
    struct mitfactory_context** context
);

#endif