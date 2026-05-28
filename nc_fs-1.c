#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include "nc_fs.h"

// Inicializa estrutura de diretorios
void nc_init_dirs(NCUserDirs *dirs, const char *base) {
    snprintf(dirs->root,     512, "%s/NuclearCloud", base);
    snprintf(dirs->config,   512, "%s/NuclearCloud/Config", base);
    snprintf(dirs->user,     512, "%s/NuclearCloud/Config/User", base);
    snprintf(dirs->sdcard,   512, "%s/NuclearCloud/Config/User/SDcard_Cloud", base);
    snprintf(dirs->tmp,      512, "%s/NuclearCloud/Config/User/SDcard_Cloud/TMP", base);
    snprintf(dirs->apps,     512, "%s/NuclearCloud/Config/User/Apps", base);
    snprintf(dirs->docs,     512, "%s/NuclearCloud/Config/User/Docs", base);
    snprintf(dirs->imgs,     512, "%s/NuclearCloud/Config/User/Images", base);
    snprintf(dirs->devapps,  512, "%s/NuclearCloud/Config/User/DevApps", base);
    snprintf(dirs->privapps, 512, "%s/NuclearCloud/Config/User/PrivApps", base);
    snprintf(dirs->lang,     512, "%s/NuclearCloud/Config/User/Languages", base);
}

// Cria todos os diretorios
int nc_create_dirs(NCUserDirs *dirs) {
    char *paths[] = {
        dirs->root, dirs->config, dirs->user,
        dirs->sdcard, dirs->tmp, dirs->apps,
        dirs->docs, dirs->imgs, dirs->devapps,
        dirs->privapps, dirs->lang, NULL
    };
    for (int i = 0; paths[i]; i++) {
        #ifdef _WIN32
            mkdir(paths[i]);
        #else
            mkdir(paths[i], 0755);
        #endif
    }
    printf("[NCFS] Estrutura de pastas criada em: %s\n", dirs->root);
    return 0;
}

// Cria um arquivo NC com cabecalho
int nc_create_file(const char *path, const char *magic, const char *data, unsigned int size, unsigned int flags) {
    FILE *f = fopen(path, "wb");
    if (!f) return -1;

    NCFileHeader h;
    memset(&h, 0, sizeof(h));
    strncpy(h.magic, magic, 4);
    strncpy(h.version, "2.0", 4);

    // Nome do arquivo (sem path)
    const char *name = strrchr(path, '/');
    strncpy(h.name, name ? name+1 : path, 255);

    strncpy(h.owner, "NuclearCloud", 63);
    h.size = size;
    h.flags = flags;

    // Data de criacao
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(h.created, 32, "%Y-%m-%d %H:%M:%S", tm);

    fwrite(&h, sizeof(h), 1, f);
    if (data && size > 0) fwrite(data, 1, size, f);
    fclose(f);
    return 0;
}

// Le um arquivo NC
int nc_read_file(const char *path, NCFileHeader *header, char *data, unsigned int maxsize) {
    FILE *f = fopen(path, "rb");
    if (!f) return -1;
    fread(header, sizeof(NCFileHeader), 1, f);
    if (data && maxsize > 0) {
        unsigned int toread = header->size < maxsize ? header->size : maxsize;
        fread(data, 1, toread, f);
    }
    fclose(f);
    return 0;
}

// Retorna o tipo baseado na extensao
const char* nc_get_type(const char *filename) {
    if (strstr(filename, ".ncfile"))   return "Arquivo NC";
    if (strstr(filename, ".ncimg"))    return "Imagem NC";
    if (strstr(filename, ".ncdocs"))   return "Documento NC";
    if (strstr(filename, ".ncapp"))    return "Aplicativo NC";
    if (strstr(filename, ".ncprivapp"))return "App Especial NC";
    if (strstr(filename, ".ncdevapp")) return "App Dev NC";
    if (strstr(filename, ".nc"))       return "Codigo NC Language";
    return "Arquivo desconhecido";
}

// Verifica se e um arquivo NC valido
int nc_is_valid(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return 0;
    char magic[4];
    fread(magic, 1, 4, f);
    fclose(f);
    return (strncmp(magic, "NCL", 3) == 0 || strncmp(magic, "NCA", 3) == 0);
}
