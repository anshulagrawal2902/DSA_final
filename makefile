main.o : main.c 
	gcc -c main.c

color.o : color.c 
	gcc -c color.c 

headerResolver.gch : headerResolver.h 
	gcc -c headerResolver.h 

readingBitmap.o : readingBitmap.c 
	gcc -c readingBitmap.c

# color.gch : color.h
# 	gcc -c color.h

OctNode.o : OctNode.c
	gcc -c OctNode.c

# OctNode.gch : OctNode.h
# 	gcc -c OctNode.h

Quantizer.o : Quantizer.c
	gcc -c Quantizer.c

# Quantizer.gch : Quantizer.h
# 	gcc -c Quantizer.h

output : main.o color.o OctNode.o Quantizer.o readingBitmap.o
	gcc main.o color.o OctNode.o Quantizer.o  readingBitmap.o -o output

