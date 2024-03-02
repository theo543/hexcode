# hexcode

A program to convert numbers to unsigned 32-bit in hex. Helpful when running programs from PowerShell, since powershell doesn't show exit codes in hex. If the code matches a Windows exception exit code as defined in `winnt.h` and [Microsoft docs](https://web.archive.org/web/20230707130733/https://learn.microsoft.com/en-us/windows/win32/debug/getexceptioncode) it will print the name as well.

```PowerShell
PS C:\> hexcode -1
0xFFFFFFFF

PS C:\> hexcode 0xAAA
0x00000AAA

PS C:\> hexcode 0xC0000135
0xC0000135 (STATUS_DLL_NOT_FOUND)

PS C:\> .\segfault.exe
NativeCommandExitException: Program "segfault.exe" ended with non-zero exit code: -1073741819.

PS C:\> hexcode -1073741819
0xC0000005 (STATUS_ACCESS_VIOLATION aka EXCEPTION_ACCESS_VIOLATION)
```

## Building

```PowerShell
> cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
> cmake --build build
# copy build\hexcode.exe to a directory in your PATH
```
