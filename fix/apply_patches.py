import os
import re
import sys

def patch_scons():
    print("--- Patching SCons (Nuclear Option: /Od and if constexpr) ---")
    for root, dirs, files in os.walk('.'):
        for file in files:
            if file in ['SConstruct', 'SConscript']:
                path = os.path.join(root, file)
                try:
                    with open(path, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                    
                    # 1. Force native "if constexpr" to help binary branch deduction
                    new_content = content.replace('IF_CONSTEXPR', 'if constexpr')
                    
                    # 2. Inherit system environment
                    new_content = new_content.replace('env = Environment(', 'env = Environment(ENV = os.environ, ')
                    
                    # 3. Nuclear downgrade: Disable all optimizations (/Od)
                    new_content = new_content.replace('/O2', '/Od').replace('/O1', '/Od').replace('/Ox', '/Od')
                    
                    # 4. Strip high-pressure flags that trigger ICE
                    for flag in ['/Gw', '/Gy', '/Zc:inline']:
                        new_content = new_content.replace(f"'{flag}'", "''").replace(f'"{flag}"', '""')
                    
                    # 5. Disable /WX and enable /permissive
                    new_content = new_content.replace('/WX', '/WX-')
                    new_content = new_content.replace('/permissive-', '/permissive')
                    
                    if new_content != content:
                        with open(path, 'w', encoding='utf-8') as f:
                            f.write(new_content)
                        print(f"Patched: {path}")
                except Exception as e:
                    print(f"Failed to patch {path}: {e}")
    
    # 6. Inject the most stable flags possible
    if os.path.exists('SConstruct'):
        try:
            with open('SConstruct', 'a') as f:
                f.write("\n# Final Boss Fix for VS 2022 ICE\n")
                f.write("if 'env' in locals(): env.Append(CCFLAGS=['/Zc:lambda-', '/d2clret-', '/bigobj', '/std:c++17'])\n")
        except: pass

def patch_future():
    # Reverting the comma induction hack as it didn't help, we rely on /Od and if constexpr now
    path = 'src/mongo/util/future_impl.h'
    if not os.path.exists(path): return
    try:
        with open(path, 'r', encoding='utf-8') as f: content = f.read()
        new_content = content.replace('(void)0, notReady()', 'notReady()') # Cleanup
        if new_content != content:
            with open(path, 'w', encoding='utf-8') as f: f.write(new_content)
    except: pass

def patch_mozjs():
    path = 'src/third_party/mozjs-60/extract/js/src/gc/StoreBuffer.h'
    if not os.path.exists(path): return
    try:
        with open(path, 'r', encoding='utf-8') as f: content = f.read()
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
                    if count == 0: brace_end = i; break
            if brace_end == -1: break
            suffix_match = re.match(r'\s*(\w+);', new_content[brace_end+1:])
            if suffix_match:
                name = suffix_match.group(1); body = new_content[brace_start+1:brace_end]
                new_content = new_content[:start_idx] + f"struct {name} {{{body}}};" + new_content[brace_end+1+suffix_match.end():]
            else: new_content = new_content[:start_idx] + "STRUCT_PROCESSED" + new_content[start_idx+6:]
        new_content = new_content.replace("STRUCT_PROCESSED", "typedef struct ")
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
    patch_scons()
    patch_future()
    patch_mozjs()
    patch_s2()
    print("--- Nuclear-option patches applied ---")
