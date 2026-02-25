.PHONY: build

build:
	cmake --build build

run:
	wine build/GestionBanque.exe

dev:
	make build
	make run

teacher:
	wine exes/C21_TP2_original_AThiboutot.exe
