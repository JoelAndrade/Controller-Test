main:
	cmake --build build --target main

app:
	cmake --build build

test:
	g++ main.cpp -o myapp \
		-I"D:\Qt\6.11.1\mingw_64\include" \
		-I"D:\Qt\6.11.1\mingw_64\include\QtWidgets" \
		-L"D:\Qt\6.11.1\mingw_64\lib" \
		-lQt6Widgets -lQt6Gui -lQt6Core