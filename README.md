# FreeGLUT for PS Vita
FreeGLUT library ported to PS Vita using [Pigs-In-A-Blanket](https://github.com/SonicMastr/Pigs-In-A-Blanket).

## To compile for DolceSDK:
First obtain [PIB.](https://github.com/SonicMastr/Pigs-In-A-Blanket)
Then,
```
mkdir build
cd build
cmake .. -DVITA=1
make -j8
make install
```
## To-Do
The controls need work as I didn't try porting a glut game to see how the controls are used.

## Credits:
- FreeGLUT contributors
- FMudanyali
- dots-tb
- SonicMastr
- GrapheneCt
- Team CBPS
