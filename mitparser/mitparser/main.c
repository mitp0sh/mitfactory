#include <stdio.h>

#include <mitfactory/mitfactory.h>

int main(int argc, const char * argv[])
{
    /* local function variables */
    union mitfactory_error err;
    struct mitfactory_context* context = NULL;
    /* ------------------------------------ */
    
    /* try to parse macho file */
    err = mitfactory_read_file("/usr/bin/uname", &context);
    if(err.factory_error != MITFACTORY_ERROR_SUCCESS)
    {
        printf("err - unable to parse file!\n");
        goto bail;
    }
    printf("file successfully parsed\n");
    
    /* everything went fine */
bail:
    return 0;
}

