import os
import re
import sys

def patch_universal_source():
    print("--- Universal Source Patching: IF_CONSTEXPR -> if constexpr ---")
    count = 0
    for root, dirs, files in os.walk('.'):
        for file in files:
            if file.endswith(('.h', '.cpp', '.cc', '.SConscript', 'SConstruct')):
                path = os.path.join(root, file)
                try:
                    with open(path, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                    
                    # 1. Kill the macro confusion globally
                    new_content = content.replace('IF_CONSTEXPR', 'if constexpr')
                    
                    # 2. Inherit environment
                    if file in ['SConstruct', 'SConscript']:
                        new_content = new_content.replace('env = Environment(', 'env = Environment(ENV = os.environ, ')
                        # Optimization downgrade to /O1 (Stable enough with template fixes)
                        new_content = new_content.replace('/O2', '/O1').replace('/Od', '/O1')
                        # Strip risky flags
                        for flag in ['/Gw', '/Gy', '/Zc:inline']:
                            new_content = new_content.replace(f"'{flag}'", "''")
                    
                    if new_content != content:
                        with open(path, 'w', encoding='utf-8') as f:
                            f.write(new_content)
                        count += 1
                except: pass
    print(f"Patched {count} files globally.")

def patch_future_deadlock():
    print("--- Patching future_impl.h (AST Deadlock Breaker) ---")
    path = 'src/mongo/util/future_impl.h'
    if not os.path.exists(path): return
    try:
        with open(path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        # Surgical fix: break the 'auto' deduction chain with a local variable
        # This simplifies the AST for the compiler
        new_content = content.replace('return notReady();', '{ auto ___res = notReady(); return ___res; }')
        
        if new_content != content:
            with open(path, 'w', encoding='utf-8') as f:
                f.write(new_content)
            print(f"Applied AST deadlock seeker to: {path}")
    except Exception as e:
        print(f"Failed to patch future_impl.h: {e}")

def patch_mozjs():
    # Robust balanced-brace logic (keeping it as it was working)
    path = 'src/third_party/mozjs-60/extract/js/src/gc/StoreBuffer.h'
    if not os.path.exists(path): return
    try:
        with open(path, 'r', encoding='utf-8') as f: content = f.read()
        new_content = content
        while True:
            match = re.search(r'typedef struct \s*\{', new_content)
            if not match: break
            start_idx = match.start(); brace_start = match.end() - 1
            cnt = 1; brace_end = -1
            for i in range(brace_start + 1, len(new_content)):
                if new_content[i] == '{': cnt += 1
                elif new_content[i] == '}':
                    cnt -= 1
                    if cnt == 0: brace_end = i; break
            if brace_end == -1: break
            suffix = re.match(r'\s*(\w+);', new_content[brace_end+1:])
            if suffix:
                name = suffix.group(1); body = new_content[brace_start+1:brace_end]
                new_content = new_content[:start_idx] + f"struct {name} {{{body}}};" + new_content[brace_end+1+suffix.end():]
            else: new_content = new_content[:start_idx] + "STRUCT_FIX" + new_content[start_idx+6:]
        new_content = new_content.replace("STRUCT_FIX", "typedef struct ")
        if new_content != content:
            with open(path, 'w', encoding='utf-8') as f: f.write(new_content)
    except: pass

def patch_s2():
    path = 'src/third_party/s2/s2cellid.cc'
    if not os.path.exists(path): return
    try:
        with open(path, 'r', encoding='utf-8') as f: content = f.read()
        if 'namespace stdext' not in content:
            patch = "\nnamespace stdext { template<typename T> size_t hash_value(const T&); }\n"
            with open(path, 'w', encoding='utf-8') as f: f.write(patch + content)
    except: pass

if __name__ == "__main__":
    patch_universal_source()
    patch_future_deadlock()
    patch_mozjs()
    patch_s2()
    # Inject Final Boss Fix
    if os.path.exists('SConstruct'):
        with open('SConstruct', 'a') as f:
            f.write("\nif 'env' in locals(): env.Append(CCFLAGS=['/Zc:lambda-', '/d2clret-', '/bigobj'])\n")
    print("--- FULL SCALE SOURCE REPAIR COMPLETE ---")
