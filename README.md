find . -type f ! -name '*.git*' ! -name 'Makefile' ! -name '*.c' ! -name 'LICENSE' ! -name '*.sh' -exec du -k {} + | awk '{sum += $1} END {print sum}'
