#pragma once

int add(int a, int b) {
	if (b == 0) return a;
	else return 1 + add(a, b - 1);
}