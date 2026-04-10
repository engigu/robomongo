import os
import sys

def force_hijack_scons():
    print("--- Force Hijacking SCons Environment (The Nuclear Way) ---")
    sconstruct_path = 'SConstruct'
    if not os.path.exists(sconstruct_path):
        # Find it if it's in a subdirectory
        for root, dirs, files in os.walk('.'):
            if 'SConstruct' in files:
                sconstruct_path = os.path.join(root, 'SConstruct')
                break
    
    if os.path.exists(sconstruct_path):
        with open(sconstruct_path, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
        
        # Prepend our massive environment sync block
        hijack_code = """
import os
import SCons.Util

# Aggressive Environment Sync
def sync_env(env):
    for key in ['PATH', 'LIB', 'INCLUDE', 'LIBPATH']:
        if key in os.environ:
            env['ENV'][key] = os.environ[key]
    env['CC'] = 'cl'
    env['CXX'] = 'cl'
    env['MSVC_VERSION'] = '14.1'
    env['MSVC_USE_SCRIPT'] = False

# We will inject a call to this function later or monkey-patch the Environment
"""
        # A more direct way: replace the creation logic
        new_content = content.replace('env = Environment(', 'env_orig = Environment(')
        # Add a wrapper
        new_content = hijack_code + new_content
        new_content += """
if 'env' in locals():
    sync_env(env)
elif 'env_orig' in locals():
    env = env_orig
    sync_env(env)
"""
        with open(sconstruct_path, 'w', encoding='utf-8') as f:
            f.write(new_content)
        print(f"Successfully hijacked {sconstruct_path}")

if __name__ == "__main__":
    force_hijack_scons()
    print("--- HIJACK COMPLETE ---")
