#include <stdio.h>
#include <stdbool.h>

#include <mitfactory/mitfactory.h>

bool
mitfactory_macho_object_is_valid_magic
(uint32_t magic)
{
    /* local function variables */
    bool           status = false;
    /* ------------------------ */
    
    if(magic != FFS_MH_MAGIC    &&
       magic != FFS_MH_MAGIC_64 &&
       magic != FFS_MH_CIGAM    &&
       magic != FFS_MH_CIGAM_64 &&
       magic != FFS_FAT_MAGIC   &&
       magic != FFS_FAT_CIGAM)
    {
        /* value is not valid */
        goto bail;
    }
    
    /* valid macho or fat magic value detected */
    status = true;
    
    /* everything went fine */
bail:
    return status;
}