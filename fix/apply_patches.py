import os
import sys

def patch_scons_files():
    print("--- INDISCRIMINATE SCONS HIJACKING (v141) ---")
    hijack_code = """
import os
import sys

# FORCE MSVC v141 ENVIRONMENT
os.environ['CC'] = 'cl'
os.environ['CXX'] = 'cl'

# Monkey-patching SCons if necessary
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
    # Find ALL SCons related files and prepend the code
    patched_count = 0
    for root, dirs, files in os.walk('.'):
        for file in files:
            if file in ['SConstruct', 'SConscript']:
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
    print(f"Patched {patched_count} SCons files.")

if __name__ == "__main__":
    patch_scons_files()
    print("--- HIJACK COMPLETE ---")
