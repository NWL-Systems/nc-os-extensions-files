#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nc_fs.h"

int main(int argc, char **argv) {
    // Base: sdcard no Android, home no desktop
    const char *base;
    #ifdef __ANDROID__
        base = "/sdcard";
    #else
        base = getenv("HOME") ? getenv("HOME") : ".";
    #endif

    if (argc > 1) base = argv[1];

    printf("=== NuclearCloud OS - Setup de Pastas ===\n");
    printf("© 2026 NWL-Systems\n\n");

    NCUserDirs dirs;
    nc_init_dirs(&dirs, base);
    nc_create_dirs(&dirs);

    printf("\nEstrutura criada:\n");
    printf("  %s\n", dirs.root);
    printf("  %s\n", dirs.config);
    printf("  %s\n", dirs.user);
    printf("  %s\n", dirs.sdcard);
    printf("  %s\n", dirs.tmp);
    printf("  %s\n", dirs.apps);
    printf("  %s\n", dirs.docs);
    printf("  %s\n", dirs.imgs);
    printf("  %s\n", dirs.devapps);
    printf("  %s\n", dirs.privapps);
    printf("  %s\n", dirs.lang);

    // Cria arquivo de boas vindas
    char welcome[512];
    snprintf(welcome, 512, "%s/NuclearCloud/Config/User/welcome.ncdocs", base);
    const char *msg = "Bem vindo ao NuclearCloud OS!\n© 2026 NWL-Systems\n";
    nc_create_file(welcome, NC_MAGIC_DOCS, msg, strlen(msg), NC_FLAG_READ);
    printf("\nArquivo de boas vindas criado: welcome.ncdocs\n");

    printf("\n✓ NuclearCloud OS pronto!\n");
    return 0;
}
