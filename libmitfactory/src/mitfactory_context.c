#include <stdlib.h>
#include <stdbool.h>

#include <mitfactory/mitfactory.h>

/* registered plugins */
struct mitfactory_plugin_interface* PLUGINS[] =
{
    &macho_plugin_iface, // macho file format plugin
    NULL                 // termination null entry - DO NOT REMOVE!
};

/* number of registered plugins */
size_t NUM_PLUGINS =
  (sizeof(PLUGINS) / sizeof(struct mitfactory_plugin_interface*));

bool
mitfactory_can_read_buffer
(
    const char* buffer,
    size_t      size
)
{
    /* local function variables */
    bool can_read = false;
    int         i = 0;
    /* ------------------------ */
    
    /* iterate through all available plugins */
    for(i = 0; i < NUM_PLUGINS; i++)
    {
        /* local variables */
        struct mitfactory_plugin_interface* current = NULL;
        /* --------------------------------------------- */
        
        /* retrieve current plugin interface */
        current = PLUGINS[i];
        if(current == NULL)
        {
            /* end of registered plugins reached! */
            break;
        }
        
        if((can_read = current->can_read_buffer(buffer, size)))
        {
            /* plugin compatible with buffer */
            break;
        }
    }
    
    /* everything went fine */
bail:
    return can_read;
}

union mitfactory_error
mitfactory_read_buffer
(
    const char*                 buffer,
    size_t                      size,
    struct mitfactory_context** context
)
{
    /* local function variables */
    enum mitfactory_factory_error   err = MITFACTORY_ERROR_FAILURE;
    struct mitfactory_context* lcontext = NULL;
    int                               i = 0;
    /* --------------------------------------------------------- */
    
    /* check function parameters */
    if(buffer == NULL || size == 0 || context == NULL)
    {
        err = MITFACTORY_ERROR_INVAL_PARAM;
        goto bail;
    }
    
    /* iterate through all available plugins */
    for(i = 0; i < NUM_PLUGINS; i++)
    {
        /* local variables */
        struct mitfactory_plugin_interface* current = NULL;
        /* --------------------------------------------- */
        
        /* retrieve current plugin interface */
        current = PLUGINS[i];
        if(current == NULL)
        {
            /* end of registered plugins reached! */
            break;
        }
        
        /* try to read buffer */
        err = current->read_buffer(buffer, size, &lcontext).factory_error;
        if(err == MITFACTORY_ERROR_SUCCESS)
        {
            /* buffer was compatible - read successful */
            break;
        }
    }
    
    /* check - at least one plugin compatible ? */
    if(err != MITFACTORY_ERROR_SUCCESS)
    {
        /* available plugins are not compatible */
        err = MITFACTORY_ERROR_PLUGINS_NOT_COMP;
        goto bail;
    }

    /* set return parameters */
    *context = lcontext;
    
    /* everything went fine */
    err = MITFACTORY_ERROR_SUCCESS;
bail:
    return (union mitfactory_error)err;
}

union mitfactory_error
mitfactory_read_file
(
    const char*                 file_name,
    struct mitfactory_context** context
)
{
    /* local function variables */
    enum mitfactory_factory_error   err = MITFACTORY_ERROR_FAILURE;
    struct mitfactory_context* lcontext = NULL;
    char*                        buffer = NULL;
    FILE*                   file_handle = NULL;
    long                      file_size = 0;
    /* --------------------------------------------------------- */
    
    /* check function parameters */
    if(file_name == NULL || context == NULL)
    {
        err = MITFACTORY_ERROR_INVAL_PARAM;
        goto bail;
    }
    
    /* open file for reading */
    file_handle = fopen(file_name, "rb");
    if(file_handle == NULL)
    {
        /* unable to open file */
        goto bail;
    }
    
    fseek(file_handle, 0, SEEK_END);
    file_size = ftell(file_handle);
    fseek(file_handle, 0, SEEK_SET);
    
    /* allocate memory for file content */
    buffer = malloc(file_size);
    if(buffer == NULL)
    {
        /* unable to allocate memory */
        goto bail_0;
    }
    
    /* read file content */
    if(fread(buffer, 1, file_size, file_handle) != file_size)
    {
        /* unable to read from file */
        err = (int)MITFACTORY_ERROR_FILE_IO_ERROR;
        goto bail_1;
    }
    
    /* read buffer */
    err = mitfactory_read_buffer(buffer, (size_t)file_size,
      &lcontext).factory_error;
    if(err != MITFACTORY_ERROR_SUCCESS)
    {
        /* unable to read buffer */
        goto bail_1;
    }
    
    /* set return parameters */
    *context = lcontext;
    
    /* everything went fine */
    err = MITFACTORY_ERROR_SUCCESS;
bail_1:
    free(buffer);
bail_0:
    fclose(file_handle);
bail:
    return (union mitfactory_error)err;
}