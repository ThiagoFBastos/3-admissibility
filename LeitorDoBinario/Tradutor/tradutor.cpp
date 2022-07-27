#include <iostream>
#include <fstream>
#include <cerrno>
#include <cstring>
#include "constants.hpp"

using namespace std;

struct Info {
	char matriz[MAX_E];
	int diam;
	int dT;
	int sigma;
};

int main(int argc, char* argv[]) {
	if(argc < 2) {
		printf("use: ./tradutor <arquivo>\n");
		return 0;
	}
	
	FILE *in = fopen(argv[1], "rb");

	if(!in) {
		printf("o arquivo %s não foi aberto: %s\n", argv[3], strerror(errno));
		return 0;
	}

	int n, matriz[MAX_E];
	Info info;

	fread(&n, sizeof(int), 1, in);
	
	while(true) {
		fread(&info, sizeof(Info), 1, in);

		if(feof(in)) break;

		memset(matriz, 0, sizeof(int) * n * n);

		printf("matriz de adjacencias:\n");
		for(int u = 0, a = 0; u < n; ++u)
		for(int v = u + 1; v < n; ++v)
			matriz[u * n + v] = matriz[v * n + u] = info.matriz[a++];

		for(int u = 0; u < n; ++u) {
			for(int v = 0; v < n; ++v) putchar(matriz[u * n + v] + '0');
			putchar('\n');
		}

		printf("dT(G) = %d\n", info.dT);
		printf("diam(G) = %d\n", info.diam);
		printf("\\sigma(G) = %d\n\n", info.sigma);
	}
	
	fclose(in);

	return 0;
}
