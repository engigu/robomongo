import os
import sys

def patch_directory(target_dir):
    print(f"--- Patches applying to: {target_dir} ---")
    hijack_code = """
import os
import sys

# FORCE MSVC v143 ENVIRONMENT (PROPERLY INJECTED)
os.environ['CC'] = 'cl'
os.environ['CXX'] = 'cl'

try:
    import SCons.Environment
    orig_init = SCons.Environment.Base.__init__
    def new_init(self, *args, **kwargs):
        kwargs['ENV'] = os.environ
        kwargs['MSVC_VERSION'] = '14.3'
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
                    if 'FORCE MSVC v143 ENVIRONMENT' in content:
                        continue
                    with open(path, 'w', encoding='utf-8') as f:
                        f.write(hijack_code + "\n" + content)
                    patched_count += 1
                except:
                    pass
    print(f"Patched {patched_count} files in {target_dir}")

def patch_cpp_syntax(target_dir):
    print(f"--- Fixing CPP Syntax in: {target_dir} ---")
    fixed_count = 0
    for root, dirs, files in os.walk(target_dir):
        for file in files:
            if file == 's2cellid.cc':
                path = os.path.join(root, file)
                try:
                    with open(path, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                    
                    # Fix stdext::hash_value specialization for VS 2022
                    old_line = "template<> size_t stdext::hash_value<S2CellId>(const S2CellId &id) {"
                    if old_line in content:
                        new_content = content.replace(
                            old_line,
                            "namespace stdext { template<> size_t hash_value<S2CellId>(const S2CellId &id) {"
                        )
                        # We need to close the namespace. In s2cellid.cc, this is usually at the end of the block.
                        # For simplicity, we just add the closing brace if we did the replacement.
                        # Actually, s2cellid.cc usually has this at the very end of the file.
                        if "namespace stdext {" in new_content and not new_content.strip().endswith("}"):
                             new_content += "\n}\n"
                        
                        with open(path, 'w', encoding='utf-8') as f:
                            f.write(new_content)
                        fixed_count += 1
                        print(f"Fixed: {path}")
                except Exception as e:
                    print(f"Failed to fix {path}: {e}")
    print(f"Fixed {fixed_count} CPP files.")

if __name__ == "__main__":
    # Patch build environments
    patch_directory('.')
    patch_directory('../robo-shell')
    patch_directory('./robomongo-shell-roboshell-v4.2')
    # Fix CPP syntax for VS 2022
    patch_cpp_syntax('.')
    patch_cpp_syntax('../robo-shell')
    patch_cpp_syntax('./robomongo-shell-roboshell-v4.2')
    print("--- GLOBAL HIJACK COMPLETE ---")
