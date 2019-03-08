import os
import shutil

# List *.cpp files in MAIN_FOLDER and build compile list

CLEAN_BEFORE = False
WITH_GRAPHICS = False

os.system("mkdir OUT_FOLDER")

file_list = filter(lambda f: f[-4:]=='.cpp', os.listdir("MAIN_FOLDER"))

for file in file_list:
    name = file[:-4]
    # REMOVE OLD main.cpp FROM SRC
    os.system("rm src/main.cpp")
    # REPLACE WITH NEW main.cpp
    shutil.copy("MAIN_FOLDER/" + file, "src/main.cpp")
    # CLEAN?
    if CLEAN_BEFORE:
        os.system("make clean")
    # COMPILE WITH OR WITHOUT GRAPHICS??
    if WITH_GRAPHICS:
        os.system("make graphics")
    else:
        os.system("make")
    # And now move to more practical nested folder!
    os.system("mkdir OUT_FOLDER/" + name)
    shutil.copy("MAIN_FOLDER/" + file,  "OUT_FOLDER/" + name + "/" + file)
    shutil.copy("bin/main.out", "OUT_FOLDER/" + name + "/" + name + ".out")
    
