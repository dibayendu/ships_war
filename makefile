###########################################################################
# Full Name			: Dibayendu Narayan Dey
# Student Number	: S 3224807
# Course			: COSC1186/1187 Interactive 3D and Graphics  animation
# Program			: BP096
###########################################################################

Assignment1: water.o obj.o texture_loader_mac.o perlin_noise.o terrain_perlin_noise.o perlin_noise_own.o skybox.o axes.o terrain.o waves.o ship.o cannon.o utility.o keys.o camera.o light.o collision_detector.o particle_system.o
	gcc -o water water.o texture_loader_mac.o perlin_noise.o terrain_perlin_noise.o obj.o perlin_noise_own.o skybox.o axes.o terrain.o waves.o ship.o cannon.o utility.o keys.o camera.o light.o collision_detector.o particle_system.o -framework Carbon -framework QuickTime -framework OpenGL -framework GLUT -std=c99 -m32

water.o: water.c water.h gl.h 
	gcc -c water.c -framework Carbon -framework QuickTime -framework OpenGL -framework GLUT -std=c99 -m32

texture_loader_mac.o: texture_loader_mac.c texture_loader_mac.h gl.h
	gcc -c texture_loader_mac.c -framework Carbon -framework QuickTime -framework OpenGL -framework GLUT -std=c99 -m32

skybox.o: skybox.c skybox.h gl.h
	gcc -c skybox.c -framework Carbon -framework QuickTime -framework OpenGL -framework GLUT -std=c99 -m32

axes.o: axes.c axes.h gl.h
	gcc -c axes.c -framework Carbon -framework QuickTime -framework OpenGL -framework GLUT -std=c99 -m32

terrain.o: terrain.c terrain.h
	gcc -c terrain.c -framework Carbon -framework QuickTime -framework OpenGL -framework GLUT -std=c99 -m32

waves.o: waves.c waves.h gl.h
	gcc -c waves.c -framework Carbon -framework QuickTime -framework OpenGL -framework GLUT -std=c99 -m32

ship.o: ship.c ship.h gl.h
	gcc -c ship.c -framework Carbon -framework QuickTime -framework OpenGL -framework GLUT -std=c99 -m32

cannon.o: cannon.c cannon.h
	gcc -c cannon.c -framework Carbon -framework QuickTime -framework OpenGL -framework GLUT -std=c99 -m32

keys.o: keys.c keys.h
	gcc -c keys.c -framework Carbon -framework QuickTime -framework OpenGL -framework GLUT -std=c99 -m32

utility.o: utility.c utility.h
	gcc -c utility.c -framework Carbon -framework QuickTime -framework OpenGL -framework GLUT -std=c99 -m32

camera.o: camera.c camera.h
	gcc -c camera.c -framework Carbon -framework QuickTime -framework OpenGL -framework GLUT -std=c99 -m32

light.o: light.c light.h
	gcc -c light.c -framework Carbon -framework QuickTime -framework OpenGL -framework GLUT -std=c99 -m32

collision_detector.o: collision_detector.h collision_detector.c
	gcc -c collision_detector.c -framework Carbon -framework QuickTime -framework OpenGL -framework GLUT -std=c99 -m32

particle_system.o: particle_system.c particle_system.h
	gcc -c particle_system.c -framework Carbon -framework QuickTime -framework OpenGL -framework GLUT -std=c99 -m32

perlin_noise.o: perlin_noise.c perlin_noise.h
	gcc -c perlin_noise.c -framework Carbon -framework QuickTime -framework OpenGL -framework GLUT -std=c99 -m32

terrain_perlin_noise.o: terrain_perlin_noise.c terrain_perlin_noise.h
	gcc -c terrain_perlin_noise.c -framework Carbon -framework QuickTime -framework OpenGL -framework GLUT -std=c99 -m32

perlin_noise_own.o: perlin_noise_own.c perlin_noise_own.h
	gcc -c perlin_noise_own.c -framework Carbon -framework QuickTime -framework OpenGL -framework GLUT -std=c99 -m32

obj.o: obj.c obj.h uthash.h
	gcc -c obj.c -framework Carbon -framework QuickTime -framework OpenGL -framework GLUT -std=c99 -m32

clean:
	rm -f *.o water core 3224807_assignment2.zip

run:
	./water water.jpg sand.jpg

archive:
	zip 3224807_assignment2.zip *.c *.h *.txt *.obj makefile makefile_mac -r images/
