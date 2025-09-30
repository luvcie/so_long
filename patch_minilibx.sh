#!/usr/bin/env bash
# Only runs on NixOS (when NIX_STORE is set)
if [ -n "$NIX_STORE" ] && [ -f minilibx-linux/configure ]; then
    echo "Patching minilibx configure for NixOS..."
    
    X11_INC="${X11_INCLUDE:-/usr/include}"
    
    cat > minilibx-linux/makefile.gen << EOF
INC=$X11_INC
HT==
DOCP=no
OLIBA=
INCLIB=
FLAG_GL=-lGL
EOF
    
    if [ -f minilibx-linux/Makefile.mk ]; then
        sed -i "s|INC.*=.*%%%%|include makefile.gen|g" minilibx-linux/Makefile.mk
    fi
    
    cat > minilibx-linux/configure << 'EOF'
#!/usr/bin/env bash
echo "Using pre-generated configuration for NixOS"
exit 0
EOF
    chmod +x minilibx-linux/configure
    
    cat > minilibx-linux/Makefile << 'EOF'
all:
	@./configure
	@make -f Makefile.mk all

clean:
	@make -f Makefile.mk clean

re: clean all
EOF
fi
