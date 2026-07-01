{
  description = "Gamble compiler flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            python3
            gcc
            clang
            cmake
            ninja
            pkg-config
            llvm_18
            valgrind
            lldb
            bear
            ccache
          ];
        };

        devShells.llvm = pkgs.mkShell {
          buildInputs = with pkgs; [
            gcc
            clang
            cmake
            ninja
            llvm_18
            llvmPackages_18.libllvm
            llvmPackages_18.libclang
          ];
        };
      }
    );
}
