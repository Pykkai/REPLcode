#!/usr/bin/env bash
set -euo pipefail

codex exec -m gpt-5-codex --sandbox workspace-write <<'EOF'
- find source files in this repository with the tag @codex in comments
- the comments following the @codex tags are instructions for you
- instructions end with the comment block or tag @xedoc
- generate a session timestap at the beginning of each session in the form
  YYYY-MM-DD HH:mm
- after you make modifications related to a particular @codex tag,
  add the session timestamp after the @codex tag
- only update for @codex tags without revision timestamps; those with
  revsion timestamps are from previous sessions
- record the revision timestamp in the comment block marked @revision
  with one revision per line with a brief summary of the revisions
- comment code copiously for human review, in particular any block
  larger than a dozen lines
- mark your changes with a @review tag with the session timestamp
- do not look at files in the retired directory, these files are archived
  and not active parts of the project
- src/template.h and src/template.c are provided as style guides and should be followed
  especially when adding new source files, classes, methods, functions, and
  variables; these templates should also be used in refactoring when
  moving methods etc.
EOF
