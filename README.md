# Essa Extensões para NuclearCloud OS foi feito por:
  NWL Systems

## E qualquer falsa acusação e Difamação sobre esta Extensão ter sido criado por Você, É Extremamente Proibido
e para Instalar o compilador para criar um APP, Docs e entre outros
... é so vim aqui:

    github.com/NWL-Systems/nc-language

### Instalação
```bash
git clone https://github.com/NWL-Systems/nc-os-extensions-files.git
cd nc-os-extensions-files
```

Extensões:
```bash
    .ncfile: para arquivos de qualquer tipo

    .ncdocs: para jsons e documentos e textos

    .ncapp: para apps comuns

    .ncprivapp: para apps especiais

    .ncdevapp: para apps pra quem é Desenvolvedor/Programador

    .ncimg: para imagens
```

# Exemplos de Compilação para App e o resto:
   so muda a forma como quer compilar

# .ncapp - Aplicativo normal
    nclang meuapp.nc meuapp.ncapp

# .ncdevapp - App de desenvolvedor
    nclang userexemple.nc terminal.ncdevapp

# .ncprivapp - App especial
    nclang userexemple.nc settings.ncprivapp

E para compilar só o arquivo .nc pode ser dessa forma
```bash
    nclang filemanager.nc
```