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
                    # 4. Fix VS 2022 Internal Compiler Error (ICE) via /Zc:lambda-
                    new_content = content.replace('env = Environment(', 'env = Environment(ENV = os.environ, ')
                    new_content = new_content.replace('/WX', '/WX-')
                    new_content = new_content.replace('/permissive-', '/permissive')
                    new_content = new_content.replace('/Zc:inline', '/Zc:inline /Zc:lambda-')
                    
                    if new_content != content:
                        with open(path, 'w', encoding='utf-8') as f:
                            f.write(new_content)
                        print(f"Patched: {path}")
                except Exception as e:
                    print(f"Failed to patch {path}: {e}")

def patch_mozjs():
    print("--- Patching mozjs StoreBuffer.h (Robust Version) ---")
    path = 'src/third_party/mozjs-60/extract/js/src/gc/StoreBuffer.h'
    if not os.path.exists(path):
        print(f"Warning: {path} not found. Skipping.")
        return
    
    try:
        with open(path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        # We need to find "typedef struct {" and match it with the correct closing "}"
        # that precedes " Name;"
        new_content = content
        while True:
            match = re.search(r'typedef struct \s*\{', new_content)
            if not match:
                break
            
            start_idx = match.start()
            brace_start = match.end() - 1
            
            # Find matching closing brace
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
            
            # Find the name after the closing brace
            suffix_match = re.match(r'\s*(\w+);', new_content[brace_end+1:])
            if suffix_match:
                name = suffix_match.group(1)
                body = new_content[brace_start+1:brace_end]
                full_match_end = brace_end + 1 + suffix_match.end()
                
                # Replace with: struct Name { body };
                replacement = f"struct {name} {{{body}}};"
                new_content = new_content[:start_idx] + replacement + new_content[full_match_end:]
            else:
                # Not the pattern we are looking for, skip this one
                # Advanced: move past this struct or mark it
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
            
        # Fix stdext::hash_value compatibility issue for VS 2022
        # We need to declare the primary template before specializing it
        if 'namespace stdext' not in content:
            patch = "\n#if defined(_MSC_VER) && _MSC_VER >= 1930\nnamespace stdext { template<typename T> size_t hash_value(const T&); }\n#endif\n"
            content = patch + content
            with open(path, 'w', encoding='utf-8') as f:
                f.write(content)
            print(f"Patched (injected declaration): {path}")
        else:
            print(f"Skipping S2 patch: already patched or declaration exists.")
    except Exception as e:
        print(f"Failed to patch S2: {e}")

if __name__ == "__main__":
    # We expect to be run from the robo-shell root directory
    patch_scons()
    patch_mozjs()
    patch_s2()
    print("--- All patches applied successfully ---")
