import re
from pathlib import Path

def main() -> None:
    codes: dict[str, str] = {}
    codes_re = re.compile(r"^#define\s+(STATUS_[A-Z_]*)\s+\(\s*\(\s*DWORD\s*\)\s*(0x[A-Z0-9]*)L?\s*\)\s*$", re.MULTILINE)
    for (macro_name, hex) in codes_re.findall(Path("winnt.h").read_text()):
        codes[macro_name] = hex
    names_re = re.compile(r"<tr>.*?(EXCEPTION_\w*).*?(STATUS_\w+).*?</tr>", re.MULTILINE | re.DOTALL)
    for (exception, status) in names_re.findall(Path("docs_table.html").read_text()):
        assert(status in codes)
        codes[status + f" aka {exception}"] = codes.pop(status)
    with open("data.c", "w") as file:
        def p(*args, **kwargs):
            print(*args, **kwargs, file=file)
        p("#include <stdint.h>\nconst uint32_t codes[] = {")
        for code in codes.values():
            p(f"    {code},")
        p("};\nconst char* names[] = {")
        for name in codes.keys():
            p(f"    \"{name}\",")
        p(f"}};\nconst int data_len = {len(codes)};")

if __name__ == "__main__":
    main()
