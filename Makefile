APP = app

all: build


.PHONY: build run release clean
	
build:
	@./scripts/build_debug.sh

run: build
	@./build/debug/bin/app -d

release:
	@./scripts/build_release.sh

test:
	@./build/debug/bin/test_$(APP)


format:
	@find ./src/ -iname *.h -o -iname *.cpp | xargs clang-format -i
	@find ./tests/ -iname *.h -o -iname *.cpp | xargs clang-format -i

clean:
	@rm -rf build
