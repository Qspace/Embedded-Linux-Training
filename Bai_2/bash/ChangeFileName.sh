for file in prefix*; do mv "$file" "${file#prefix}"; done;
