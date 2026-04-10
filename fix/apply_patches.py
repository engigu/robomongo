import os
import re
import sys

def patch_scons_standard():
    print("--- Patching SCons for Standard v141 Build ---")
    for root, dirs, files in os.walk('.'):
        for file in files:
            if file in ['SConstruct', 'SConscript']:
                path = os.path.join(root, file)
                try:
                    with open(path, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                    
                    # Ensure environment inheritance
                    new_content = content.replace('env = Environment(', 'env = Environment(ENV = os.environ, ')
                    
                    # Disable /WX (Warnings as Errors) for safety
                    new_content = new_content.replace('/WX', '/WX-')
                    
                    if new_content != content:
                        with open(path, 'w', encoding='utf-8') as f:
                            f.write(new_content)
                except: pass

def patch_mozjs():
    path = 'src/third_party/mozjs-60/extract/js/src/gc/StoreBuffer.h'
    if not os.path.exists(path): return
    try:
        with open(path, 'r', encoding='utf-8', errors='ignore') as f: content = f.read()
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

def patch_s2():
    path = 'src/third_party/s2/s2cellid.cc'
    if not os.path.exists(path): return
    try:
        with open(path, 'r', encoding='utf-8', errors='ignore') as f: content = f.read()
        if 'namespace stdext' not in content:
            content = "\nnamespace stdext { template<typename T> size_t hash_value(const T&); }\n" + content
            with open(path, 'w', encoding='utf-8') as f: f.write(content)
    except: pass

if __name__ == "__main__":
    patch_scons_standard()
    patch_mozjs()
    patch_s2()
    print("--- v141 NATIVE PATCH COMPLETE ---")
