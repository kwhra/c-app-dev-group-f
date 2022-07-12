#ifndef PART_H
#define PART_H

extern GLfloat color[][4];
extern GLfloat pos1[];//光源、消した
//extern int XG;
//extern int YG;

//playerで定めた変数
enum COLOR { WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, GRAY, BLACK , PURPLE , BROWN, SKIN, LIGHTBLUE, GREENYELLOW, POWDERBLUE, FFFF33, FF6666, LEMONCHIFFON };//色(groundでも利用)
extern double M;
extern double player_x;//プレイヤーの座標x
extern double player_y;//プレイヤーの座標y
extern double player_z;//プレイヤーの座標z
extern double player_w;//プレイヤーの横幅(初期値は1.5)
extern double small_player;//プレイヤーの大きさ
extern int mySpecialValue;//プレイヤーの移動判定
extern int hit;//hitしたかどうかのフラグ
//extern int score;

//Groundで定めた変数
extern int width;//廊下の幅(playerでも利用)
extern double depth;//廊下の奥行
extern double tile_width;//廊下のタイルの幅
extern double wall_width;//塀の幅
extern double wall_height;//塀の高さ
extern double x;
extern double y;
extern double z;
extern int Flag;//背景の変更

//playerの関数
void drawPlayer();//プレイヤーの描画(大元)
void disPlayer();//プレイヤーの描画(回転・入力による移動)
void myKeyboardFunc(unsigned char key, int x, int y);
void mySpcialFunc(int key, int x, int y);
void mySpcialUpFunc(int key, int x, int y);
void myMouseFunc(int button, int state, int x, int y);
void myPassiveMotionFunc(int x, int y);

//hit_actionの関数
void printString(float x, float y, char* str, int length);//文字の生成
void actionHit();//

//Groundの関数
void drawGround();

//hitの関数
GLboolean isHit(int index);//消す予定

//他のプログラムでも利用するもの
void display(void);
void init(void);
//void myTimerFunc(int value);





#endif
