import os
import sys

def patch_directory(target_dir):
    print(f"--- Patches applying to: {target_dir} ---")
    hijack_code = """
import os
import sys

# FORCE MSVC v141 ENVIRONMENT (PROPERLY INJECTED)
os.environ['CC'] = 'cl'
os.environ['CXX'] = 'cl'

try:
    import SCons.Environment
    orig_init = SCons.Environment.Base.__init__
    def new_init(self, *args, **kwargs):
        kwargs['ENV'] = os.environ
        kwargs['MSVC_VERSION'] = '14.1'
        kwargs['MSVC_USE_SCRIPT'] = False
        kwargs['TARGET_ARCH'] = 'x86_64'
        orig_init(self, *args, **kwargs)
        self['CC'] = 'cl'
        self['CXX'] = 'cl'
    SCons.Environment.Base.__init__ = new_init
except:
    pass
"""
    patched_count = 0
    if not os.path.exists(target_dir):
        print(f"Directory {target_dir} not found!")
        return

    for root, dirs, files in os.walk(target_dir):
        for file in files:
            if file in ['SConstruct', 'SConscript', 'Sconstruct']:
                path = os.path.join(root, file)
                try:
                    with open(path, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                    if 'FORCE MSVC v141 ENVIRONMENT' in content:
                        continue
                    with open(path, 'w', encoding='utf-8') as f:
                        f.write(hijack_code + "\n" + content)
                    patched_count += 1
                except:
                    pass
    print(f"Patched {patched_count} files in {target_dir}")

if __name__ == "__main__":
    # Patch both the current dir (robomongo) and its sibling (robo-shell)
    patch_directory('.')
    patch_directory('../robo-shell')
    print("--- GLOBAL HIJACK COMPLETE ---")
