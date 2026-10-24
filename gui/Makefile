SRCS = $(shell find . -name '*.cpp')

LOCAL_PREFIX = $(HOME)/.local
SDL_TTF_VERSION = release-2.20.1
SDL_TTF_SOURCE = $(HOME)/src/SDL_ttf

DEBUGFLAGS = -g
LIBS = $(shell pkg-config --cflags --libs sdl2 SDL2_ttf) -pthread

run: check-sdl-ttf
	g++ $(SRCS) -o client $(LIBS)
	# ./client 127.0.0.1

check-sdl-ttf:
	@if ! pkg-config --exists SDL2_ttf; then \
		echo "SDL2_ttf n'est pas installé."; \
		$(MAKE) install-sdl-ttf || exit 1; \
	fi

install-sdl-ttf:
	@echo "Installation locale de SDL2_ttf..."

	@mkdir -p $(HOME)/src

	@if [ ! -d "$(SDL_TTF_SOURCE)/.git" ]; then \
		git clone --depth 1 --branch $(SDL_TTF_VERSION) \
			https://github.com/libsdl-org/SDL_ttf.git \
			$(SDL_TTF_SOURCE) || exit 1; \
	fi

	cmake -S $(SDL_TTF_SOURCE) -B $(SDL_TTF_SOURCE)/build \
		-DCMAKE_INSTALL_PREFIX=$(LOCAL_PREFIX) \
		-DSDL2TTF_VENDORED=OFF

	cmake --build $(SDL_TTF_SOURCE)/build -j2

	cmake --install $(SDL_TTF_SOURCE)/build

	@echo "Installation terminée."

debug: check-sdl-ttf
	g++ $(DEBUGFLAGS) $(SRCS) -o client $(LIBS)
	valgrind --leak-check=full --show-leak-kinds=all ./client 127.0.0.1 2> val.txt

clean:
	rm -f ./client
