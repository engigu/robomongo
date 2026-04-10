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
                    
                    if new_content != content:
                        with open(path, 'w', encoding='utf-8') as f:
                            f.write(new_content)
                        print(f"Patched: {path}")
                except Exception as e:
                    print(f"Failed to patch {path}: {e}")

def patch_mozjs():
    print("--- Patching mozjs StoreBuffer.h ---")
    path = 'src/third_party/mozjs-60/extract/js/src/gc/StoreBuffer.h'
    if not os.path.exists(path):
        print(f"Warning: {path} not found. Skipping.")
        return
    
    try:
        with open(path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        # Proper regex to fix unnamed structs (C7626 error on VS 2022)
        # Finds: typedef struct { ... } Name;
        # Replaces with: struct Name { ... };
        new_content = re.sub(r'typedef struct \{(.*?)\} (\w+);', r'struct \2 {\1};', content, flags=re.DOTALL)
        
        if new_content != content:
            with open(path, 'w', encoding='utf-8') as f:
                f.write(new_content)
            print(f"Patched: {path}")
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
            
        # Fix stdext::hash_value compatibility issue
        new_content = content.replace('size_t stdext::hash_value', 'size_t hash_value')
        
        if new_content != content:
            with open(path, 'w', encoding='utf-8') as f:
                f.write(new_content)
            print(f"Patched: {path}")
    except Exception as e:
        print(f"Failed to patch S2: {e}")

if __name__ == "__main__":
    # We expect to be run from the robo-shell root directory
    patch_scons()
    patch_mozjs()
    patch_s2()
    print("--- All patches applied successfully ---")
