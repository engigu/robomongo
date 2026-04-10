import os
import re
import sys

def patch_scons_v141_env():
    print("--- Mandatory SCons Environment Sync (v141 Target) ---")
    for root, dirs, files in os.walk('.'):
        for file in files:
            if file in ['SConstruct', 'SConscript']:
                path = os.path.join(root, file)
                try:
                    with open(path, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                    
                    # Force environment inheritance and lock MSVC version to 14.1
                    new_content = re.sub(r'Environment\s*\(', "Environment(ENV = os.environ, MSVC_VERSION='14.1', TARGET_ARCH='x86_64', ", content)
                    
                    # Fix the literal $CC bug often found in these forks
                    new_content = new_content.replace("env['CXX'] = '$CC'", "env['CXX'] = 'cl'")
                    new_content = new_content.replace('env["CXX"] = "$CC"', 'env["CXX"] = "cl"')
                    
                    if new_content != content:
                        with open(path, 'w', encoding='utf-8') as f:
                            f.write(new_content)
                except: pass

if __name__ == "__main__":
    patch_scons_v141_env()
    print("--- v141 ENVIRONMENT SYNC COMPLETE ---")
