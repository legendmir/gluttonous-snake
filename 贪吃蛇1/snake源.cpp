#include"snake.h"
extern int g_buff[MAP_LEN][MAP_WID];//ȫ�ֶ�ά���飬���ڱ༭��ͼ
//�ڵ���,�����ڵ�����,ͼ��,����,�ƶ�����,Ϊ���������Ԫ.
class Node {
	unsigned int m_x;
	unsigned int m_y;
	char* m_pfig;
	int m_dir;
public:
	Node( int x=5,int y=5, const char* pstr = "��",int dir=RIGHT) :m_x(x), m_y(y), m_pfig("��"),m_dir(dir){}
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
	//�ڵ��ƶ�Ϊ������̰���ߵĻ���˼·
	//���ݷ����ӡ�µĽڵ�,������ԭ�нڵ�.
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
//�������һ���ڵ�����,����������Ԫ�ص��ƶ���ʾ�ߵ��ƶ�
//�߳�ʳ������,ͨ���ж���ͷ��������ʳ�������غ�
//��������β������һ����Ԫ��.
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
	//���ƶ�,ͨ����ѭ�������������е�ÿһ���ڵ���ƶ�
	void move()
	{
		//������ûһ���ڵ��ƶ�֮ǰ,Ҫ�Ƚ�������ǰһ���ڵ�ķ���ֵ����һ���ڵ�
		//����������̵��ǴӺ���ǰ,�ȴӺ���ǰ���е�
		//��ͨ���ж�ÿһ���ڵ�ķ�������ƶ�
		for (int i = m_len;i >0;i--)
		{
			m_buff[i].setDir(m_buff[i - 1].getDir());
		}
		char c_key = 0;
		if (_kbhit())
		{
			c_key = _getch();
		}
		switch (c_key)//��ѭ���н��ռ������뷽�򣬲���ֵ����һ���ڵ�
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
			while (1)//������ո������ѭ��,����ͣ�ƶ�,�ٴ�����ո��߼����ƶ�
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
	Food(int x = 0, int y = 0,char*fig="��") :m_food_x(x), m_food_y(y),m_food_fig(fig){}
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
	//�������ʳ��Ϊһ�����ӵĵ�,���ܴ����ڵ�ͼ�༭���ϰ�����,�Ҳ��ܳ���������������.
	//ͨ�������ж���������Ƿ�ϸ�,���ϸ������������,֪���ϸ�Ϊֹ
	//�в��õĵط�,�����������ŵ�ͼ�ĸ��Ӹ���,�ߵĳ��ȸ���,����ɿ���
	void create(Snake snake)//Ϊ�˱�������,�Դ�����������ķ�ʽ���******
	{
		srand((unsigned)time(0));
		m_food_x = rand() % (MAP_LEN - 2) + 1;
		m_food_y = rand() % (MAP_WID - 2) + 1;
		m_food_fig = "��";
		for (int i = 0;i < snake.getLen();i++)//����������֮�����������жϣ�
			//���Ƿ��������غϣ��غ�������������ʳ��
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
	Map(int x = 1, int y = 1, char* piece = "��") :m_cursor_x(x), m_cursor_y(y), m_Map_piece(piece) {}
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
		show_char(MAP_LEN , 6, "��w���ϡ�a����s���¡�d���ҡ�");
		show_char(MAP_LEN , 7, "�ƶ����");
		show_char(MAP_LEN , 8, "�����ո�����/����ϰ�������");
		show_char(MAP_LEN , 9, "����p����ʼ��Ϸ");
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
					show_char(i, j, "��");
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
		show_char( MAP_LEN, 0,"��ǰ�ٶȣ�" );
		show_char( MAP_LEN, 2,"������");
		show_char( MAP_LEN, 4,"�����ո���ͣ/����" );
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
		show_char(15, 5, "̰����");
		show_char(15, 7, "1.��ʼ��Ϸ");
		show_char(15, 9, "2.�༭��Ϸ");
		show_char(15, 11,"3.�˳�");
		show_char(15, 13, "������ѡ�");
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
						show_char(12, 11, "�Ƿ����¿�ʼ��y/n��:");
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
						show_char(MAP_LEN / 2 - 5, MAP_WID / 2, "�Ƿ����¿�ʼ��y/n��:");
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
	system("title ̰����");
	system("mode con cols=100 lines=30");
	Menu obj;
	obj.setMenu();
}
//�������ܽ�
//1.
//��ӡ�ƶ��������ʱ������һ������,�������ԭ��Ӧ����,ǰ�ڵ�ķ��򸳸���һ���ڵ�,
//����뵱Ȼ����Ϊ��for(int i=0;i<len;i++) buff[i]=buff[i+1]������
//��������,�����˺ܾ�,�����Ӧ����for(int i=len-1;i>0;i--) buff[i]=buff[i-1];
//���ֿ��Ʋ��Ĵ�����ʵ�кܴ�Ĳ��,�Ժ���Ҫ��ע��һ��.
//2.
//�������������װ,���кܶ಻̫��ѧ�ĵط�,д��Ŀ��ʱ����������һ��һ����С���ܵ�ʵ��,
//�����淢��ÿ��������һ�����ܾ�Ҫ������������ܴ�ĸĶ�,
//��������д���ͼ�༭�Ժ���д��Ϸ����о��ر���������,�о���Ҫ����������ĸ����߰˰˲��ܰѹ���ʵ��.
//�Ժ�����һЩȫ�ֵķ��������.
