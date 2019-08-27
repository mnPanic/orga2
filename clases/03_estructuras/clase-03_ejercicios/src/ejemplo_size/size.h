struct alumno {
	char* nombre;
	char comision;
	int dni;
};

struct alumno2 {
	char comision;
	char* nombre;
	int dni;
};

struct alumno3 {
	char* nombre;
	int dni;
	char comision;
} __attribute__((packed));

struct alumno4 {
	char* nombre;
	short comision;
};

struct alumno5 {
	short comision;
	char division;
};

enum tipos {
	tipo_auto, tipo_camion
};