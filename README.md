# Furry YOB

rougelike game inspired by ultrakill and risk of rain 2

Build vcpkg(Windows)
```
vcpkg/bootstrap-vcpkg.bat
```

Build project
```
mkdir build
cmake -B build --preset vcpkg
cmake --build ./build --config Release
```

Run project
```
./build/Release/roguelike.exe
```

or move 'resources' folder to 'build/Release' and run executable from this folder