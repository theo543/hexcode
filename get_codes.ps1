cat winnt.h | sd "^#define\s+(STATUS_[A-Z_]*)\s+\(\s*\(\s*DWORD\s*\)\s*(0x[A-Z0-9]*)L?\s*\)\s*$" "ERRORCODE: codes[`$2] = `"`$1`";`n" | sls "ERRORCODE:" | sd "ERRORCODE: " "" > data/codes.inc
