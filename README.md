# CONSTANT STRAIN TRIANGLE - FINITE ELEMENT METHOD IN C++
## Author - GABRIEL CORREIA DA SILVA

This is a program for finite elements of the type CST (constant strain triangle)

### HOW TO USE IT?

#### Open the file " ENTRADA.txt";
    *there you can edit all the dimentions and nodes of your element mesh*
1. IN MATERIALS
    IN MATERIALS
    MATERIAIS (MATERIALS)
    ``N E POISSON``
        WHERE: 
            - N: MATERIAL INDEX;
            - E: YOUNG MODULE;
            - POISSON: POISSON;
    *One material per line*

2. IN COORDINATES
    COORDENADAS (COORDINATES)
    ``N X Y VINX VINY UX UY FX FY``  
        WHERE:
         - N: NODE INDEX;
         - X and Y: COORDINATES;
         - VINX and VINY: LINKAGE IN X and Y;
         - UX and UY: DISPLACEMENT IN X and Y;
         - FX and FY: LOADING IN X and Y;
         *One node per line*

3. IN CONNECTIVITY
    CONECTIVIDADE (CONNECTIVITY)
    ``N NO0 NO1 N02 EP MAT``
        WHERE:
         - N: ELEMENT INDEX;  
         - NO0, NO1, NO2: 3 NODES OF ELEMENT;
         - EP: EPT OR EPD;
         - MAT: MATERIAL INDEX;
         *One element per line*

##### OBS:
    THIS IS A PROTOTYPE AND MIGHT HAVE SOME BUGS
    FEEL FREE TO MAKE CHANGES AND USE IT IN YOUR PROJECT
