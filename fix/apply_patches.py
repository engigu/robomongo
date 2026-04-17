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
        # COMPATIBILITY HACKS FOR MOZJS-60 AND VS 2022 - FORCE PREPEND FOR PRIORITY
        self.Prepend(CPPDEFINES=[
            '_HAS_STD_BYTE=0', 
            '_HAS_AUTO_PTR_ETC=1',
            '_HAS_OLD_IOSTREAMS_MEMBERS=1',
            '_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS', 
            '_SILENCE_ALL_CXX20_DEPRECATION_WARNINGS'
        ])
        # Disable /WX (Warnings as Errors) and force C++14 standard
        self.Prepend(CCFLAGS=['/Zc:__cplusplus', '/D_HAS_STD_BYTE=0', '/WX-', '/std:c++14', '/wd4819', '/wd4005', '/wd4996', '/wd5033'])
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
    if not os.path.exists(target_dir):
        return

    for root, dirs, files in os.walk(target_dir):
        for file in files:
            path = os.path.join(root, file)
            
            # 1. Fix s2cellid.cc (stdext::hash_value specialization)
            if file == 's2cellid.cc':
                try:
                    with open(path, 'r', encoding='utf-8', errors='ignore') as f:
                        lines = f.readlines()
                    new_lines = []
                    found = False
                    for line in lines:
                        if "template<> size_t stdext::hash_value<S2CellId>(const S2CellId" in line:
                            new_lines.append("namespace stdext {\n")
                            new_lines.append("    inline size_t hash_value(const S2CellId& id) {\n")
                            found = True
                        elif found and line.strip() == "}":
                            new_lines.append("    }\n}\n")
                            found = False
                        else:
                            new_lines.append(line)
                    with open(path, 'w', encoding='utf-8') as f:
                        f.writelines(new_lines)
                    fixed_count += 1
                    print(f"Fixed (S2 Hash): {path}")
                except: pass

            # 2. Fix UUID::fromCDR brace initialization
            if file.endswith('.cpp') or file.endswith('.h'):
                try:
                    with open(path, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                    if 'UUID::fromCDR({' in content:
                        new_content = content.replace('UUID::fromCDR({', 'UUID::fromCDR(ConstDataRange{')
                        with open(path, 'w', encoding='utf-8') as f:
                            f.write(new_content)
                        fixed_count += 1
                        print(f"Fixed (UUID Brace): {path}")
                except: pass
                
    print(f"Fixed {fixed_count} CPP syntax issues.")

if __name__ == "__main__":
    patch_directory('.')
    patch_directory('../robo-shell')
    patch_directory('./robo-shell')
    patch_directory('./robomongo-shell-roboshell-v4.2')
    
    patch_cpp_syntax('.')
    patch_cpp_syntax('../robo-shell')
    patch_cpp_syntax('./robo-shell')
    patch_cpp_syntax('./robomongo-shell-roboshell-v4.2')
    print("--- GLOBAL HIJACK COMPLETE ---")
