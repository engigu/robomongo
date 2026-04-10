import os
import re
import sys

def patch_minimal():
    print("--- Minimal Patch (Zero-Test) ---")
    for root, dirs, files in os.walk('.'):
        for file in files:
            if file in ['SConstruct', 'SConscript']:
                path = os.path.join(root, file)
                try:
                    with open(path, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                    
                    # Only keeping the absolute bare minimum: ENV inheritance
                    # Without this, SCons can't find ANY compiler even if it's installed.
                    new_content = content.replace('env = Environment(', 'env = Environment(ENV = os.environ, ')
                    
                    if new_content != content:
                        with open(path, 'w', encoding='utf-8') as f:
                            f.write(new_content)
                except: pass

if __name__ == "__main__":
    patch_minimal()
    print("--- Patches Removed, Environment Inheritance Only ---")
