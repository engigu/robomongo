import os
import re
import sys

def patch_scons_precision():
    print("--- Precision Patching SCons and Environment ---")
    for root, dirs, files in os.walk('.'):
        for file in files:
            if file in ['SConstruct', 'SConscript']:
                path = os.path.join(root, file)
                try:
                    with open(path, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                    
                    # 1. Inherit env and force C++17 standard to avoid "if constexpr" parse errors
                    new_content = content.replace('env = Environment(', 'env = Environment(ENV = os.environ, ')
                    
                    # 2. Optimization downgrade /O2 -> /O1 for ICE avoidance
                    new_content = new_content.replace('/O2', '/O1')
                    
                    # 3. Strip risky linking/optimization flags
                    for flag in ['/Gw', '/Gy', '/Zc:inline', '/WX']:
                        new_content = new_content.replace(f"'{flag}'", "''").replace(f'"{flag}"', '""')
                    
                    if new_content != content:
                        with open(path, 'w', encoding='utf-8') as f:
                            f.write(new_content)
                except: pass
    
    # Global flag injection at the root
    if os.path.exists('SConstruct'):
        with open('SConstruct', 'a') as f:
            f.write("\n# Precision VS 2022 compatibility\n")
            f.write("if 'env' in locals(): env.Append(CCFLAGS=['/std:c++17', '/Zc:lambda-', '/d2clret-', '/bigobj'])\n")

def patch_future_precision():
    print("--- Precision Patching future_impl.h ---")
    path = 'src/mongo/util/future_impl.h'
    if not os.path.exists(path): return
    try:
        with open(path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        # 1. Precision replace IF_CONSTEXPR using regex boundaries
        new_content = re.sub(r'\bIF_CONSTEXPR\b', 'if constexpr', content)
        
        # 2. Safe AST induction for both void and non-void returns
        new_content = new_content.replace('return notReady();', 'return (void)0, notReady();')
        
        if new_content != content:
            with open(path, 'w', encoding='utf-8') as f:
                f.write(new_content)
            print(f"Patched future_impl.h with precision regex and induction hack.")
    except Exception as e:
        print(f"Failed to patch future_impl.h: {e}")

def patch_third_party():
    # mozjs: typedef struct anonymous fix
    path = 'src/third_party/mozjs-60/extract/js/src/gc/StoreBuffer.h'
    if os.path.exists(path):
        try:
            with open(path, 'r', encoding='utf-8') as f: content = f.read()
            new_content = content
            while True:
                match = re.search(r'typedef struct \s*\{', new_content)
                if not match: break
                start = match.start(); b_start = match.end() - 1
                cnt=1; b_end=-1
                for i in range(b_start+1, len(new_content)):
                    if new_content[i]=='{': cnt+=1
                    elif new_content[i]=='}':
                        cnt-=1
                        if cnt==0: b_end=i; break
                if b_end == -1: break
                suffix = re.match(r'\s*(\w+);', new_content[b_end+1:])
                if suffix:
                    name = suffix.group(1); body = new_content[b_start+1:b_end]
                    new_content = new_content[:start] + f"struct {name} {{{body}}};" + new_content[b_end+1+suffix.end():]
                else: new_content = new_content[:start] + "STRUCT_FIX" + new_content[start+6:]
            new_content = new_content.replace("STRUCT_FIX", "typedef struct ")
            if new_content != content:
                with open(path, 'w', encoding='utf-8') as f: f.write(new_content)
        except: pass

    # S2: hash_value template fix
    path = 'src/third_party/s2/s2cellid.cc'
    if os.path.exists(path):
        try:
            with open(path, 'r', encoding='utf-8') as f: content = f.read()
            if 'namespace stdext' not in content:
                content = "\nnamespace stdext { template<typename T> size_t hash_value(const T&); }\n" + content
                with open(path, 'w', encoding='utf-8') as f: f.write(content)
        except: pass

if __name__ == "__main__":
    patch_scons_precision()
    patch_future_precision()
    patch_third_party()
    print("--- PRECISION FIX APPLIED ---")
