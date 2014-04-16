#ifndef MITFACTORY_CONTEXT_H
    #define MITFACTORY_CONTEXT_H

    #include <stdio.h>

struct mitfactory_plugin_interface;

struct mitfactory_context
{
    struct mitfactory_plugin_interface* iface;
    size_t                              num_objects;
    void**                              objects;
};

union mitfactory_error
mitfactory_read_file
(
    const char*                 file_name,
    struct mitfactory_context** context
);

union mitfactory_error
mitfactory_read_buffer
(
    const char*                 buffer,
    size_t                      size,
    struct mitfactory_context** context
);

#endif