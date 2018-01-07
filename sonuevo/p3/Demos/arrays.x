const MAXIMO=10;

struct indices_notas {
	int indices<MAXIMO>;
};

struct respuesta_notas {
	float notas<MAXIMO>;
};

program ARRAYS {
	version ARRAYS_VER {
		respuesta_notas obtener_notas(indices_notas indices)=1;
	} = 1;
} = 0x30000003;
