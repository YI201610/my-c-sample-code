#include "Model.h"
#include "Math.h"
#include "TaskManager.h"
#include "GI.h"

extern cBind_GlobalAppData g_app_data;

//extern GI g_gi;

//ベクトル
//Vector_init0 {{{
Vector* Vector_init0(Vector* v)
{
	v->x = 0;
	v->y = 0;
	v->z = 0;

	return v;
}
//}}}
//Vector_set {{{
Vector* Vector_set(Vector* v, float _x, float _y, float _z)
{
    v->x = _x; 
    v->y = _y; 
    v->z = _z;

	return v;
}
//}}}
//Vector2d_init0 {{{
Vector2d* Vector2d_init0(Vector2d* v)
{
	v->x = 0;
	v->y = 0;

	return v;
}
//}}}
//Vector2d_set {{{
Vector2d* Vector2d_set(Vector2d* v, float _x, float _y)
{
    v->x = _x; 
	
//    v->y = _y;   こっちがただしい
//	iPhone3G用に小細工
//	v->y = 480-64-_y;
    v->y = g_app_data.nTotalOglOffsetY - 64 - _y;

	return v;
}
//}}}

//OpenGLのウィンドウ座標形が、左下原点なのを考慮した、タッチ衝突判定比較用のy座標値を返す関数
float Vector2d_getSCRY2OGLY(Vector2d* v){
//	return 480-64- v->y;
	return g_app_data.nTotalOglOffsetY-64- v->y;
}

//頂点
//Vertex_new {{{
/**
 *	Constructor
 *
 *
 */
Vertex* Vertex_new(int n)
{
	Vertex* this;
	this = (Vertex*)calloc(n, sizeof(Vertex));
	return this;
}
//}}}
//Vertex_delete {{{
/**
 *	Desctructor
 *
 *
 */
void Vertex_delete(Vertex* this)
{
	free(this);
	this = NULL;
}
//}}}
//Vertex_init0 {{{
Vertex* Vertex_init0(Vertex* v)
{
	v->m_pos.x = 0;
	v->m_pos.y = 0;
	v->m_pos.z = 0;

	v->m_normal.x = 0;
	v->m_normal.y = 0;
	v->m_normal.z = 0;

	v->m_used = 0;

	return v;
}
//}}}
//Vertex_set {{{
Vertex* Vertex_set(Vertex* v, float _x, float _y, float _z)
{
    v->m_pos.x = _x; 
    v->m_pos.y = _y; 
    v->m_pos.z = _z;

	return v;
}
//}}}

//面
//Face_new {{{
/**
 *	Constructor
 *
 *
 */
Face* Face_new(int n)
{
	Face* this;
	this = (Face*)calloc(n, sizeof(Face));
	return this;
}
//}}}
//Face_delete {{{
/**
 *	Desctructor
 *
 *
 */
void Face_delete(Face* this)
{
	free(this);
	this = NULL;
}
//}}}

//Model
//Model_new {{{
/**
 *	Constructor
 *
 *
 */
Model* Model_new(const char* _name)
{
	Model* this;
	this = (Model*)calloc(1, sizeof(Model));

    this->m_vertices = NULL;
    this->m_faces = NULL;       
    this->m_edges = NULL;       
	
	sprintf(this->name, "%s", _name);
	dp("O: model[%s]", this->name);

	return this;
}
//}}}
//Model_delete {{{
/**
 *	Desctructor
 *
 *
 */
void Model_delete(Model* this)
{
	if(this->m_vertices != NULL){
		Vertex_delete(this->m_vertices);
	}
    if(this->m_faces != NULL){
		Face_delete(this->m_faces);
	}
	if(this->m_edges != NULL){
		free(this->m_edges);
	}

	dp("X: model[%s]", this->name);

	free(this);
	this = NULL;
}
//}}}

//Model_set_face_normal {{{
//全ての面の法線ベクトルを求める
int Model_set_face_normal(Model* p)
{
	int i;

    for(i=0; i < p->m_num_faces; i++)
    {
    	Vector v1, v2, v3, v4;
        Vector ab, ac, n;

        if(p->m_faces[i].type == 3)    //triangle
        {
			Vector_set(&v1, 
					p->m_vertices[p->m_faces[i].index[0]].m_pos.x, 
					p->m_vertices[p->m_faces[i].index[0]].m_pos.y, 
					p->m_vertices[p->m_faces[i].index[0]].m_pos.z); 

			Vector_set(&v2, 
					p->m_vertices[p->m_faces[i].index[1]].m_pos.x, 
					p->m_vertices[p->m_faces[i].index[1]].m_pos.y, 
					p->m_vertices[p->m_faces[i].index[1]].m_pos.z); 

			Vector_set(&v3, 
					p->m_vertices[p->m_faces[i].index[2]].m_pos.x, 
					p->m_vertices[p->m_faces[i].index[2]].m_pos.y, 
					p->m_vertices[p->m_faces[i].index[2]].m_pos.z); 
        }
        else if(p->m_faces[i].type == 4) //quad 
        {
			Vector_set(&v1, 
					p->m_vertices[p->m_faces[i].index[0]].m_pos.x, 
					p->m_vertices[p->m_faces[i].index[0]].m_pos.y, 
					p->m_vertices[p->m_faces[i].index[0]].m_pos.z); 

			Vector_set(&v2, 
					p->m_vertices[p->m_faces[i].index[1]].m_pos.x, 
					p->m_vertices[p->m_faces[i].index[1]].m_pos.y, 
					p->m_vertices[p->m_faces[i].index[1]].m_pos.z); 

			Vector_set(&v3, 
					p->m_vertices[p->m_faces[i].index[2]].m_pos.x, 
					p->m_vertices[p->m_faces[i].index[2]].m_pos.y, 
					p->m_vertices[p->m_faces[i].index[2]].m_pos.z); 

			Vector_set(&v4, 
					p->m_vertices[p->m_faces[i].index[3]].m_pos.x, 
					p->m_vertices[p->m_faces[i].index[3]].m_pos.y, 
					p->m_vertices[p->m_faces[i].index[3]].m_pos.z); 
        }

        //------------------
        //面の法線を求める
        //------------------
        Math_dir(v1, v2, &ab);
        Math_dir(v1, v3, &ac);
        Math_crossproduct(ab, ac, &n);
        Math_normalize(&n);

        Math_invert(&n); //これやっといたほうがいい模様

        p->m_faces[i].normal = n;
    }

	return 0;
}
//}}}
//Model_set_vertex_normal {{{
//------------------------------------------------------------
// <desc>   全ての頂点の法線ベクトルを求める
// <in>    
// <out>    
// <memo>   頂点の法線ベクトルは、その頂点を共有する全ての面の
//          法線を平均化することにより、求める
//------------------------------------------------------------
int Model_set_vertex_normal(Model* p)
{
	int i, j;
    for(i=0; i < p->m_num_faces; i++)
    {
        for(j= 0; j < p->m_faces[i].type; j++)
        {
            //その頂点の使用回数を増加する
            p->m_vertices[p->m_faces[i].index[j]].m_used++; 

            //その頂点の法線に、使用されている面の法線を加算する
            Math_add(&(p->m_vertices[p->m_faces[i].index[j]].m_normal), p->m_faces[i].normal);
        }
    }
        
    //各頂点の法線を平均化する
    for(i = 0; i < p->m_num_vertices; i++)
    {
        Math_division(&p->m_vertices[i].m_normal, p->m_vertices[i].m_used);
    }

	return 0;
}
//}}}
//Model_set_edge_list {{{
//------------------------------------------------------------
// <desc>   エッジリストをつくる
// <in>    
// <out>    エッジの数
// <memo>   エッジ：辺
//------------------------------------------------------------
int Model_set_edge_list(Model* p)
{

#if 0
    m_edges = new CEdge[m_num_faces*3];  //三角形は、３辺をもつ
    m_num_edges = 0;

    int ei = 0;

    //-------------------------------------
    //  全辺を抽出
    //  i1 < i2 < i3 < i1 でチェックする
    //-------------------------------------
    //  辺を抽出
    for(int i = 0; i < m_num_faces; i++)
    {
        int i1 = m_faces[i].index[0];
        int i2 = m_faces[i].index[1];
        int i3 = m_faces[i].index[2];

        if(i1 < i2)
        {
            m_edges[ei].vertexindex[0] = i1;
            m_edges[ei].vertexindex[1] = i2;
            m_edges[ei].triangleindex[0] = i;
            m_edges[ei].triangleindex[1] = -1;
            m_num_edges++;
            ei++;
        }

        if(i2 < i3)
        {
            m_edges[ei].vertexindex[0] = i2;
            m_edges[ei].vertexindex[1] = i3;
            m_edges[ei].triangleindex[0] = i;
            m_edges[ei].triangleindex[1] = -1;
            m_num_edges++;
            ei++;
        }

        if(i3 < i1)
        {
            m_edges[ei].vertexindex[0] = i3;
            m_edges[ei].vertexindex[1] = i1;
            m_edges[ei].triangleindex[0] = i;
            m_edges[ei].triangleindex[1] = -1;
            m_num_edges++;
            ei++;
        }
    }

    //--------------------------------------
    //  割り当てられなかった三角形を抽出
    //  i1 > i2 > i3 > i1 でチェックする
    //--------------------------------------
    for(int i = 0; i < m_num_faces; i++)
    {
        int i1 = m_faces[i].index[0];
        int i2 = m_faces[i].index[1];
        int i3 = m_faces[i].index[2];

        if(i1 > i2)
        {
            ei = 0;
            for(int j = 0; j < m_num_edges; j++)
            {
                if(m_edges[ei].vertexindex[0] == i2 && 
                   m_edges[ei].vertexindex[1] == i1 &&
                   m_edges[ei].triangleindex[1] == -1)
                {
                   m_edges[ei].triangleindex[1] = i;
                }
                ei++;
            }
        }

        if(i2 > i3)
        {
            ei = 0;
            for(int j = 0; j < m_num_edges; j++)
            {
                if(m_edges[ei].vertexindex[0] == i3 && 
                   m_edges[ei].vertexindex[1] == i2 &&
                   m_edges[ei].triangleindex[1] == -1)
                {
                   m_edges[ei].triangleindex[1] = i;
                }
                ei++;
            }
        }

        if(i3 > i1)
        {
            ei = 0;
            for(int j = 0; j < m_num_edges; j++)
            {
                if(m_edges[ei].vertexindex[0] == i1 && 
                   m_edges[ei].vertexindex[1] == i3 &&
                   m_edges[ei].triangleindex[1] == -1)
                {
                   m_edges[ei].triangleindex[1] = i;
                }
                ei++;
            }
        }

    }

    return m_num_edges;

#endif
	return 0;
}
//}}}



#if 0

//Model_load {{{
//3D object　ファイルを開き、モデルデータをロードする。
Model* Model_load(Model* p, const char* filepath, const int _tex_id)
{
	int i;
	char line1[256]; 
    FILE* pf = fopen(filepath, "r");

	assert(pf != NULL);
	memset(line1, 0, sizeof(line1));
	
	dp("model load : %s", filepath);

	//--------------------------------
	// 頂点数を調べて、メモリを確保する
   	//--------------------------------
	while(p->m_num_vertices == 0)  
	{
		if(NULL == fgets(line1, sizeof(line1), pf))  //１行取得
			continue;

		//--------------------------
       	//コメントおよび空行処理
       	//--------------------------
		if(strncmp(line1, "//", 2) == 0 || line1[0] == '¥n')
			continue;

		if(strlen(line1) == 0)
			continue;

		//メモリ確保
       	sscanf(line1, "vertex : %d", &(p->m_num_vertices));	
		p->m_vertices = Vertex_new(p->m_num_vertices);

		memset(line1, 0, sizeof(line1));
	} 
	dp("*num vertices: %d", p->m_num_vertices);

    //--------------------------------
    // 頂点を読み込む
    //--------------------------------
    for(i = 0; i < p->m_num_vertices; i++)
    {
        float x, y, z;

        //１行取得
        if(NULL == fgets(line1, sizeof(line1), pf)) 
            continue;

        //--------------------------
        //コメントおよび空行処理
        //--------------------------
        if(strncmp(line1, "//", 2) == 0 || strncmp(line1, "¥n", 1) == 0)
            continue;

        if(strlen(line1) == 0)
            continue;
        
        //頂点を読み込む
            
	    sscanf(line1, "%f %f %f", &x, &y, &z);
        p->m_vertices[i].m_pos.x = x;
        p->m_vertices[i].m_pos.y = y;
        p->m_vertices[i].m_pos.z = z;

        memset(line1, 0, sizeof(line1));
    } 

	/*
	for(i = 0; i < p->m_num_vertices; i++){
		dp("(x, y, z) = (%f, %f, %f)", 
				p->m_vertices[i].m_pos.x, 
				p->m_vertices[i].m_pos.y, 
				p->m_vertices[i].m_pos.z 
				);
	}
	*/

    //--------------------------------
    // 面数を調べて、メモリを確保する
    //--------------------------------
    while(p->m_num_faces == 0)  
    {
        if(NULL == fgets(line1, sizeof(line1), pf))  //１行取得
            continue;

        //--------------------------
        //コメントおよび空行処理
        //--------------------------
        if(strncmp(line1, "//", 2) == 0 || line1[0] == '¥n')
            continue;

        if(strlen(line1) == 0)
            continue;

        //メモリ確保
        sscanf(line1, "face : %d", &(p->m_num_faces));	
        p->m_faces = Face_new(p->m_num_faces);
        
        memset(line1, 0, sizeof(line1));
    } 

	dp("* num faces: %d", p->m_num_faces);

    //--------------------------------
    // 面情報を読み込む
    //--------------------------------
    for(i = 0; i < p->m_num_faces; i++)
    {
        int type;	//三角形(3)か、四角形(4)か

        //１行取得
        if(NULL == fgets(line1, sizeof(line1), pf)) 
			continue;

        if(strncmp(line1, "//", 2) == 0 || strncmp(line1, "¥n", 1) == 0)
            continue;

        if(strlen(line1) == 0)
            continue;
        
        //頂点を読み込む
        sscanf(line1, "%d", &type);
           
        if(type == 3)
        {
            sscanf(line1, "%d V(%d %d %d) UV(%f %f %f %f %f %f)", 
                   &(p->m_faces[i].type), 
                   &(p->m_faces[i].index[0]), 
				   &(p->m_faces[i].index[1]), 
				   &(p->m_faces[i].index[2]), 
                   &(p->m_faces[i].uv[0][0]), &(p->m_faces[i].uv[0][1]), 
                   &(p->m_faces[i].uv[1][0]), &(p->m_faces[i].uv[1][1]), 
                   &(p->m_faces[i].uv[2][0]), &(p->m_faces[i].uv[2][1]));

            p->m_faces[i].m_visible = 0;
        }
        else if(type == 4)
        {
            sscanf(line1, "%d V(%d %d %d %d) UV(%f %f %f %f %f %f %f %f)", 
                   &(p->m_faces[i].type), 
                   &(p->m_faces[i].index[0]),
				   &(p->m_faces[i].index[1]), 
				   &(p->m_faces[i].index[2]), 
				   &(p->m_faces[i].index[3]), 
                   &(p->m_faces[i].uv[0][0]), &(p->m_faces[i].uv[0][1]), 
                   &(p->m_faces[i].uv[1][0]), &(p->m_faces[i].uv[1][1]), 
                   &(p->m_faces[i].uv[2][0]), &(p->m_faces[i].uv[2][1]),
                   &(p->m_faces[i].uv[3][0]), &(p->m_faces[i].uv[3][1]));
            
            p->m_faces[i].m_visible = 0;
        }

        //getchar();
        memset(line1, 0, sizeof(line1));
    } 

    fclose(pf);

	//全ての面の法線ベクトルを求める
    Model_set_face_normal(p);

	//全ての頂点の法線ベクトルを求める
    Model_set_vertex_normal(p);

	//エッジリストをつくる
    //dp("num edges : %d", Model_set_edge_list(p));

	//テクスチャIDの設定
	p->m_tex_id = _tex_id;

	return p;
}
//}}}


#endif



//Model_get_num_vertices {{{
int Model_get_num_vertices(Model* p)
{
	return p->m_num_vertices;
}
//}}}
//Model_get_num_faces {{{
int Model_get_num_faces(Model* p)
{
	return p->m_num_faces;
}
//}}}
//Model_get_num_edges {{{
int Model_get_num_edges(Model* p)
{
	return p->m_num_edges;
}
//}}}

#if 0
//Model_render {{{
//TODO: 下記の方式だと、とても描画が遅いはず。
//モデル読み込み時に動的にDisplayリストを生成して、ここではそれを一気に描画する。
void Model_render(Model* p)
{
	int i;
	Vertex v1, v2, v3, v4;
	Vector n;

	for(i=0; i < p->m_num_faces; i++)
	{
		if(p->m_faces[i].type == 3)
		{
			v1 = p->m_vertices[p->m_faces[i].index[0]];
			v2 = p->m_vertices[p->m_faces[i].index[1]];
			v3 = p->m_vertices[p->m_faces[i].index[2]];
			n = p->m_faces[i].normal;

			GI_triangle(v1, v2, v3, n, 1.0f, 0);
		}
		else if(p->m_faces[i].type == 4) 
		{
			Vector color;
			Vector_set(&color, 1.0f, 1.0f, 1.0f);

			v1 = p->m_vertices[p->m_faces[i].index[0]];
			v2 = p->m_vertices[p->m_faces[i].index[1]];
			v3 = p->m_vertices[p->m_faces[i].index[2]];
			v4 = p->m_vertices[p->m_faces[i].index[3]];
			n = p->m_faces[i].normal;

			GI_quad(&g_gi, v1, v2, v3, v4, n, color, 1.0f, 1, 1, 1, p->m_tex_id);
		}
	}

}
//}}}

#endif



