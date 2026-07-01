#!/usr/bin/env python3
import subprocess
import sys

def run(cmd):
    return subprocess.check_output(cmd, text=True).strip()

def main():

    if len(sys.argv) > 2:
        print("Usage: git gamblec-commit \"message\"")
        sys.exit(1)

    staged_files = run(["git", "diff", "--cached", "--name-only"]).splitlines()

    if(len(staged_files) == 0):
        subprocess.run(["git", "status"])
        sys.exit(1)

    files_to_write = ""
    for f in staged_files:
        files_to_write += f"* {f},\n"
    if files_to_write.endswith(",\n"):
        files_to_write = files_to_write[:-2] + ": Here.\n"

    commit_title = "Auto-commit-message"
    if len(sys.argv) == 2:
        commit_title=sys.argv[1]

    commit_message = f"{commit_title}\n\n{files_to_write}"

    subprocess.run(["git", "commit", "-m", commit_message])
    subprocess.run(["git", "commit", "--amend"])


if __name__ == "__main__":
    main()

