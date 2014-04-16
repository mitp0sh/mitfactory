#ifndef MITFACTORY_MACHO_SPEC_H
    #define MITFACTORY_MACHO_SPEC_H

enum mfp_macho_header_magic
{
    FFS_MH_MAGIC    = 0xfeedface,
    FFS_MH_CIGAM    = 0xcefaedfe,
    FFS_MH_MAGIC_64 = 0xfeedfacf,
    FFS_MH_CIGAM_64 = 0xcffaedfe
};

enum mfp_fat_header_magic
{
    FFS_FAT_MAGIC = 0xcafebabe,
    FFS_FAT_CIGAM = 0xbebafeca
};

#endif