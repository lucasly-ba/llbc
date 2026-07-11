#!/usr/bin/env bash

set -u

BIN="${GBLC:-./src/gblc}"
ROOT="${1:-tests/binder}"

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

    if ! "$BIN" --print-ast --bindings "$f" >"$tmp/out" 2>"$tmp/err"; then
        printf 'FAIL  good/%-24s expected clean bind, got error\n' "$name"
        sed 's/^/        /' "$tmp/err"
        fail=$((fail + 1))
        continue
    fi

    if grep -q 'unbound' "$tmp/out"; then
        printf 'FAIL  good/%-24s unresolved name(s) in bindings output\n' "$name"
        grep -n 'unbound' "$tmp/out" | sed 's/^/        /'
        fail=$((fail + 1))
        continue
    fi

    printf 'PASS  good/%-24s\n' "$name"
    pass=$((pass + 1))
done

for f in "$ROOT"/errors/*.gbl; do
    [ -e "$f" ] || continue
    name="$(basename "$f")"

    "$BIN" "$f" >"$tmp/out" 2>"$tmp/err"
    rc=$?

    if [ "$rc" -eq 3 ]; then
        printf 'PASS  errors/%-22s %s' "$name" "$(head -n1 "$tmp/err")"
        printf '\n'
        pass=$((pass + 1))
    elif [ "$rc" -eq 0 ]; then
        printf 'FAIL  errors/%-22s bound clean, expected a bind error\n' "$name"
        fail=$((fail + 1))
    else
        printf 'FAIL  errors/%-22s expected bind error (3), got exit %d\n' \
            "$name" "$rc"
        sed 's/^/        /' "$tmp/err"
        fail=$((fail + 1))
    fi
done

echo
echo "bind: $pass passed, $fail failed"
[ "$fail" -eq 0 ]
