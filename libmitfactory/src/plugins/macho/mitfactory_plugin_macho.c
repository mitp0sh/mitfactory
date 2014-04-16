#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <mitfactory/mitfactory.h>

struct mitfactory_macho_iface macho_iface =
{
    NULL
};

struct mitfactory_plugin_interface macho_plugin_iface =
{
    /* plugin for macho file format */
    (mitfactory_plugin_release_context_decl)
    mitfactory_plugin_macho_release_context,
    mitfactory_plugin_macho_can_read_file,
    mitfactory_plugin_macho_can_read_buffer,
    (mitfactory_plugin_read_file_decl)
    mitfactory_plugin_macho_read_file,
    (mitfactory_plugin_read_buffer_decl)
    mitfactory_plugin_macho_read_buffer,
    &macho_iface
};

void*
mitfactory_plugin_macho_release_context
(void)
{
    /* TODO - NOT IMPLEMENTED YET !!! */
    return NULL;
}

bool
mitfactory_plugin_macho_can_read_file
(const char* file_name)
{
    /* local function variables */
    bool       status = false;
    char*      buffer = NULL;
    FILE* file_handle = NULL;
    long    file_size = 0;
    bool     can_read = false;
    /* ------------------------ */
    
    /* check function parameters */
    if(file_name == NULL)
    {
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
        goto bail_1;
    }
    
    /* can read buffer ? */
    if(!(can_read = mitfactory_plugin_macho_can_read_buffer(buffer,
      (size_t)file_size)))
    {
        /* unable to read buffer */
        goto bail_1;
    }
    
    /* everything went fine */
    status = can_read;
bail_1:
    free(buffer);
bail_0:
    fclose(file_handle);
bail:
    return status;
}

bool
mitfactory_plugin_macho_can_read_buffer
(
    const char* buffer,
    size_t      size
)
{
    /* local function variables */
    bool           status = false;
    uint32_t        magic = 0;
    /* ------------------------ */
    
    /* check size */
    if(size <= 4)
    {
        /* macho file too small */
        goto bail;
    }
    
    /* retrieve magic and validate */
    magic = ((uint32_t*)buffer)[0];
    if(!mitfactory_macho_object_is_valid_magic(magic))
    {
        /* incompatible macho detected */
        goto bail;
    }
    
    /* compatible magic detected */
    status = true;
    
    /* everything went fine */
bail:
    return status;
}

enum mitfactory_plugin_macho_error
mitfactory_plugin_macho_read_file
(
    const char*                 file_name,
    struct mitfactory_context** context
)
{
    /* local function variables */
    enum mitfactory_plugin_macho_error err = PLUG_MACHO_ERROR_FAILURE;
    struct mitfactory_context*    lcontext = NULL;
    char*                           buffer = NULL;
    FILE*                      file_handle = NULL;
    long                         file_size = 0;
    /* ------------------------------------------------------------ */
    
    /* check function parameters */
    if(file_name == NULL || context == NULL)
    {
        err = (int)MITFACTORY_ERROR_INVAL_PARAM;
        goto bail;
    }
    
    /* is plugin compatible with file */
    if(!mitfactory_plugin_macho_can_read_file(file_name))
    {
        err = PLUG_MACHO_ERROR_NO_A_MACHO_BINARY;
        goto bail;
    }
    
    /* open file for reading */
    file_handle = fopen(file_name, "rb");
    if(file_handle == NULL)
    {
        /* unable to open file */
        err = (int)MITFACTORY_ERROR_FILE_ERROR;
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
        err = (int)MITFACTORY_ERROR_ALLOC_FAILED;
        goto bail_0;
    }
    
    /* read file content */
    if(fread(buffer, 1, file_size, file_handle) != file_size)
    {
        /* unable to read from file */
        err = (int)MITFACTORY_ERROR_FILE_IO_ERROR;
        goto bail_1;
    }
    
    /* read macho from buffer */
    err = mitfactory_plugin_macho_read_buffer(buffer, (size_t)file_size,
      &lcontext);
    if(err != PLUG_MACHO_ERROR_SUCCESS)
    {
        /* unable to read buffer */
        goto bail_1;
    }
    
    /* set return parameters */
    *context = lcontext;
    
    /* everything went fine */
    err = PLUG_MACHO_ERROR_SUCCESS;
bail_1:
    free(buffer);
bail_0:
    fclose(file_handle);
bail:
    return err;
}

enum mitfactory_plugin_macho_error
mitfactory_plugin_macho_read_buffer
(
    const char*                 buffer,
    size_t                      size,
    struct mitfactory_context** context
)
{
    /* local function variables */
    enum mitfactory_plugin_macho_error err = PLUG_MACHO_ERROR_FAILURE;
    struct mitfactory_context*    lcontext = NULL;
    /* ------------------------------------------------------------ */
    
    if(buffer == NULL || size == 0 || context == NULL)
    {
        /* invalid function parameters */
        err = (int)MITFACTORY_ERROR_INVAL_PARAM;
        goto bail;
    }
    
    /* is plugin compatible with file */
    if(!mitfactory_plugin_macho_can_read_buffer(buffer, size))
    {
        err = PLUG_MACHO_ERROR_NO_A_MACHO_BINARY;
        goto bail;
    }
    
    
    
    
    
    
    
    
    
    /* set return parameters */
    *context = lcontext;
    
    /* everything went fine */
    err = PLUG_MACHO_ERROR_SUCCESS;
bail:
    return err;
}