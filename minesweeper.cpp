#define _CRT_SECURE_NO_WARNINGS

#include <bangtal>
using namespace bangtal;

#include <iostream>
using namespace std;

#define TRAPby 16

ScenePtr stage1, stage2, stage3, stage4;

ObjectPtr restart;
ObjectPtr trap1[4][4], trap2[6][6], trap3[8][8], trap4[8][8], trap5[TRAPby][TRAPby]; //[row][col]
ObjectPtr restartButton1, restartButton2, restartButton3, restartButton4;

TimerPtr timer1, timer2, timer3, timer4;

int trap; //함정 개수
int trap_hint[TRAPby][TRAPby]; //[col][row]
int click[TRAPby][TRAPby]; //클릭상태, 1: 오픈, 2: 플래그, [row][col]

int flag = 0; //깃발개수
int a;
int mode = 0; //지뢰, 깃발 선택
int state = 0; //0: 게임중, 1: 게임중x, -1: 게임 종료

int index_to_x(int index) {
	return 304 + 84 * index;
}

int index_to_y(int index) {
	return 590 - 84 * index;
}

//피스에서 인덱스 추출
int game_index1(ObjectPtr piece) { 
	for (int i = 0; i < 4;i++) {
		for (int j = 0; j < 4;j++) {
			if (trap1[i][j] == piece) return i * 10 + j;
		}
	}
	return -1; //INVALID PIECE
}
int game_index2(ObjectPtr piece) { //피스에서 인덱스 추출
	for (int i = 0; i < 6;i++) {
		for (int j = 0; j < 6;j++) {
			if (trap2[i][j] == piece) return i * 10 + j;
		}
	}
	return -1; //INVALID PIECE
}
int game_index3(ObjectPtr piece) { //피스에서 인덱스 추출
	for (int i = 0; i < 8;i++) {
		for (int j = 0; j < 8;j++) {
			if (trap3[i][j] == piece) return i * 10 + j;
		}
	}
	return -1; //INVALID PIECE
}
int game_index4(ObjectPtr piece) { //피스에서 인덱스 추출
	for (int i = 0; i < 8;i++) {
		for (int j = 0; j < 8;j++) {
			if (trap4[i][j] == piece) return i * 10 + j;
		}
	}
	return -1; //INVALID PIECE
}
int game_index5(ObjectPtr piece) { //피스에서 인덱스 추출
	for (int i = 0; i < 16;i++) {
		for (int j = 0; j < 16;j++) {
			if (trap5[i][j] == piece) return i * 10 + j;
		}
	}
	return -1; //INVALID PIECE
}

//폭탄 모드 상태로 클릭 시 셀 확인
void show1(int row, int col, int row_size, int col_size) {
	char path[20];
	if (col < col_size && col >= 0 && row < row_size && row >= 0) {
		if (click[row][col] == 0) {
			//cout << "row: " << row << "col: " << col << endl;
			if (trap_hint[col][row] == 0) {
				trap1[row][col]->setImage("Images/클릭.png");
				click[row][col] = 1;
				//cout << 222 << endl;
				for (int a = -1; a < 2; a++) { //주변 8칸 둘러보기 위한 for 문
					for (int b = -1; b < 2; b++) {
						if (a != 0 || b != 0)
							show1(row + b, col + a, row_size, col_size);
					}
				}
			}
			else if (trap_hint[col][row] != -1) {
				//cout << 333 << endl;
				sprintf(path, "Images/숫자_%d.png", trap_hint[col][row]);
				trap1[row][col]->setImage(path);
				click[row][col] = 1;
			}
		}
	}
}

void show2(int row, int col, int row_size, int col_size) {
	char path[20];
	if (col < col_size && col >= 0 && row < row_size && row >= 0) {
		if (click[row][col] == 0) {
			cout << "row: " << row << "col: " << col << endl;
			if (trap_hint[col][row] == 0) {
				trap2[row][col]->setImage("Images/클릭.png");
				click[row][col] = 1;
				cout << 222 << endl;
				for (int a = -1; a < 2; a++) { //주변 8칸 둘러보기 위한 for 문
					for (int b = -1; b < 2; b++) {
						if (a != 0 || b != 0)
							show2(row + b, col + a, row_size, col_size);
					}
				}
			}
			else if (trap_hint[col][row] != -1) {
				cout << 333 << endl;
				sprintf(path, "Images/숫자_%d.png", trap_hint[col][row]);
				trap2[row][col]->setImage(path);
				click[row][col] = 1;
			}
		}
	}
}

void show3(int row, int col, int row_size, int col_size) {
	char path[20];
	if (col < col_size && col >= 0 && row < row_size && row >= 0) {
		if (click[row][col] == 0) {
			cout << "row: " << row << "col: " << col << endl;
			if (trap_hint[col][row] == 0) {
				trap3[row][col]->setImage("Images/클릭.png");
				click[row][col] = 1;
				cout << 222 << endl;
				for (int a = -1; a < 2; a++) { //주변 8칸 둘러보기 위한 for 문
					for (int b = -1; b < 2; b++) {
						if (a != 0 || b != 0)
							show3(row + b, col + a, row_size, col_size);
					}
				}
			}
			else if (trap_hint[col][row] != -1) {
				cout << 333 << endl;
				sprintf(path, "Images/숫자_%d.png", trap_hint[col][row]);
				trap3[row][col]->setImage(path);
				click[row][col] = 1;
			}
		}
	}
}

void show4(int row, int col, int row_size, int col_size) {
	char path[20];
	if (col < col_size && col >= 0 && row < row_size && row >= 0) {
		if (click[row][col] == 0) {
			cout << "row: " << row << "col: " << col << endl;
			if (trap_hint[col][row] == 0) {
				trap4[row][col]->setImage("Images/클릭.png");
				click[row][col] = 1;
				cout << 222 << endl;
				for (int a = -1; a < 2; a++) { //주변 8칸 둘러보기 위한 for 문
					for (int b = -1; b < 2; b++) {
						if (a != 0 || b != 0)
							show4(row + b, col + a, row_size, col_size);
					}
				}
			}
			else if (trap_hint[col][row] != -1) {
				cout << 333 << endl;
				sprintf(path, "Images/숫자_%d.png", trap_hint[col][row]);
				trap4[row][col]->setImage(path);
				click[row][col] = 1;
			}
		}
	}
}

void show5(int row, int col, int row_size, int col_size) {
	char path[20];
	if (col < col_size && col >= 0 && row < row_size && row >= 0) {
		if (click[row][col] == 0) {
			cout << "row: " << row << "col: " << col << endl;
			if (trap_hint[col][row] == 0) {
				trap5[row][col]->setImage("Images/클릭.png");
				click[row][col] = 1;
				cout << 222 << endl;
				for (int a = -1; a < 2; a++) { //주변 8칸 둘러보기 위한 for 문
					for (int b = -1; b < 2; b++) {
						if (a != 0 || b != 0)
							show5(row + b, col + a, row_size, col_size);
					}
				}
			}
			else if (trap_hint[col][row] != -1) {
				cout << 333 << endl;
				sprintf(path, "Images/숫자_%d.png", trap_hint[col][row]);
				trap5[row][col]->setImage(path);
				click[row][col] = 1;
			}
		}
	}
}

//폭탄 랜덤 생성, 폭탄 힌트 생성
void random(int row_size, int col_size, int trap, int trap_hint[][TRAPby]) {
	int trap_place[TRAPby] = { 0, };
	int flag1;
	int randint;

	int i=0;
	while (i < trap) {
		flag1 = 0; //0이면 중복 없음
		randint = rand() % (row_size * col_size) + 1;
		for (int j = 0; j < i; j++) {
			if (randint == trap_place[j]) {
				cout << "i: " << i << " j: " << j << " randint " << j << endl;
				flag1 = 1;
			}
		}
		if (flag1 == 0) {
			trap_place[i] = randint;
			i++;
		}
	}

	for (i = 0; i < trap; i++) { //폭탄 랜덤 생성
		while (1) {
			flag1 = 0; //0이면 중복 없음
			randint = rand() % (row_size * col_size);
			for (int j = 0; j < i + 1; j++) {
				if (randint == trap_place[j]) {
					cout << "i: " << i << " j: " << j << " randint " << randint << endl;
					flag1 = 1;
				}
			}
			if (flag1 == 0) break;
		}
		trap_place[i] = randint;
		cout << " randint: " << randint << endl;
	}

	int row, col;
	for (i = 0; i < trap; i++) { //폭탄 위치 기록 (-1)
		row = trap_place[i] % row_size;
		col = trap_place[i] / col_size;
		//cout << trap_place[i] << ' ' << row << ' ' << col << endl;
		trap_hint[col][row] = -1;
		//cout << trap_hint[col][row] << endl;
	}

	//폭탄 주변에, 주변 폭탄의 개수에 대한 힌트 추가
	for (i = 0; i < TRAPby; i++) {
		for (int j = 0; j < TRAPby; j++) { //j: row, i: col
			if (trap_hint[i][j] != -1) {
				for (int a = -1; a < 2; a++) { //주변 8칸 둘러보기 위한 for 문
					for (int b = -1; b < 2; b++) {
						if (i + a < col_size && i + a >= 0 && j + b < row_size && j + b >= 0)
							if (trap_hint[i + a][j + b] == -1)
								trap_hint[i][j]++;
					}
				}
			}
		}
	}
	int sum=0;
	for (i = 0; i < col_size; i++) {
		for (int j = 0; j < col_size; j++) {
			cout << trap_hint[i][j] << ' ';
			if (trap_hint[i][j] == -1)
				sum++;
		}
		cout << endl;
	}
	cout << sum << endl;
}

//초기화
void init() { 
	for (int i = 0; i < TRAPby; i++) {
		for (int j = 0; j < TRAPby; j++) {
			click[i][j] = 0;
			trap_hint[i][j] = 0;
		}
	}
	flag = 0; //깃발개수
	mode = 0; //지뢰, 깃발 선택
	state = 0; //0: 게임중, 1: 게임중x, -1: 게임 종료
}

int main() {
    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	srand((unsigned int)time(NULL));

	char path[20];
	int slidenum = 1; //스토리 슬라이드 순서

	ScenePtr ending = Scene::create("엔딩", "Images/엔딩화면.png");
	ScenePtr scene1 = Scene::create("메인화면", "Images/시작화면.png");
	ScenePtr scene2 = Scene::create("스토리", "Images/p1.png");
	ScenePtr scene3 = Scene::create("클래식", "Images/배경.png");

	ScenePtr mission1 = Scene::create("미션1", "Images/LV1_미션배경.png");
	ScenePtr mission2 = Scene::create("미션1", "Images/LV2_미션배경.png");
	ScenePtr mission3 = Scene::create("미션1", "Images/LV3_미션배경.png");
	ScenePtr mission4 = Scene::create("미션1", "Images/LV4_미션배경.png");

	stage1 = Scene::create("스테이지1", "Images/배경_LV1.png");
	stage2 = Scene::create("스테이지2", "Images/배경_LV2.png");
	stage3 = Scene::create("스테이지3", "Images/배경_LV3.png");
	stage4 = Scene::create("스테이지4", "Images/배경_LV4.png");

	auto slide = Object::create("Images/빈화면.png", scene2, 0, 0);
	slide->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
		slidenum++;
		if (slidenum == 9)
			mission1->enter();
		sprintf(path, "Images/p%d.png", slidenum);
		piece->setImage(path);
		return true;
		});

	timer1 = Timer::create(60.f);
	timer2 = Timer::create(60.f);
	timer3 = Timer::create(60.f);
	timer4 = Timer::create(60.f);

	auto storyButton = Object::create("Images/스토리모드.png", scene1, 415, 200);
	storyButton->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
		scene2->enter();
		return true;
		});
	auto classicButton = Object::create("Images/클래식 모드.png", scene1, 415, 50);
	classicButton->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
		scene3->enter();
		return true;
		});

	auto startButton1 = Object::create("Images/start.png", mission1, 115, 400);
	startButton1->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
		showTimer(timer1);
		stage1->enter();
		return true;
		});
	auto startButton2 = Object::create("Images/start.png", mission2, 115, 400);
	startButton2->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
		showTimer(timer2);
		stage2->enter();
		return true;
		});
	auto startButton3 = Object::create("Images/start.png", mission3, 115, 400);
	startButton3->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
		showTimer(timer3);
		stage3->enter();
		return true;
		});
	auto startButton4 = Object::create("Images/start.png", mission4, 115, 400);
	startButton4->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
		showTimer(timer4);
		stage4->enter();
		return true;
		});
	
	/***  stage 1  ***/
	//trap = 2;
	stage1->setOnEnterCallback([](ScenePtr scene)->bool {
		init();
		random(4, 4, 2, trap_hint);
		return true;
		});

	auto trapnum = Object::create("Images/지뢰개수.png", stage1, 1010, 550);
	trapnum->setScale(.5f);
	auto flagnum = Object::create("Images/깃발개수.png", stage1, 1010, 450);
	flagnum->setScale(.5f);
	auto trap_number = Object::create("Images/지뢰숫자_2.png", stage1, 1155, 560);
	trap_number->setScale(.4f);
	auto flag_number = Object::create("Images/지뢰숫자_0.png", stage1, 1155, 460);
	flag_number->setScale(.4f);

	auto timerIMG = Object::create("Images/타이머.png", stage1, 585, 676);
	timerIMG->setScale(.12f);

	auto flagButton = Object::create("Images/깃발_초록.png", stage1, 1050, 200);
	auto trapButton = Object::create("Images/지뢰누름.png", stage1, 1050, 50);
	flagButton->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
		piece->setImage("Images/깃발누름.png");
		trapButton->setImage("Images/지뢰.png");
		mode = 1;
		return true;
		});
	trapButton->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
		piece->setImage("Images/지뢰누름.png");
		flagButton->setImage("Images/깃발_초록.png");
		mode = 0;
		return true;
		});

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			trap1[i][j] = Object::create("Images/한칸.png", stage1, index_to_x(i+2), index_to_y(j+2)); //i+2, i+3 으로 6*6 4*4
			trap1[i][j]->setScale(.6f);
			trap1[i][j]->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
				trap = 2;
				if (state == 0) {
					timer1->start();
					restartButton1->hide();
					state = 1;
				}
				else if (state == 1) {
					a = game_index1(piece);
					cout << a << endl;

					if (mode == 0) { //지뢰 찾기
						if (trap_hint[a % 10][a / 10] == -1) {
							for (int k = 0; k < 4; k++)
								for (int l = 0; l < 4; l++)
									if (trap_hint[k][l] == -1)
										trap1[l][k]->setImage("Images/지뢰.png");

							showMessage("지뢰를 밟았습니다!");
							state = -1;
							timer1->stop();
							restartButton1->show();
						}
						else
							show1(a / 10, a % 10, 4, 4);
					}
					else { //깃발 꼽기
						if (click[a / 10][a % 10] == 2) {
							click[a / 10][a % 10] = 0;
							piece->setImage("Images/한칸.png");
							flag--;
							sprintf(path, "Images/지뢰숫자_%d.png", flag);
							flag_number->setImage(path);
						}
						else {
							click[a / 10][a % 10] = 2;
							piece->setImage("Images/깃발_초록.png");
							flag++;
							sprintf(path, "Images/지뢰숫자_%d.png", flag);
							flag_number->setImage(path);
						}
					}
				}
				cout << " flag trap" << flag << trap << endl;
				if (flag == trap) {
					cout << "equal!" << flag << trap << endl;
					int clear = 1;
					for (int k = 0; k < 8; k++) {
						for (int l = 0; l < 8; l++) {
							if (trap_hint[k][l] == -1) {
								if (click[l][k] != 2)
									clear = 0;
							}
						}
					}
					if (clear == 1) {
						showMessage("클리어!");
						hideTimer();
						mission2->enter();
						state = -1;
						timer1->stop();
					}
				}

				for (int k = 0; k < 4; k++) {
					for (int l = 0; l < 4; l++) {
						cout << click[l][k] << ' ';
					}
					cout << endl;
				}

				return true;
				});
		}
	}

	restartButton1 = Object::create("Images/restart.png", stage1, 115, 400);
	restartButton1->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
		init();
		random(4, 4, 2, trap_hint);
		flag = 0;
		state = 0;
		timer1->stop();
		timer1->set(60.f);

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				trap1[i][j]->setImage("Images/한칸.png");

		return true;
		});
	restartButton1->hide();

	timer1->setOnTimerCallback([&](auto)->bool {
		timer1->stop();
		showMessage("시간 초과!");
		state = -1;
		restartButton1->show();
		return true;
		});


	/***  stage 2  ***/
	//trap = 4;
	stage2->setOnEnterCallback([](ScenePtr scene)->bool {
		init();
		random(6, 6, 4, trap_hint);
		return true;
		});

	auto trapnum2 = Object::create("Images/지뢰개수.png", stage2, 1010, 550);
	trapnum2->setScale(.5f);
	auto flagnum2 = Object::create("Images/깃발개수.png", stage2, 1010, 450);
	flagnum2->setScale(.5f);
	auto trap_number2 = Object::create("Images/지뢰숫자_4.png", stage2, 1155, 560);
	trap_number2->setScale(.4f);
	auto flag_number2 = Object::create("Images/지뢰숫자_0.png", stage2, 1155, 460);
	flag_number2->setScale(.4f);

	auto timerIMG2 = Object::create("Images/타이머.png", stage2, 585, 676);
	timerIMG2->setScale(.12f);

	auto flagButton2 = Object::create("Images/깃발_초록.png", stage2, 1050, 200);
	auto trapButton2 = Object::create("Images/지뢰누름.png", stage2, 1050, 50);
	flagButton2->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
		piece->setImage("Images/깃발누름.png");
		trapButton2->setImage("Images/지뢰.png");
		mode = 1;
		return true;
		});
	trapButton2->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
		piece->setImage("Images/지뢰누름.png");
		flagButton2->setImage("Images/깃발_초록.png");
		mode = 0;
		return true;
		});

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			trap2[i][j] = Object::create("Images/한칸.png", stage2, index_to_x(i + 1), index_to_y(j + 1)); //i+2, i+3 으로 6*6 4*4
			trap2[i][j]->setScale(.6f);
			trap2[i][j]->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
				trap = 4;
				if (state == 0) {
					timer2->start();
					restartButton2->hide();
					state = 1;
				}
				else if (state == 1) {
					a = game_index2(piece);
					cout << a << endl;

					if (mode == 0) { //지뢰 찾기
						if (trap_hint[a % 10][a / 10] == -1) {
							for (int k = 0; k < 6; k++)
								for (int l = 0; l < 6; l++)
									if (trap_hint[k][l] == -1)
										trap2[l][k]->setImage("Images/지뢰.png");

							showMessage("지뢰를 밟았습니다!");
							state = -1;
							timer2->stop();
							restartButton2->show();
						}
						else
							show2(a / 10, a % 10, 6, 6);
					}
					else { //깃발 꼽기
						if (click[a / 10][a % 10] == 2) {
							click[a / 10][a % 10] = 0;
							piece->setImage("Images/한칸.png");
							flag--;
							sprintf(path, "Images/지뢰숫자_%d.png", flag);
							flag_number2->setImage(path);
						}
						else {
							click[a / 10][a % 10] = 2;
							piece->setImage("Images/깃발_초록.png");
							flag++;
							sprintf(path, "Images/지뢰숫자_%d.png", flag);
							flag_number2->setImage(path);
						}
					}
				}
				cout << " flag trap" << flag << trap << endl;
				if (flag == trap) {
					cout << "equal!" << flag << trap << endl;
					int clear = 1;
					for (int k = 0; k < 6; k++) {
						for (int l = 0; l < 6; l++) {
							if (trap_hint[k][l] == -1) {
								if (click[l][k] != 2)
									clear = 0;
							}
						}
					}
					if (clear == 1) {
						showMessage("클리어!");
						hideTimer();
						mission3->enter();
						state = -1;
						timer2->stop();
					}
				}

				for (int k = 0; k < 6; k++) {
					for (int l = 0; l < 6; l++) {
						cout << click[l][k] << ' ';
					}
					cout << endl;
				}

				return true;
				});
		}
	}

	restartButton2 = Object::create("Images/restart.png", stage2, 115, 400);
	restartButton2->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
		init();
		random(6, 6, 4, trap_hint);
		flag = 0;
		state = 0;
		timer2->stop();
		timer2->set(60.f);

		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 6; j++)
				trap2[i][j]->setImage("Images/한칸.png");

		return true;
		});
	restartButton2->hide();

	timer2->setOnTimerCallback([&](auto)->bool {
		timer2->stop();
		showMessage("시간 초과!");
		state = -1;
		restartButton2->show();
		return true;
		});

	/***  stage 3  ***/
	//trap = 7;
	stage3->setOnEnterCallback([](ScenePtr scene)->bool {
		init();
		random(8, 8, 7, trap_hint);
		return true;
		});

	auto trapnum3 = Object::create("Images/지뢰개수.png", stage3, 1010, 550);
	trapnum3->setScale(.5f);
	auto flagnum3 = Object::create("Images/깃발개수.png", stage3, 1010, 450);
	flagnum3->setScale(.5f);
	auto trap_number3 = Object::create("Images/지뢰숫자_7.png", stage3, 1155, 560);
	trap_number3->setScale(.4f);
	auto flag_number3 = Object::create("Images/지뢰숫자_0.png", stage3, 1155, 460);
	flag_number3->setScale(.4f);

	auto timerIMG3 = Object::create("Images/타이머.png", stage3, 585, 676);
	timerIMG3->setScale(.12f);

	auto flagButton3 = Object::create("Images/깃발_초록.png", stage3, 1050, 200);
	auto trapButton3 = Object::create("Images/지뢰누름.png", stage3, 1050, 50);
	flagButton3->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
		piece->setImage("Images/깃발누름.png");
		trapButton3->setImage("Images/지뢰.png");
		mode = 1;
		return true;
		});
	trapButton3->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
		piece->setImage("Images/지뢰누름.png");
		flagButton3->setImage("Images/깃발_초록.png");
		mode = 0;
		return true;
		});

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			trap3[i][j] = Object::create("Images/한칸.png", stage3, index_to_x(i), index_to_y(j)); //i+2, i+3 으로 6*6 4*4
			trap3[i][j]->setScale(.6f);
			trap3[i][j]->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
				trap = 7;
				if (state == 0) {
					timer3->start();
					restartButton3->hide();
					state = 1;
				}
				else if (state == 1) {
					a = game_index3(piece);
					cout << a << endl;

					if (mode == 0) { //지뢰 찾기
						if (trap_hint[a % 10][a / 10] == -1) {
							for (int k = 0; k < 8; k++)
								for (int l = 0; l < 8; l++)
									if (trap_hint[k][l] == -1)
										trap3[l][k]->setImage("Images/지뢰.png");

							showMessage("지뢰를 밟았습니다!");
							state = -1;
							timer3->stop();
							restartButton3->show();
						}
						else
							show3(a / 10, a % 10, 8, 8);
					}
					else { //깃발 꼽기
						if (click[a / 10][a % 10] == 2) {
							click[a / 10][a % 10] = 0;
							piece->setImage("Images/한칸.png");
							flag--;
							sprintf(path, "Images/지뢰숫자_%d.png", flag);
							flag_number3->setImage(path);
						}
						else {
							click[a / 10][a % 10] = 2;
							piece->setImage("Images/깃발_초록.png");
							flag++;
							sprintf(path, "Images/지뢰숫자_%d.png", flag);
							flag_number3->setImage(path);
						}
					}
				}
				cout << " flag trap" << flag << trap << endl;
				if (flag == trap) {
					cout << "equal!" << flag << trap << endl;
					int clear = 1;
					for (int k = 0; k < 8; k++) {
						for (int l = 0; l < 8; l++) {
							if (trap_hint[k][l] == -1) {
								if (click[l][k] != 2)
									clear = 0;
							}
						}
					}
					if (clear == 1) {
						showMessage("클리어!");
						hideTimer();
						mission4->enter();
						state = -1;
						timer3->stop();
					}
				}

				for (int k = 0; k < 8; k++) {
					for (int l = 0; l < 8; l++) {
						cout << click[l][k] << ' ';
					}
					cout << endl;
				}

				return true;
				});
		}
	}

	restartButton3 = Object::create("Images/restart.png", stage3, 115, 400);
	restartButton3->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
		init();
		random(8, 8, 7, trap_hint);
		flag = 0;
		state = 0;
		timer3->stop();
		timer3->set(60.f);

		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				trap3[i][j]->setImage("Images/한칸.png");

		return true;
		});
	restartButton3->hide();

	timer3->setOnTimerCallback([&](auto)->bool {
		timer3->stop();
		showMessage("시간 초과!");
		state = -1;
		restartButton3->show();
		return true;
		});

	/***  stage 4  ***/
	//trap = 9;
	stage4->setOnEnterCallback([](ScenePtr scene)->bool {
		init();
		random(8, 8, 9, trap_hint);
		return true;
		});

	auto trapnum4 = Object::create("Images/지뢰개수.png", stage4, 1010, 550);
	trapnum4->setScale(.5f);
	auto flagnum4 = Object::create("Images/깃발개수.png", stage4, 1010, 450);
	flagnum4->setScale(.5f);
	auto trap_number4 = Object::create("Images/지뢰숫자_9.png", stage4, 1155, 560);
	trap_number4->setScale(.4f);
	auto flag_number4 = Object::create("Images/지뢰숫자_0.png", stage4, 1155, 460);
	flag_number4->setScale(.4f);

	auto timerIMG4 = Object::create("Images/타이머.png", stage4, 585, 676);
	timerIMG4->setScale(.12f);

	auto flagButton4 = Object::create("Images/깃발_초록.png", stage4, 1050, 200);
	auto trapButton4 = Object::create("Images/지뢰누름.png", stage4, 1050, 50);
	flagButton4->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
		piece->setImage("Images/깃발누름.png");
		trapButton4->setImage("Images/지뢰.png");
		mode = 1;
		return true;
		});
	trapButton4->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
		piece->setImage("Images/지뢰누름.png");
		flagButton4->setImage("Images/깃발_초록.png");
		mode = 0;
		return true;
		});

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			trap4[i][j] = Object::create("Images/한칸.png", stage4, index_to_x(i), index_to_y(j)); //i+2, i+3 으로 6*6 4*4
			trap4[i][j]->setScale(.6f);
			trap4[i][j]->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
				trap = 9;
				if (state == 0) {
					timer4->start();
					restartButton4->hide();
					state = 1;
				}
				else if (state == 1) {
					a = game_index4(piece);
					cout << a << endl;

					if (mode == 0) { //지뢰 찾기
						if (trap_hint[a % 10][a / 10] == -1) {
							for (int k = 0; k < 8; k++)
								for (int l = 0; l < 8; l++)
									if (trap_hint[k][l] == -1)
										trap4[l][k]->setImage("Images/지뢰.png");

							showMessage("지뢰를 밟았습니다!");
							state = -1;
							timer4->stop();
							restartButton4->show();
						}
						else
							show4(a / 10, a % 10, 8, 8);
					}
					else { //깃발 꼽기
						if (click[a / 10][a % 10] == 2) {
							click[a / 10][a % 10] = 0;
							piece->setImage("Images/한칸.png");
							flag--;
							sprintf(path, "Images/지뢰숫자_%d.png", flag);
							flag_number4->setImage(path);
						}
						else {
							click[a / 10][a % 10] = 2;
							piece->setImage("Images/깃발_초록.png");
							flag++;
							sprintf(path, "Images/지뢰숫자_%d.png", flag);
							flag_number4->setImage(path);
						}
					}
				}
				cout << " flag trap" << flag << trap << endl;
				if (flag == trap) {
					cout << "equal!" << flag << trap << endl;
					int clear = 1;
					for (int k = 0; k < 8; k++) {
						for (int l = 0; l < 8; l++) {
							if (trap_hint[k][l] == -1) {
								if (click[l][k] != 2)
									clear = 0;
							}
						}
					}
					if (clear == 1) {
						showMessage("클리어!");
						hideTimer();
						ending->enter();
						state = -1;
						timer4->stop();
					}
				}

				for (int k = 0; k < 8; k++) {
					for (int l = 0; l < 8; l++) {
						cout << click[l][k] << ' ';
					}
					cout << endl;
				}

				return true;
				});
		}
	}

	restartButton4 = Object::create("Images/restart.png", stage4, 115, 400);
	restartButton4->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
		init();
		random(8, 8, 9, trap_hint);
		flag = 0;
		state = 0;
		timer4->stop();
		timer4->set(60.f);

		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				trap4[i][j]->setImage("Images/한칸.png");

		return true;
		});
	restartButton4->hide();

	timer4->setOnTimerCallback([&](auto)->bool {
		timer4->stop();
		showMessage("시간 초과!");
		state = -1;
		restartButton4->show();
		return true;
		});


    startGame(scene1);

	return 0;
}