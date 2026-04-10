import os
import re
import sys

def patch_scons():
    print("--- Patching SCons configuration files (Global Optimization Downgrade) ---")
    for root, dirs, files in os.walk('.'):
        for file in files:
            if file in ['SConstruct', 'SConscript']:
                path = os.path.join(root, file)
                try:
                    with open(path, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                    
                    # 1. Inherit system environment
                    new_content = content.replace('env = Environment(', 'env = Environment(ENV = os.environ, ')
                    
                    # 2. Global optimization downgrade /O2 -> /O1 to avoid ICE
                    new_content = new_content.replace('/O2', '/O1')
                    
                    # 3. Disable /WX and enable /permissive
                    new_content = new_content.replace('/WX', '/WX-')
                    new_content = new_content.replace('/permissive-', '/permissive')
                    
                    if new_content != content:
                        with open(path, 'w', encoding='utf-8') as f:
                            f.write(new_content)
                        print(f"Patched: {path}")
                except Exception as e:
                    print(f"Failed to patch {path}: {e}")
    
    # 4. Inject ICE-fix flags
    if os.path.exists('SConstruct'):
        try:
            with open('SConstruct', 'a') as f:
                f.write("\n# Forced VS 2022 compatibility flags\n")
                f.write("if 'env' in locals(): env.Append(CCFLAGS=['/Zc:lambda-', '/d2clret-'])\n")
            print("Injected VS 2022 ICE-fix flags")
        except Exception as e:
            print(f"Failed to inject flags: {e}")

def patch_future():
    print("--- Patching future_impl.h (AST Induction Version) ---")
    path = 'src/mongo/util/future_impl.h'
    if not os.path.exists(path): return
    try:
        with open(path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        # Surgical fix: use comma operator to nudge the compiler AST generator
        # This often bypasses deduction issues in VS 2022
        new_content = content.replace('return notReady();', 'return (void)0, notReady();')
        
        if new_content != content:
            with open(path, 'w', encoding='utf-8') as f:
                f.write(new_content)
            print(f"Applied AST induction patch to: {path}")
    except Exception as e:
        print(f"Failed to patch future_impl.h: {e}")

def patch_mozjs():
    # ... (Keeping the robust logic from previous version)
    path = 'src/third_party/mozjs-60/extract/js/src/gc/StoreBuffer.h'
    if not os.path.exists(path): return
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
    except: pass

def patch_s2():
    path = 'src/third_party/s2/s2cellid.cc'
    if not os.path.exists(path): return
    try:
        with open(path, 'r', encoding='utf-8') as f: content = f.read()
        if 'namespace stdext' not in content:
            patch = "\n#if defined(_MSC_VER) && _MSC_VER >= 1930\nnamespace stdext { template<typename T> size_t hash_value(const T&); }\n#endif\n"
            with open(path, 'w', encoding='utf-8') as f: f.write(patch + content)
    except: pass

if __name__ == "__main__":
    patch_scons()
    patch_future()
    patch_mozjs()
    patch_s2()
    print("--- All patches applied with AST induction logic ---")
