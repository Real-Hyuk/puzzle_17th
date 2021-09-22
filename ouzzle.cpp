#include <bangtal>
#define _CRT_SECURE_NO_WARNINGS
using namespace bangtal;


ScenePtr scene;
ObjectPtr game_board[16];

int blank;
int game_index(ObjectPtr piece) {
	for (int i = 0; i < 16; i++)
		if (game_board[i] == piece)	return i;
	return -1;

}

int index_X(int index) {
	return  300 + 150 * (index % 4);
}

int index_Y(int index) {
	return  470 - 150 * (index / 4);
}

void game_move(int index) {
	//index와 blank를 swap 
	auto piece = game_board[index];
	game_board[index] = game_board[blank];
	game_board[index]->locate(scene, index_X(index), index_Y(index));
	game_board[blank] = piece; //오류
	game_board[blank]->locate(scene, index_X(blank), index_Y(blank));
	blank = index;
}

void init_game() {
	auto scene = Scene::create("퍼즐 메인", "Images/배경.png");


	char path[20];

	for (int i = 0; i < 16; i++) {
		sprintf_s(path, "Images/%d.png", i + 1);
		game_board[i] = Object::create(path, scene, index_X(i), index_Y(i));
		game_board[i]->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
			// piece로부터 index알아내는 함수
			int index = game_index(piece); //클릭 된 object가 board의 몇번째인지 반환
			game_move(index); 

			return true;
			});
	}
	blank = 15;
	game_board[blank]->hide();

	startGame(scene);
}






int main() {
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	init_game();




	return 0;
}