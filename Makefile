main:
	cmake --build build --target main
	cmake --build build --target stick_checkout
	cmake --build build --target button_checkout

app:
	cmake --build build
