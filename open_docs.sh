#!/bin/bash

DOCS_FILE="Docs/html/index.html"

if [ -f "$DOCS_FILE" ]; then
    echo "Opening documentation..."
    xdg-open "$DOCS_FILE"
else
    echo "Documentation not found. Run: doxygen Doxyfile"
    exit 1
fi
