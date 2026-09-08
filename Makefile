main:
	cmake --build build --target main
	cmake --build build --target stick_checkout

app:
	cmake --build build
