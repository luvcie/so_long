{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    clang_12
    gnumake
    xorg.libX11
    xorg.libX11.dev
    xorg.libXext
    xorg.libXext.dev
    libbsd
  ];

  shellHook = ''
    export CC=${pkgs.clang_12}/bin/clang
    export X11_INCLUDE="${pkgs.xorg.libX11.dev}/include"
    export CFLAGS="-I${pkgs.xorg.libX11.dev}/include"
    export LDFLAGS="-L${pkgs.xorg.libX11}/lib -L${pkgs.xorg.libXext}/lib"
  '';
}
