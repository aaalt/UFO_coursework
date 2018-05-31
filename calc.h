#define O printf
#define SZ sizeof
#define R return
#define VER "\u2503"
#define HOR "\u2501"
#define CRS "\u254b"
#define CLP "\u253b"
#define DO(n,x) {int i=0,_i=(n);for(;i<_i;++i){x;}}
#define BAR(s1,s2) {O("%s",(s1));DO(7,O("%s",(s2)));}

//	структура содержит в себе цвет и число
typedef struct Rod {
	int col;
	int num;
} rod;

