{
  description = "Game framework flake.";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }: 
  let
    pkgs = nixpkgs.legacyPackages.x86_64-linux;
  in 
  {
    devShells.x86_64-linux.default = 
    let
      sdl3ConfigDeps = with pkgs; [
        alsa-lib.dev
        hidapi
        ibusMinimal.dev
        jack2.dev
        libdecor.dev
        libthai.dev
        fribidi.dev
        libGL.dev
        libpulseaudio.dev
        libusb1.dev
        libX11.dev
        libxcursor.dev
        libxext.dev
        libxfixes.dev
        libxi.dev
        libxinerama.dev
        libxkbcommon.dev
        libxrandr.dev
        libxrender.dev
        libxtst
        libxscrnsaver
        mesa
        pipewire.dev
        sndio
      ];
      debugTools = with pkgs; [
        gef
        strace
      ];
    in 
    pkgs.mkShell {
      packages = with pkgs; [
        clang-tools
        cmake 
        ninja

        vulkan-headers.out
      ] ++ [sdl3ConfigDeps debugTools];

      shellHook = ''
        echo "Entering game framework shell!"
      '';
    };
  };
}
