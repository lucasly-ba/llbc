#!/usr/bin/env bash

set -u

BIN="${GBLC:-./src/gblc}"
ROOT="${1:-tests/gbir}"

if [ ! -x "$BIN" ]; then
    echo "error: gblc binary not found at '$BIN' (set GBLC=...)" >&2
    exit 2
fi

tmp="$(mktemp -d)"
trap 'rm -rf "$tmp"' EXIT

pass=0
fail=0

for f in "$ROOT"/good/*.gbl; do
    [ -e "$f" ] || continue
    name="$(basename "$f" .gbl)"
    golden="$ROOT/good/$name.gbir"

    if ! "$BIN" --print-gbir "$f" >"$tmp/out" 2>"$tmp/err"; then
        printf 'FAIL  good/%-22s gbir generation failed\n' "$name.gbl"
        sed 's/^/        /' "$tmp/err"
        fail=$((fail + 1))
        continue
    fi

    if [ "${GBIR_UPDATE:-0}" = "1" ]; then
        cp "$tmp/out" "$golden"
        printf 'UPDATE good/%-22s\n' "$name.gbl"
        pass=$((pass + 1))
        continue
    fi

    if [ ! -e "$golden" ]; then
        printf 'FAIL  good/%-22s missing golden (run GBIR_UPDATE=1)\n' \
            "$name.gbl"
        fail=$((fail + 1))
        continue
    fi

    if diff -q "$golden" "$tmp/out" >/dev/null; then
        printf 'PASS  good/%-22s\n' "$name.gbl"
        pass=$((pass + 1))
    else
        printf 'FAIL  good/%-22s output differs from golden\n' "$name.gbl"
        diff "$golden" "$tmp/out" | sed 's/^/        /'
        fail=$((fail + 1))
    fi
done

echo
echo "gbir: $pass passed, $fail failed"
[ "$fail" -eq 0 ]
