#ifndef MODEL_H
#define MODEL_H

//-----------------------------------------------------
// <name>   
// <desc>   位置ベクトル
// <memo>   
//-----------------------------------------------------
typedef struct Vector 
{
    float x;
    float y;
    float z;
}Vector;

Vector* Vector_init0(Vector* v);
Vector* Vector_set(Vector* v, float, float, float);

typedef struct Vector2d
{
    float x;
    float y;
}Vector2d;

Vector2d* Vector2d_init0(Vector2d* v);
Vector2d* Vector2d_set(Vector2d* v, float, float);
float Vector2d_getSCRY2OGLY(Vector2d* v);


//-----------------------------------------------------
// <name>   
// <desc>   頂点
// <memo>   頂点は、位置ベクトルを継承している
//-----------------------------------------------------
typedef struct Vertex
{
    Vector m_pos;
    Vector m_normal;

    int m_used; //使用回数

}Vertex;

Vertex* Vertex_new(int size);
void Vertex_delete(Vertex* p);

Vertex* Vertex_init0(Vertex* );
Vertex* Vertex_set(Vertex* v, float, float, float);

//---------------------------------------------------
// <name>   
// <desc>   ひとつの面
// <memo>   triangleである場合、order, uvの末尾値は0
//---------------------------------------------------
typedef struct Face
{
    int type;           //triangle / quad
    int index[4];       //面を構成する頂点番号配列

    Vector normal;     //面の法線ベクトル

    float uv[4][2];       //テクスチャ座標

    int m_visible;

}Face;

Face* Face_new(int size);
void Face_delete(Face* p);


//---------------------------------------------------
// <name>   
// <desc>   辺(エッジ)
// <memo>   
//---------------------------------------------------
typedef struct Edge
{
    int vertexindex[2];
    int triangleindex[2];
}Edge;

//-----------------------------------------------
// <name>   
// <desc>   3D object を表す
// <memo>   頂点、
//          面(三角形、および四角形)
//-----------------------------------------------
typedef struct Model
{
	char name[256];
    int m_num_vertices;     //頂点数
    int m_num_faces;        //面数
    int m_num_edges;        //辺数

    Vertex* m_vertices;    //頂点データ
    Face*   m_faces;       //面データ
    Edge*   m_edges;       //辺データ

	int m_tex_id;			//テクスチャID

}Model;


enum GRID_TYPE {
	GRID_TYPE_BLOCK = 0, 
	GRID_TYPE_ALPHABET, 
	GRID_TYPE_SPACE,
	GRID_TYPE_LOG, 
	GRID_TYPE_CURSOR,	//カーソルがある
};

enum LOG_TYPE {
	LOG_TYPE_NONE = 0, 
};

//TODO: 別の場所に移動
typedef struct GridItem {
	int type;		//ブロック、アルファベット、空白
	int log_value;	//ログのタイプ
	char cursor_char;	//グリッドに何らかの文字のカーソルがある場合、その文字を示す.大文字、小文字があり得る
	Vector pos;		//OpenGL座標
	Vector center;
} GridItem;




Model* Model_new(const char* _name);
void Model_delete(Model* p);

int Model_set_face_normal(Model* p);
int Model_set_vertex_normal(Model* p);
int Model_set_edge_list(Model* p);
Model* Model_load(Model* p, const char* filepath, const int tex_id);

int Model_get_num_vertices(Model* p);
int Model_get_num_faces(Model* p);
int Model_get_num_edges(Model* p);

void Model_render(Model* p);

#endif


//eof
