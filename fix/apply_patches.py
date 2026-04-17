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
                        lines = f.readlines()
                    
                    new_lines = []
                    found = False
                    for line in lines:
                        # Find the problematic specialization
                        if "template<> size_t stdext::hash_value<S2CellId>(const S2CellId" in line:
                            # Replace with a simpler overload that works in VS 2022
                            new_lines.append("namespace stdext {\n")
                            new_lines.append("    inline size_t hash_value(const S2CellId& id) {\n")
                            found = True
                        elif found and line.strip() == "}":
                            new_lines.append("    }\n")
                            new_lines.append("}\n")
                            found = False
                        else:
                            new_lines.append(line)
                    
                    if found: # Fallback if closing brace wasn't found exactly as expected
                         new_lines.append("    }\n}\n")

                    with open(path, 'w', encoding='utf-8') as f:
                        f.writelines(new_lines)
                    fixed_count += 1
                    print(f"Fixed (Overload Style): {path}")
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
