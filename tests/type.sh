#!/usr/bin/env bash

set -u

BIN="${GBLC:-./src/gblc}"
ROOT="${1:-tests/type}"

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
    name="$(basename "$f")"

    "$BIN" "$f" >"$tmp/out" 2>"$tmp/err"
    rc=$?

    if [ "$rc" -eq 0 ]; then
        printf 'PASS  good/%-24s\n' "$name"
        pass=$((pass + 1))
    else
        printf 'FAIL  good/%-24s expected clean typecheck, got exit %d\n' \
            "$name" "$rc"
        sed 's/^/        /' "$tmp/err"
        fail=$((fail + 1))
    fi
done

for f in "$ROOT"/errors/*.gbl; do
    [ -e "$f" ] || continue
    name="$(basename "$f")"

    "$BIN" "$f" >"$tmp/out" 2>"$tmp/err"
    rc=$?

    if [ "$rc" -eq 4 ]; then
        printf 'PASS  errors/%-22s %s' "$name" "$(head -n1 "$tmp/err")"
        printf '\n'
        pass=$((pass + 1))
    elif [ "$rc" -eq 0 ]; then
        printf 'FAIL  errors/%-22s typechecked clean, expected a type error\n' \
            "$name"
        fail=$((fail + 1))
    else
        printf 'FAIL  errors/%-22s expected type error (4), got exit %d\n' \
            "$name" "$rc"
        sed 's/^/        /' "$tmp/err"
        fail=$((fail + 1))
    fi
done

echo
echo "type: $pass passed, $fail failed"
[ "$fail" -eq 0 ]
