# Adding Classes
- Copy `template.cpp` and `.hpp` from `src/haggle/sdk/` to `src/haggle/sdk/SexySDK/`
- Rename `template.` to whatever class you are adding, in this example: `FloatingTextMgr`

- In `FloatingTextMgr.hpp`:
    - rename the `Template` class to `FloatingTextMgr`
    - rename the `Template* temp` to `FloatingTextMgr* floating_text_mgr`

- In `FloatingTextMgr.cpp`:
    - Auto method:
        - Ctrl + H 
        - replace `Template` with `FloatingTextMgr`
    - Manual method:
        - rename any `Template` line with `FloatingTextMgr`
    
    - In the `Sexy::FloatingTextMgr::setup` function, replace `0x0` with the ctor address
        - in this case, `0x0046E6E0`
    - Double check the detour'd ctor function for the proper calling convention and arguments
        - in this case, it only calls `this` as a `__thiscall`
            - when detouring a function without the entire class reversed, we do `__fastcall` and pass `ecx` and `edx`

- In `sdk/SexySDK.hpp`:
    - add `sdk/FloatingTextMgr.hpp` to the headers

- In `main.cpp`:
    - add `Sexy::FloatingTextMgr::setup()` to the modules list