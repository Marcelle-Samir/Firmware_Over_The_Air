import sys, site, shutil, os, platform

# make sure we are installing Chilkat for the correct
# Python version, the correct architecture (32-bit/64-bit/...),
# and the correct operating system (Linux, Windows, ...).
pyMajorVersion = sys.version_info.major
pyMinorVersion = sys.version_info.minor
pyVersion = str(pyMajorVersion) + "." + str(pyMinorVersion)
print("This Python version " + pyVersion)

# Make sure this Chilkat download is for the correct Python version.
if not os.path.exists(pyVersion):
    print("This Python version does not match the downloaded Chilkat module.\n")
    exit()

# system can be Linux, Darwin, Windows, SunOS
mySystem = platform.system()
print("This system: " + mySystem)

# machine can be x86_64, i686, i386, AMD64, sun4u, ia64, ppc64, armv6l
# sun4u is a SPARC, ia64 is Itanium, ppc64 is PowerPC
myMachine = platform.machine()
print("This processor: " + myMachine)

# coalesce all ARM architectures into "arm"
if "arm" in myMachine:
    myMachine = "arm"

if myMachine == "AMD64":
    myMachine = "x86_64"

if myMachine == "i386":
    myMachine = "i686"

# If this is a 64-bit Windows machine, skip the architecture check because
# 32-bit Python could be used.
skipArchCheck = False
if (mySystem == "Windows") and (myMachine == "x86_64"):
    skipArchCheck = True

# Make sure this Chilkat download is for the correct processor architecture
if not skipArchCheck:
    if not os.path.exists(myMachine):
        print("This processor architecture does not match the downloaded Chilkat module.\n")
        exit()

# Make sure this Chilkat download is for the correct operating system
if not os.path.exists(mySystem):
    print("This operating system does not match the downloaded Chilkat module.\n")
    exit()


bGlobalInstall = False

if len(sys.argv) > 1:
    opt = sys.argv[1]
    if opt == '-g':
        bGlobalInstall = True
        print("Installing globally...\n")


if bGlobalInstall:
    spList = site.getsitepackages()
    print(spList)
    spDir = spList[0]
    if not "site-packages" in spDir:
        # prefer the first directory having "site-packages" in the name.
        for d in spList:
            if "site-packages" in d:
                spDir = d
                break

else:
    spDir = site.getusersitepackages()

print("Installing to site-packages directory: " + spDir)

# if the spDir does not exist, create it.
if not os.path.exists(spDir):
    print("creating directory " + spDir)
    os.makedirs(spDir)

print("copying chilkat.py to " + spDir)
shutil.copy("chilkat.py",spDir)

if mySystem == "Windows":
    print("copying _chilkat.pyd to " + spDir)
    shutil.copy("_chilkat.pyd",spDir)
else:
    print("copying _chilkat.so to " + spDir)
    shutil.copy("_chilkat.so",spDir)

print("The Chilkat Python module is ready to be used.")
print("Success.")




