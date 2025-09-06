find . -name "*.c" -exec sh -c '
for file; do
    sed -i "1s|^|/*\n * Copyright (C) 2025 Ivan Gaydardzhiev\n * Licensed under the GPL-3.0-only\n */\n\n|" "$file"
done
' sh {} +
