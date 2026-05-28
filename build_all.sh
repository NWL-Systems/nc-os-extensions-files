#!/bin/bash
# Build NC Language compiler para todas as plataformas
# © 2026 NWL-Systems

echo "=== NC Language Compiler Build ==="
echo "© 2026 NWL-Systems"
echo ""

# Linux
echo "Compilando para Linux..."
gcc -o nc nc_compiler.c -lm && echo "✓ Linux: ./nc"

# Android (Termux)
echo "Compilando para Android (Termux)..."
clang -o nc_android nc_compiler.c -lm && echo "✓ Android: ./nc_android"

# Windows (requer MinGW)
echo "Compilando para Windows..."
x86_64-w64-mingw32-gcc -o nc.exe nc_compiler.c -lm 2>/dev/null && echo "✓ Windows: nc.exe" || echo "⚠ MinGW nao encontrado - instale com: sudo apt install mingw-w64"

# Mac (requer macOS ou osxcross)
echo ""
echo "Para Mac: clang -o nc nc_compiler.c -lm"
echo ""
echo "=== Build completo! ==="
echo "Uso: nc programa.nc"
