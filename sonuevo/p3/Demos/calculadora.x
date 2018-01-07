struct entrada {
	int arg1;
	int arg2;
};

program CALCULADORA {
	version CALCULADORA_VER {
		int sumar(entrada) = 1;
		int restar(entrada) = 2;
		int multiplicar(entrada) = 3;
		int dividir(entrada) = 4;
	} = 1;
} = 0x30000001;