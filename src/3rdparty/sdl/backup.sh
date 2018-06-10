cd "${BASH_SOURCE%/*}" || exit

mkdir -p src/video/btos
cp -Rv ../SDL2-2.0.7/src/video/btos/*.c src/video/btos
cp -Rv ../SDL2-2.0.7/src/video/btos/*.h src/video/btos
cp -Rv ../SDL2-2.0.7/src/timer/btos/*.c src/timer/btos
cp -Rv ../SDL2-2.0.7/src/timer/btos/*.h src/timer/btos
cp ../SDL2-2.0.7/src/dynapi/SDL_dynapi.h .
cp ../SDL2-2.0.7/src/video/SDL_video.c .
cp ../SDL2-2.0.7/src/video/SDL_sysvideo.h .
cp -Rv ../SDL2-2.0.7/Makefile .
cp -Rv ../SDL2-2.0.7/include/SDL_config.h .
cp -Rv ../SDL2-2.0.7/include/SDL_config_btos.h .
