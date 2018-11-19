#include"snake.h"
extern int g_buff[MAP_LEN][MAP_WID];//全局二维数组，用于编辑地图
//节点类,包含节点坐标,图像,方向,移动方法,为蛇类基本单元.
class Node {
	unsigned int m_x;
	unsigned int m_y;
	char* m_pfig;
	int m_dir;
public:
	Node( int x=5,int y=5, const char* pstr = "●",int dir=RIGHT) :m_x(x), m_y(y), m_pfig("●"),m_dir(dir){}
	void setX(int val)
	{
		m_x = val;
	}
	int  getX()
	{
		return m_x;
	}
	void setY(int val)
	{
		m_y = val;
	}
	int getY()
	{
		return m_y;
	}
	void setPfig(char* val)
	{
		m_pfig = val;
	}
	char* getPfig()
	{
		return m_pfig;
	}
	int getDir()
	{
		return m_dir;
	}
	void setDir(int val)
	{
		m_dir = val;
	}
	void show()
	{
		show_char(m_x, m_y, m_pfig );
	}
	void erase()
	{
		show_char(m_x, m_y, "  ");
	}
	//节点移动为方法是贪吃蛇的基本思路
	//根据方向打印新的节点,并擦除原有节点.
	void move()
	{
		switch (m_dir)
		{
		case UP:
			erase();
			m_y--;
			show();
			break;
		case DOWN:
			erase();
			m_y++;
			show();
			break;
		case LEFT:
			erase();
			m_x--;
			show();
			break;
		case RIGHT:
			erase();
			m_x++;
			show();
			break;
		}
	}
};
//蛇类包含一个节点数组,以整个数组元素的移动表示蛇的移动
//蛇吃食物增长,通过判断蛇头部坐标与食物坐标重合
//在蛇数组尾部增加一个新元素.
class Snake {
	Node m_buff[SNAKE_SIZE];
	int m_len;
	Node m_head;
public:
	Snake() :m_head(5, 5), m_len(0) {
		m_buff[0] = m_head;
	}
	void Init()
	{
		this->m_len = 0;
		this->m_buff[0].setX(5);
		this->m_buff[0].setY(5);
		this->m_buff[0].setDir(RIGHT);
	}
	Node getHead()
	{
		return m_head;
	}
	Node* getBuff()
	{
		return m_buff;
	}
	void setBuff(Node* buff)
	{
		for (int i = 0;i < m_len;i++)
		{
			m_buff[i] = buff[i];
		}
	}
	void addBuff()
	{
		if (m_buff[m_len].getDir() == UP)
		{
			m_buff[m_len + 1].setX(m_buff[m_len].getX());
			m_buff[m_len + 1].setY(m_buff[m_len].getY() + 1);
			m_buff[m_len + 1].setDir(m_buff[m_len].getDir());
			m_buff[m_len + 1].setPfig(m_buff[m_len].getPfig());
		}
		else if (m_buff[m_len].getDir() == DOWN)
		{
			m_buff[m_len + 1].setX(m_buff[m_len].getX());
			m_buff[m_len + 1].setY(m_buff[m_len].getY() - 1);
			m_buff[m_len + 1].setDir(m_buff[m_len].getDir());
			m_buff[m_len + 1].setPfig(m_buff[m_len].getPfig());
		}
		else if (m_buff[m_len].getDir() == LEFT)
		{
			m_buff[m_len + 1].setX(m_buff[m_len].getX() + 1);
			m_buff[m_len + 1].setY(m_buff[m_len].getY());
			m_buff[m_len + 1].setDir(m_buff[m_len].getDir());
			m_buff[m_len + 1].setPfig(m_buff[m_len].getPfig());
		}
		else
		{
			m_buff[m_len + 1].setX(m_buff[m_len].getX() - 1);
			m_buff[m_len + 1].setY(m_buff[m_len].getY());
			m_buff[m_len + 1].setDir(m_buff[m_len].getDir());
			m_buff[m_len + 1].setPfig(m_buff[m_len].getPfig());
		}
		m_len++;
	}
	int getLen()
	{
		return m_len;
	}
	void setLen(int len)
	{
		m_len = len;
	}
	//蛇移动,通过死循环遍历蛇数组中的每一个节点而移动
	void move()
	{
		//蛇数组没一个节点移动之前,要先将数组中前一个节点的方向赋值给后一个节点
		//并且这个过程得是从后向前,先从后向前进行的
		//在通过判断每一个节点的方向进行移动
		for (int i = m_len;i >0;i--)
		{
			m_buff[i].setDir(m_buff[i - 1].getDir());
		}
		char c_key = 0;
		if (_kbhit())
		{
			c_key = _getch();
		}
		switch (c_key)//在循环中接收键盘输入方向，并赋值给第一个节点
		{
		case 'W':
		case 'w':
			if ((m_buff[0].getDir() == LEFT) || (m_buff[0].getDir() == RIGHT))
				m_buff[0].setDir(UP);
			break;
		case 'S':
		case 's':
			if ((m_buff[0].getDir() == LEFT) || (m_buff[0].getDir() == RIGHT))
				m_buff[0].setDir(DOWN);
			break;
		case 'A':
		case 'a':
			if ((m_buff[0].getDir() == UP) || (m_buff[0].getDir() == DOWN))
				m_buff[0].setDir(LEFT);
			break;
		case 'D':
		case 'd':
			if ((m_buff[0].getDir() == UP) || (m_buff[0].getDir() == DOWN))
				m_buff[0].setDir(RIGHT);
			break;
		case ' ':
			while (1)//若输入空格进入死循环,蛇暂停移动,再次输入空格蛇继续移动
			{
				char ch = 0;
				ch = _getch();
				if (ch == ' ')
					break;
			}
			break;
		}
		for (int i = 0;i < m_len + 1;i++)
		{
			m_buff[i].move();
		}
	}
	
	void showSnake()
	{
		for (int i = 0;i < m_len;i++)
		{
			m_buff[i].show();
		}
	}
};
class Food
{
	int m_food_x;
	int m_food_y;
	char* m_food_fig;
public:
	Food(int x = 0, int y = 0,char*fig="☆") :m_food_x(x), m_food_y(y),m_food_fig(fig){}
	void setX(int val)
	{
		m_food_x = val;
	}
	int getX()
	{
		return m_food_x;
	}
	void setY(int val)
	{
		m_food_y = val;
	}
	int getY()
	{
		return m_food_y;
	}
	//随机创建食物为一个复杂的点,不能创建在地图编辑的障碍里面,且不能出现在蛇身体里面.
	//通过遍历判断随机坐标是否合格,不合格重新随机生成,知道合格为止
	//有不好的地方,这样遍历随着地图的复杂更高,蛇的长度更大,会造成卡顿
	void create(Snake snake)//为了遍历蛇身,以传递蛇类参数的方式解决******
	{
		srand((unsigned)time(0));
		m_food_x = rand() % (MAP_LEN - 2) + 1;
		m_food_y = rand() % (MAP_WID - 2) + 1;
		m_food_fig = "☆";
		for (int i = 0;i < snake.getLen();i++)//在生成事物之后对坐标进行判断，
			//看是否与蛇体重合，重合则重新生成新食物
		{
			while ((m_food_x == snake.getBuff()[i].getX() &&
				m_food_y == snake.getBuff()[i].getY())||
				g_buff[m_food_x][m_food_y]==1)
			{
				srand((unsigned)time(0));
				m_food_x = rand() % (MAP_LEN - 2) + 1;
				m_food_y = rand() % (MAP_WID - 2) + 1;
			}
		}
		show_char(m_food_x, m_food_y, m_food_fig);
	}
};
class Map
{
	int m_cursor_x;
	int m_cursor_y;
	char* m_Map_piece;
public:
	Map(int x = 1, int y = 1, char* piece = "■") :m_cursor_x(x), m_cursor_y(y), m_Map_piece(piece) {}
	void map_init()
	{
		for (int i = 0;i < MAP_LEN;i++)
		{

			if (i == 0 || i == (MAP_LEN-1))
			{
				for (int j = 0;j < MAP_WID;j++)
				{
					show_char(i, j, m_Map_piece);
					g_buff[i][j] = 1;
				}
			}
			else
			{
				for (int j = 0;j < MAP_WID;j++)
				{
					if (j == 0 || j == (MAP_WID-1))
					{
						show_char(i, j, m_Map_piece);
						g_buff[i][j] = 1;
					}
					else
					{
						show_char(i, j, "  ");
						g_buff[i][j] = 0;
					}
				}
			}
		}
	}
	void map_edit()
	{
		map_init();
		show_char(MAP_LEN , 6, "按w【上】a【左】s【下】d【右】");
		show_char(MAP_LEN , 7, "移动光标");
		show_char(MAP_LEN , 8, "按【空格】生成/清除障碍【■】");
		show_char(MAP_LEN , 9, "按【p】开始游戏");
		set_cursor(m_cursor_x, m_cursor_y);
		char ckey = 0;
		while (1)
		{
			if (_kbhit())
				ckey = _getch();
			switch (ckey)
			{
			case 'W':
			case 'w':
				if ((m_cursor_y - 1) != 0)
				{
					set_cursor(m_cursor_x, --m_cursor_y );
				}
				break;
			case 'S':
			case 's':
				if ((m_cursor_y + 1) != MAP_WID)
				{
					set_cursor(m_cursor_x, ++m_cursor_y);
				}
				break;
			case 'A':
			case 'a':
				if ((m_cursor_x - 1) != 0)
				{
					set_cursor(--m_cursor_x, m_cursor_y);
				}
				break;
			case 'D':
			case 'd':
				if ((m_cursor_x + 1) != MAP_LEN)
				{
					set_cursor(++m_cursor_x, m_cursor_y);
				}
				break;
			case ' ':
				if (g_buff[m_cursor_x][m_cursor_y] == 0)
				{
					show_char(m_cursor_x, m_cursor_y, m_Map_piece);
					g_buff[m_cursor_x][m_cursor_y] = 1;
				}
				else
				{
					show_char(m_cursor_x, m_cursor_y, "  ");
					g_buff[m_cursor_x][m_cursor_y] = 0;
				}
				break;
			case 'P':
			case 'p':
				return;
			}
			ckey = 0;
		}
	}
	void show_map()
	{
		for (int i = 0;i < MAP_LEN;i++)
		{
			for (int j = 0;j < MAP_WID;j++)
			{
				if (g_buff[i][j] == 1)
					show_char(i, j, "■");
				else
					show_char(i, j, "  ");
			}
		}
	}
};
class Game{
	Snake m_snake;
	Food  m_food;
	Map m_Map;
	bool snake_die;
	unsigned int m_speed;
	unsigned int m_score;
public:
	Game() :snake_die(0), m_speed (200),m_score(0){}
	void game_Run()
	{
		show_char( MAP_LEN, 0,"当前速度：" );
		show_char( MAP_LEN, 2,"分数：");
		show_char( MAP_LEN, 4,"按【空格】暂停/继续" );
		m_snake.Init();
		m_Map.show_map();
		m_food.create(m_snake);
		while (1)
		{
			show_char(MAP_LEN, 1, "");
			cout << get_speed();
			show_char(MAP_LEN, 3, "");
			cout << get_score();
			Sleep(get_speed());
			m_snake.move();
			if (m_food.getX() == m_snake.getBuff()[0].getX() && m_food.getY() == m_snake.getBuff()[0].getY())
			{
				m_snake.addBuff();
				m_food.create(m_snake);
			}
			if (m_snake.getBuff()[0].getX() == 0 || m_snake.getBuff()[0].getX() == (MAP_LEN-1) ||
				(m_snake.getBuff()[0].getY()) == 0 || m_snake.getBuff()[0].getY() == (MAP_WID-1)||
				g_buff[m_snake.getBuff()[0].getX()][m_snake.getBuff()[0].getY()]==1)
			{
				snake_die = 1;
				return;
			}
			for (int i = 4;i < m_snake.getLen();i++)
			{
				if (m_snake.getBuff()[0].getX() == m_snake.getBuff()[i].getX() &&
					m_snake.getBuff()[0].getY() == m_snake.getBuff()[i].getY())
				{
					snake_die = 1;
					return;
				}
			}
		}
	}
	int get_speed()
	{
		return m_speed - m_snake.getLen()*10;
	}
	int get_score()
	{
		return m_snake.getLen();
	}
	int get_snake_die()
	{
		return snake_die;
	}
	Snake get_snake()
	{
		return m_snake;
	}
};
class Menu 
{ 
	Map m_map;
	Game m_game;
public:
	Menu() {}
	void setMenu()
	{
		PlaySoundA("sound\\background.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		show_char(15, 5, "贪吃蛇");
		show_char(15, 7, "1.开始游戏");
		show_char(15, 9, "2.编辑游戏");
		show_char(15, 11,"3.退出");
		show_char(15, 13, "请输入选项：");
		while(1)
		{
			int nKey;
			scanf_s("%d", &nKey);
			if (nKey == 1)
			{

				HANDLE hStdOut;
				hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
				CONSOLE_CURSOR_INFO cci = { 0 };
				cci.bVisible = FALSE;
				cci.dwSize = 5;
				SetConsoleCursorInfo(hStdOut, &cci);
				system("cls");
				m_map.map_init();
				m_game.game_Run();
				if (m_game.get_snake_die()==1)
				{
					char cKey =0;
					while (1)
					{
						show_char(12, 9, "GAME OVER!");
						show_char(12, 11, "是否重新开始（y/n）:");
						cKey = _getch();
						if (cKey == 'y' || cKey == 'Y')
						{
							system("cls");
							m_game.game_Run();
						}
						if (cKey == 'n' || cKey == 'N')
						{
							system("cls");
							return;
						}
					}	
				}
			}
			if (nKey == 2)
			{

				HANDLE hStdOut;
				hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
				CONSOLE_CURSOR_INFO cci = { 0 };
				cci.bVisible = TRUE;
				cci.dwSize = 5;
				SetConsoleCursorInfo(hStdOut, &cci);
				system("cls");
				m_map.show_map();
				m_map.map_edit();
				m_game.game_Run();
				if (m_game.get_snake_die() == 1)
				{
					char cKey = 0;
					while (1)
					{
						show_char(MAP_LEN / 2 - 3, MAP_WID / 2, "GAME OVER!");
						show_char(MAP_LEN / 2 - 5, MAP_WID / 2, "是否重新开始（y/n）:");
						cKey = _getch();
						if (cKey == 'y' || cKey == 'Y')
						{
							system("cls");
							m_map.show_map();
							m_game.game_Run();
						}
						if (cKey == 'n' || cKey == 'N')
						{
							system("cls");
							return;
						}
					}
				}
			}
			if (nKey == 3)
			{
				return;
			}
		}
	}
};
int main()
{
	system("title 贪吃蛇");
	system("mode con cols=100 lines=30");
	Menu obj;
	obj.setMenu();
}
//分析与总结
//1.
//打印移动蛇身体的时候遇到一个问题,其基本的原理应该是,前节点的方向赋给后一个节点,
//最初想当然的以为是for(int i=0;i<len;i++) buff[i]=buff[i+1]就行了
//出了问题,困扰了很久,最后发现应该是for(int i=len-1;i>0;i--) buff[i]=buff[i-1];
//这种看似差不多的代码其实有很大的差别,以后需要多注意一下.
//2.
//对于类的设计与封装,还有很多不太科学的地方,写项目的时候总是想着一个一个的小功能的实现,
//到后面发现每次想增加一个功能就要对整体代码做很大的改动,
//以至于在写完地图编辑以后再写游戏保存感觉特别难以下手,感觉是要把整个代码改个七七八八才能把功能实现.
//以后尽量多一些全局的分析与设计.
