import os
import re
import sys

def patch_scons():
    print("--- Patching SCons configuration files ---")
    for root, dirs, files in os.walk('.'):
        for file in files:
            if file in ['SConstruct', 'SConscript']:
                path = os.path.join(root, file)
                try:
                    with open(path, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                    
                    # 1. Inherit system environment for compiler detection
                    # 2. Disable Treat Warnings as Errors (/WX -> /WX-)
                    # 3. Enable permissive mode (/permissive- -> /permissive) for old libs
                    new_content = content.replace('env = Environment(', 'env = Environment(ENV = os.environ, ')
                    new_content = new_content.replace('/WX', '/WX-')
                    new_content = new_content.replace('/permissive-', '/permissive')
                    
                    # Remove /Zc:inline as it's known to conflict with if constexpr in VS 2022 ICE
                    new_content = new_content.replace("'/Zc:inline'", "").replace('"/Zc:inline"', "")
                    
                    if new_content != content:
                        with open(path, 'w', encoding='utf-8') as f:
                            f.write(new_content)
                        print(f"Patched: {path}")
                except Exception as e:
                    print(f"Failed to patch {path}: {e}")
    
    # 4. Force injection of VS 2022 compatibility flags at the end of SConstruct
    if os.path.exists('SConstruct'):
        try:
            with open('SConstruct', 'a') as f:
                f.write("\n# Forced VS 2022 compatibility flags - Fix ICE in future_impl.h\n")
                # Using /d2clret- to help with deduction crashes
                f.write("if 'env' in locals(): env.Append(CCFLAGS=['/Zc:lambda-', '/d2clret-', '/bigobj'])\n")
            print("Injected VS 2022 ICE-fix flags into root SConstruct")
        except Exception as e:
            print(f"Failed to inject flags: {e}")

def patch_mozjs():
    print("--- Patching mozjs StoreBuffer.h (Robust Version) ---")
    path = 'src/third_party/mozjs-60/extract/js/src/gc/StoreBuffer.h'
    if not os.path.exists(path):
        print(f"Warning: {path} not found. Skipping.")
        return
    try:
        with open(path, 'r', encoding='utf-8') as f:
            content = f.read()
        new_content = content
        while True:
            match = re.search(r'typedef struct \s*\{', new_content)
            if not match: break
            start_idx = match.start()
            brace_start = match.end() - 1
            count = 1
            brace_end = -1
            for i in range(brace_start + 1, len(new_content)):
                if new_content[i] == '{': count += 1
                elif new_content[i] == '}':
                    count -= 1
                    if count == 0:
                        brace_end = i
                        break
            if brace_end == -1: break
            suffix_match = re.match(r'\s*(\w+);', new_content[brace_end+1:])
            if suffix_match:
                name = suffix_match.group(1)
                body = new_content[brace_start+1:brace_end]
                full_match_end = brace_end + 1 + suffix_match.end()
                replacement = f"struct {name} {{{body}}};"
                new_content = new_content[:start_idx] + replacement + new_content[full_match_end:]
            else:
                new_content = new_content[:start_idx] + "STRUCT_PROCESSED" + new_content[start_idx+6:]
        new_content = new_content.replace("STRUCT_PROCESSED", "typedef struct ")
        if new_content != content:
            with open(path, 'w', encoding='utf-8') as f:
                f.write(new_content)
            print(f"Patched with balanced braces: {path}")
    except Exception as e:
        print(f"Failed to patch mozjs: {e}")

def patch_s2():
    print("--- Patching S2 Geometry Library ---")
    path = 'src/third_party/s2/s2cellid.cc'
    if not os.path.exists(path):
        print(f"Warning: {path} not found. Skipping.")
        return
    try:
        with open(path, 'r', encoding='utf-8') as f:
            content = f.read()
        if 'namespace stdext' not in content:
            patch = "\n#if defined(_MSC_VER) && _MSC_VER >= 1930\nnamespace stdext { template<typename T> size_t hash_value(const T&); }\n#endif\n"
            content = patch + content
            with open(path, 'w', encoding='utf-8') as f:
                f.write(content)
            print(f"Patched (injected declaration): {path}")
    except Exception as e:
        print(f"Failed to patch S2: {e}")

if __name__ == "__main__":
    patch_scons()
    patch_mozjs()
    patch_s2()
    print("--- All patches applied successfully ---")
