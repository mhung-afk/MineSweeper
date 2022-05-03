
#include "Funtion.h"
#include "Header.h"
#include "Console.h"

COORD ViTriConTro;  //vị trí con trỏ, toạ độ đầu là (0;0), x hoành độ, y tung độ
bool SuDungPhim = false;
CauTrucBang CTBang;
CauTrucO** CTO;
bool DangChoi = false; //lưu trạng thái có đang chơi hay k (chưa vào game hoặc thắng/thua game sẽ false)
bool lose = false;  //kiểm tra thua game chưa?
short Select= 0;   //lưu module đang chọn ở Menu()
short ManHinh = 0; //0: màn hình chính, 1:màn hình chọn level, 2: màn hình giới thiệu, 3:màn hình chơi game , 4: màn hình out game

void TaoMang2Chieu()
{
	CTO = new CauTrucO*[CTBang.SDong]; //quản lí các dòng
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		CTO[i] = new CauTrucO[CTBang.SCot]; //quản lí cột
	}
}
void XoaMang2Chieu()
{
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		delete[] CTO[i];
	}
	delete[] CTO;
}
void KhoiTao(short SDong, short SCot, short SSoBom)
{
	setBackgroundColor(0);
	CTBang.SDong = SDong;
	CTBang.SCot = SCot;
	CTBang.SSoBom = SSoBom;
	CTBang.SSoODaMo = 0;
	CTBang.SSoCo = 0;
	TaoMang2Chieu();
	TaoBom();
	DangChoi = true;  //bắt đầu chơi
	system("cls");
	MainLine();	
	VeBang();
	XuLiSuKien();
	
	Select = 0;
	XoaMang2Chieu();
}

short ToaDoX(short SX)
{
	return SX * 2 + ConsoleWidth/2 - CTBang.SCot ;
}
short ToaDoY(short SY)
{
	return SY + ConsoleHeight/2 - CTBang.SDong + 12*CTBang.SDong/20;
}

void VeO(short SX, short SY, short SKieu)
{
	switch (SKieu)
	{
	case 0:
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 0, 11, "  ");
		break;
	case 1:
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 9, 15, " 1");
		break;
	case 2:
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 2, 15, " 2");
		break;
	case 3:
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 12, 15, " 3");
		break;
	case 4:
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 1, 15, " 4");
		break;
	case 5:
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 4, 15, " 5");
		break;
	case 6:
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 3, 15, " 6");
		break;
	case 7:
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 0, 15, " 7");
		break;
	case 8:
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 13, 15, " 8");
		break;
	case 9:  //ô có bom
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 14, 12, " B");
		break;
	case 10:  //ô chẵn
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 0, 8, "  ");
		break;  
	case 11:  //ô lẻ
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 0, 7, "  ");
		break;
	case 12:   //con trỏ
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 0, 13, " ");
		break;
	case 13:   //căm cờ
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 12, 14, " P");
		break;
	case 14:   //cắm cờ sai
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 15, 16, "XP");
		break;
	case 15:  //cắm cờ đúng
		setColorBGTextXY(ToaDoX(SX), ToaDoY(SY), 12, 14, "~P");
		break;
	}
}

void VeBang()
{
	TrangThaiGame(1);
	if (win() == true || lose == true)
	{
		DangChoi = false;
	}
	for (int i = 0; i < CTBang.SCot; ++i)
	{
		for (int j = 0; j < CTBang.SDong; ++j)
		{
			if (CTO[i][j].BCamCo)
			{
				if (DangChoi)
				{
					VeO(j, i, 13);
				}
				else
				{
					if (CTO[i][j].BCoBom)
						VeO(j, i, 15);
					else if(!CTO[i][j].BCoBom && !CTO[i][j].BDaMo)
						VeO(j, i, 14);
				}
			}
			else if (!CTO[i][j].BCamCo && CTO[i][j].BCoBom && !DangChoi)
				VeO(j, i, 9);

			else if (CTO[i][j].SBomLanCan)
			{
				VeO(j, i, CTO[i][j].SBomLanCan);
			}
			else if (CTO[i][j].BDaMo)
			{
				VeO(j, i, 0);
			}	
			else if ((i + j) % 2 )
				VeO(j, i, 11);
			else 
				 VeO(j, i, 10);
			
			if (SuDungPhim)
				VeO(ViTriConTro.X, ViTriConTro.Y, 12);
		}	
	}
	if (win())
	{
		TrangThaiGame(3);		
		setBackgroundColor(0);
		setColorBGTextXY(43, 7, 12, 0, "WAIT 3 sec TO QUIT TO MENU");
		Sleep(800);
		setColorBGTextXY(43, 7, 12, 0, "                          ");
		Sleep(200);
		setColorBGTextXY(43, 7, 12, 0, "WAIT 2 sec TO QUIT TO MENU");
		Sleep(800);
		setColorBGTextXY(43, 7, 12, 0, "                          ");
		Sleep(200);
		setColorBGTextXY(43, 7, 12, 0, "WAIT 1 sec TO QUIT TO MENU");
		Sleep(800);
		setColorBGTextXY(43, 7, 12, 0, "                          ");
		Sleep(200);
		system("cls");
		ManHinh = 0;
		MainLine();
		Menu();
	}
	else if (lose)
	{		
		lose = false;
		TrangThaiGame(2);
		setColorBGTextXY(0, 9, 9, 0,  "      SO SAD!! :v   ");
		setColorBGTextXY(0, 11, 9, 0, " PLEASE PRESS ESCAPE");
		setColorBGTextXY(0, 12, 9, 0, "        TO QUIT     ");
		setColorBGTextXY(0, 14, 4, 7, "      GOOD BYE!!    ");
		XuLiSuKien();
		system("cls");
		ManHinh = 0;
	}
}

void TaoBom()
{
	srand((short)time(NULL));
	short SSoBom = CTBang.SSoBom;
	short SI, SJ; //biến chỉ hàng - cột trên bảng
	while (SSoBom)
	{
		SI = rand() % CTBang.SDong;
		SJ = rand() % CTBang.SCot;
		if (CTO[SI][SJ].BCoBom)
			continue;
		CTO[SI][SJ].BCoBom = true;
		--SSoBom;
	}
}

short SoBomLanCan(short SX, short SY)
{
	short dem = 0;
	for (int i = SX - 1; i <= SX + 1; ++i)
	{
		for (int j = SY - 1; j <= SY + 1; ++j)
		{
			if (i < 0 || i == CTBang.SDong || j < 0 || j == CTBang.SCot || (i == SX && j == SY))
				continue;
			if (CTO[i][j].BCoBom)
				++dem;
		}
	}
	return dem;
}

void open(short SX, short SY)
{
	if (!CTO[SX][SY].BDaMo && !CTO[SX][SY].BCamCo)
	{
		CTO[SX][SY].BDaMo = true;
		if (CTO[SX][SY].BCoBom)
		{
			lose = true;
			return;
		}
			
		else
		{
			short SSoBomLanCan = SoBomLanCan(SX, SY);
			if (SSoBomLanCan > 0)
				CTO[SX][SY].SBomLanCan = SSoBomLanCan;
			else
			{
				for (int i = SX - 1; i <= SX + 1; ++i)
				{
					for (int j = SY - 1; j <= SY + 1; ++j)
					{
						if (i < 0 || i == CTBang.SDong || j < 0 || j == CTBang.SCot || (i == SX && j == SY))
							continue;
						else
							open(i, j);
					}
				}
			}
			++CTBang.SSoODaMo;
		}
	}
}

void ClickL(short SX, short SY)
{
	if (!CTO[SX][SY].BDaMo && !CTO[SX][SY].BCamCo)
	{
		open(SX, SY);
		VeBang();
	}
}

//cắm cờ
void ClickR(short SX, short SY)
{
	if (!CTO[SX][SY].BDaMo)
	{
		if (CTO[SX][SY].BCamCo)
		{
			CTO[SX][SY].BCamCo = false;
			--CTBang.SSoCo;
		}
		else
		{
			CTO[SX][SY].BCamCo = true;
			++CTBang.SSoCo;
		}
	}
	if (CTBang.SSoCo > CTBang.SSoBom)
	{
		--CTBang.SSoCo;
		CTO[SX][SY].BCamCo = false;
	}	
	VeBang();
}

void XuLiPhim(KEY_EVENT_RECORD key)  
{
	if (key.bKeyDown)  //có nhấn phím hay không
	{
		switch (key.wVirtualKeyCode)  //lưu phím đc nhấn
		{
		case VK_UP:
			if (DangChoi)
			{
				SuDungPhim = true;
				ViTriConTro.Y = (ViTriConTro.Y == 0 ? (CTBang.SDong - 1) : (ViTriConTro.Y - 1));
				VeBang();
			}
			else 
			{
				Select = (Select == 0 ? (Select + 2) : (Select - 1));
				if (ManHinh == 0)
				{
					Menu();
				}
				else if (ManHinh == 1)
				{
					SelectLevel();
				}
			}
			break;  //mũi tên lên
		case VK_DOWN:
			if (DangChoi)
			{
				SuDungPhim = true;
				ViTriConTro.Y = (ViTriConTro.Y == (CTBang.SDong - 1) ? 0 : (ViTriConTro.Y + 1));
				VeBang();
			}
			else
			{
				Select = (Select == 2 ? (Select - 2) : (Select + 1));
				if (ManHinh == 0)
				{
					Menu();
				}
				else if (ManHinh == 1)
				{
					SelectLevel();
				}
			}
			break;   //mũi tên xuống
		case VK_LEFT:
			if (DangChoi)
			{
				SuDungPhim = true;
				ViTriConTro.X = (ViTriConTro.X == 0 ? (CTBang.SCot - 1) : (ViTriConTro.X - 1));
				VeBang();
			}
			break;  //mũi tên trái
		case VK_RIGHT:
			if (DangChoi)
			{
				SuDungPhim = true;
				ViTriConTro.X = (ViTriConTro.X == (CTBang.SCot - 1) ? 0 : (ViTriConTro.X + 1));
				VeBang();
			}
			break;   //mũi tên phải
		case VK_RETURN:
			if (ManHinh == 0)
			{
				switch (Select)
				{
				case 0:
					ManHinh = 1;
					SelectLevel();
					Select = 0;
					break;
				case 1:
					ManHinh = 2;
					Description();
					Select = 0;
					break;
				case 2:
					system("cls");					
					setColorBGTextXY(46, 15, 12, 0, " GOOD BYE!! ");
					setColorBGTextXY(40, 19, 12, 0, "PRESS ANY KEY TO GET OUT!");
					setColor(8);
					setBackgroundColor(8);
					ManHinh = 4;
					exit(0);
					XuLiSuKien();
				}				
			}
			else if (ManHinh == 1)
			{
				if (Select == 0)
				{
					ManHinh = 3;
					KhoiTao(10, 10, 12);
				}
				else if (Select == 1)
				{
					ManHinh = 3;
					KhoiTao(20, 20, 60);
				}
				else if (Select == 2)
				{
					ManHinh = 3;
					KhoiTao(30, 30, 180);
				}
			}
			
		
			break;  //Enter
		case VK_ESCAPE:
			if (ManHinh == 2)
			{
				system("cls");
				ManHinh = 0;
				MainLine();
				Menu();
			}
			else if (ManHinh == 1)
			{
				ManHinh = 0;
				Menu();
			}
			else if (ManHinh == 3)
			{
				if (!win()) {
					ManHinh = 0;
					Select = 0;
					DangChoi = false;
					CTBang.SSoODaMo = 0;
					CTBang.SSoCo = 0;
					setBackgroundColor(0);
					XoaMang2Chieu();
					system("cls");
					MainLine();
					Menu();
				}
				
			}		
			break;   //Esc
		case ClickLeft:  //Z
			if (DangChoi)
			{
				ClickL(ViTriConTro.Y, ViTriConTro.X);
			}
			break;  
		case ClickRight:  //X
			if (DangChoi)
			{
				ClickR(ViTriConTro.Y, ViTriConTro.X);
			}
			break;
		case ChangeMusic: //S
			music();
			break;
		}
	}
}


void XuLiSuKien()
{
	while (true)
	{
		DWORD DW = 0;  //lưu sự kiện hiện tại
		DWORD DWR = 0;  //lưu số lượng sự kiện đã đọc
		HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE);  //Nhấn phím - lưu sự kiện Input vào biến HConsoleInput
		GetNumberOfConsoleInputEvents(HConsoleInput, &DW);  //đặt sự kiện đầu vào  cho DW
		if (DW)
		{
			INPUT_RECORD* IREvenBuffer = new INPUT_RECORD[DW]; //Con trỏ lưu sự kiện trong bộ nhớ đệm
			ReadConsoleInput(HConsoleInput, IREvenBuffer, DW, &DWR);  //gắn cho con trỏ sự kiện(từ HConsoleInput) và lưu lại sự kiện đã đọc cho DWR từ DW
			for (DWORD i = 0; i < DW; ++i)
			{
				if (IREvenBuffer[i].EventType == KEY_EVENT)  //kiểm tra sự kiện dạng phím hay không
				{
					XuLiPhim(IREvenBuffer[i].Event.KeyEvent);
				}
			}
		}
	}
}

void MainLine()
{
	setColor(7);
	for (int i = 0; i < ConsoleWidth; i++)
	{
		printf("%c", 45);
	}
	setColorBGTextXY(47, 2, 12, 0, "MINESWEEPER\n\n");
	setColor(7);
	for (int i = 0; i < ConsoleWidth; i++)
	{
		printf("%c", 45);
	}
}

void TrangThaiGame(short trangthai)
{
	setColorBGTextXY(1, 5, 7, 0, "MAP:   ");
	std::cout << CTBang.SDong << " x " << CTBang.SCot << std::endl;
	setColorBGTextXY(1, 6, 7, 0, "BOOMS: ");
	std::cout << CTBang.SSoBom << "    FLAG PLUGGED:  " << CTBang.SSoCo;

	switch (trangthai)
	{
	case 1: 
		setColorBGTextXY(65, 5, 7, 0, "SITUATION:  YOU WILL LOSE!! ");
		break;
	case 2:
		setColorBGTextXY(65, 5, 9, 7, "SITUATION:       LOSE       ");
		break;
	case 3:
		setColorBGTextXY(65, 5, 9, 7, "SITUATION:      VICTORY     ");
		break;
	}
	setBackgroundColor(0);
	setColor(7);
	std::cout << std::endl<<std::endl;
	
	for (int i = 0; i < ConsoleWidth; i++)
	{
		printf("%c", 45);
	}
}

bool win()
{
	if (CTBang.SSoODaMo + CTBang.SSoBom == CTBang.SCot * CTBang.SDong)
		return true;
	else
		return false;
}

void Menu()
{	
	switch (Select)
	{
	case 0:	
		setColorBGTextXY(46, 11, 12, 8, "  PLAY NOW   ");
		setColorBGTextXY(46, 13, 12, 0, " INSTRUCTION ");
		setColorBGTextXY(46, 15, 12, 0, "    QUIT     ");
		break;
	case 1:
		setColorBGTextXY(46, 11, 12, 0, "  PLAY NOW   ");
		setColorBGTextXY(46, 13, 12, 8, " INSTRUCTION ");
		setColorBGTextXY(46, 15, 12, 0, "    QUIT     ");
		break;
	case 2:
		setColorBGTextXY(46, 11, 12, 0, "  PLAY NOW   ");
		setColorBGTextXY(46, 13, 12, 0, " INSTRUCTION ");
		setColorBGTextXY(46, 15, 12, 8, "    QUIT     ");
		break;
	}
	XuLiSuKien();
}
void SelectLevel()
{
	switch (Select)
	{
	case 0:
		setColorBGTextXY(46, 11, 12, 8, "    EASY     ");
		setColorBGTextXY(46, 13, 12, 0, "   MEDIUM    ");
		setColorBGTextXY(46, 15, 12, 0, "    HARD     ");
		break;
	case 1:
		setColorBGTextXY(46, 11, 12, 0, "    EASY     ");
		setColorBGTextXY(46, 13, 12, 8, "   MEDIUM    ");
		setColorBGTextXY(46, 15, 12, 0, "    HARD     ");
		break;
	case 2:
		setColorBGTextXY(46, 11, 12, 0, "    EASY     ");
		setColorBGTextXY(46, 13, 12, 0, "   MEDIUM    ");
		setColorBGTextXY(46, 15, 12, 8, "    HARD     ");
		break;
	}
	XuLiSuKien();
}
void Description()
{
	system("cls");
	MainLine();
	setColorBGTextXY(44, 7, 12, 0, "WELCOME TO MY GAME!"); 
	setColorBGTextXY(20, 9, 12, 0, "THIS IS MINESWIPPER!");
	setColorBGTextXY(50, 9, 6, 0, "BUTTONS:");
	setColorBGTextXY(50, 10, 12, 0, "Z          : OPEN CELL           ");
	setColorBGTextXY(50, 11, 12, 0, "X          : FLAGGING/REMOVE FLAG");
	setColorBGTextXY(50, 12, 12, 0, "S          : CHANGE THE SONG     ");
	setColorBGTextXY(50, 13, 12, 0, "ESC        : BACK TO MENU        ");
	setColorBGTextXY(50, 14, 12, 0, "ENTER      : CHOOSE              ");
	setColorBGTextXY(50, 15, 12, 0, "ARROW KEY  : MOVE THE POINTER    ");

	setColorBGTextXY(50, 10, 5, 0, "Z");
	setColorBGTextXY(50, 11, 5, 0, "X");
	setColorBGTextXY(50, 12, 5, 0, "S");
	setColorBGTextXY(50, 13, 5, 0, "ESC");
	setColorBGTextXY(50, 14, 5, 0, "ENTER");
	setColorBGTextXY(50, 15, 5, 0, "ARROW KEY");

	setColorBGTextXY(36, 17, 12, 0, "WISH YOU HAPPY GAMING AND GOOD LUCK!");
	setColorBGTextXY(36, 19, 9, 0, "PRESS ESCAPE BUTTON TO BACK TO MENU.");
}

void music()
{
	PlaySound(NULL, NULL, NULL);
	srand((short)time(NULL));
	short sound = rand() % 24;
	
	switch (sound)
	{
	case 0:
		PlaySound(TEXT("Toradora.wav"), NULL, SND_ASYNC|SND_LOOP);
		break;
	case 1:
		PlaySound(TEXT("Attention.wav"), NULL, SND_ASYNC|SND_LOOP);
		break;
	case 2:
		PlaySound(TEXT("Black_Magic.wav"), NULL, SND_ASYNC|SND_LOOP);
		break;
	case 3:
        PlaySound(TEXT("Give_Your_Heart_A_Break.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
	case 4:
		PlaySound(TEXT("HAY_TRAO_CHO_ANH.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
	case 5:
		PlaySound(TEXT("Light_It_Up.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
	case 6:
		PlaySound(TEXT("renai.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
	case 7:
		PlaySound(TEXT("ROOM_112.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
	case 8:
		PlaySound(TEXT("Senorita.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
	case 9:
		PlaySound(TEXT("Every_Time_We_Talk.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
	case 10:
		PlaySound(TEXT("Give_Your_Heart_A_Break.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
	case 11:
		PlaySound(TEXT("Black_Magic.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
	case 12:
		PlaySound(TEXT("How_To_Be_A_Heartbreak.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
	case 13:
		PlaySound(TEXT("Heart_Attack.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
	case 14:
		PlaySound(TEXT("Hoodie.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
	case 15:
		PlaySound(TEXT("I_Really_Like_You.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
	case 16:
		PlaySound(TEXT("IDOL.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
	case 17:
		PlaySound(TEXT("If_I_Was_A_Boyfriend.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
	case 18:
		PlaySound(TEXT("Lily.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
	case 19:
		PlaySound(TEXT("On_My_Way.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
	case 20:
		PlaySound(TEXT("Run_Devil_Run.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
	case 21:
		PlaySound(TEXT("Sweet_But_Psycho.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
	case 22:
		PlaySound(TEXT("True_Damage.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
	case 23:
		PlaySound(TEXT("What_Makes_You_Beautiful.wav"), NULL, SND_ASYNC | SND_LOOP);
		break;
	}
	
}