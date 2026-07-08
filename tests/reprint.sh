#!/usr/bin/env bash

set -u

BIN="${GBLC:-./src/gblc}"
DIR="${1:-tests/parser/good}"

if [ ! -x "$BIN" ]; then
    echo "error: gblc binary not found at '$BIN' (set GBLC=...)" >&2
    exit 2
fi

tmp="$(mktemp -d)"
trap 'rm -rf "$tmp"' EXIT

pass=0
fail=0

for f in "$DIR"/*.gbl; do
    name="$(basename "$f")"

    if ! "$BIN" --print-ast "$f" >"$tmp/p1" 2>"$tmp/e1"; then
        printf 'FAIL  %-20s print #1 failed\n' "$name"
        sed 's/^/        /' "$tmp/e1"
        fail=$((fail + 1))
        continue
    fi

    if ! "$BIN" --print-ast "$tmp/p1" >"$tmp/p2" 2>"$tmp/e2"; then
        printf 'FAIL  %-20s reparse of printed output failed\n' "$name"
        sed 's/^/        /' "$tmp/e2"
        fail=$((fail + 1))
        continue
    fi

    if diff -q "$tmp/p1" "$tmp/p2" >/dev/null; then
        printf 'PASS  %-20s\n' "$name"
        pass=$((pass + 1))
    else
        printf 'FAIL  %-20s output not idempotent (print1 vs print2)\n' "$name"
        diff "$tmp/p1" "$tmp/p2" | sed 's/^/        /'
        fail=$((fail + 1))
    fi
done

echo
echo "reprint: $pass passed, $fail failed"
[ "$fail" -eq 0 ]
