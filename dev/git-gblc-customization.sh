#!/bin/sh

git config alias.gblc-commit '!f() { "`git rev-parse --show-toplevel`/dev/git-gblc-commit.py" "$@"; }; f'

read -p "Name? " NAME
read -p "Mail? " EMAIL

git config user.name "$NAME"
git config user.email "$EMAIL"

echo "Git configured locally with:"
echo "Name: $NAME"

echo "Email: $EMAIL"
