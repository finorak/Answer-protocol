SRCS = $(shell find . -name '*.cpp')

LOCAL_PREFIX = $(HOME)/.local
SDL_TTF_VERSION = release-2.20.1
SDL_TTF_SOURCE = $(HOME)/src/SDL_ttf

SERVER_IP ?= 

DEBUGFLAGS = -g -fsanitize=thread
LIBS = $(shell pkg-config --cflags --libs sdl2 SDL2_ttf) -pthread

CPP_LINT = $(HOME)/.venv/bin/cpplint

NAME = client

.PHONY: all run-client check-sdl-ttf install-sdl-ttf \
        install-cpplint lint clean re

all: check-sdl-ttf $(NAME)

$(NAME): $(SRCS)
	g++ $(SRCS) -o $(NAME) -I.. $(LIBS)

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

install-cpplint:
	python3 -m venv $(HOME)/.venv
	$(HOME)/.venv/bin/pip install cpplint

lint:
	@if [ ! -x "$(CPP_LINT)" ]; then \
		$(MAKE) install-cpplint || exit 1; \
	fi
	find . -type f -name "*.cpp" -print0 | xargs -0 $(CPP_LINT)

clean:
	rm -rf ./client $(HOME)/.venv

re: clean all
