#include<Bangtal.h>

SceneID scene1, scene2,scene3,scene4;
ObjectID knight1, knight2, start, monster, attack,restart,restart2,end;

int x = 100, y = 175;
int z = 1000, c = 175;
int q , e ;
int dx = 0, dy = 0, dq = 0;

#define ANIMATION_TIME		0.01f
#define ANIMATION_STEP		6

void startGame() {
	showObject(monster);
	enterScene(scene2);
	x = 100, y = 175;
}

void endGame() {
	enterScene(scene3);
	showObject(restart);
}

void win() {
	enterScene(scene4);
	showObject(end);
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == start) {
		startGame();
	}
	else if (object == restart) {
		enterScene(scene1);
	}
	else if (object == end) {
		
	}
}

void keyboardCallback(KeyCode code, KeyState state) {
	if (code == KeyCode::KEY_W) {
		dy += (state == KeyState::KEY_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
		hideObject(attack);
	}
	else if (code == KeyCode::KEY_S) {
		dy -= (state == KeyState::KEY_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
		hideObject(attack);
	}
	else if (code == KeyCode::KEY_D) {
		hideObject(knight2);
		showObject(knight1);
		hideObject(attack);
		dx += (state == KeyState::KEY_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
	}
	else if (code == KeyCode::KEY_A) {
		hideObject(knight1);
		showObject(knight2);
		hideObject(attack);
		dx -= (state == KeyState::KEY_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
	}
	else if (code == KeyCode::KEY_J) {
		dq += (state == KeyState::KEY_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
		locateObject(attack, scene2, q = x +20, e = y+20);
		showObject(attack);

		if (q + 50 >= z) {
			win();
		
		}
		
	}
}

void timerCallback(TimerID timer)
{
	x += dx; y += dy; q += dq;
	locateObject(knight1, scene2, x, y);
	locateObject(knight2, scene2, x, y);
	locateObject(attack, scene2, q = x +20, e = y+20);
	
	setTimer(timer, ANIMATION_TIME);
	startTimer(timer);

		if (x < 0) {
		x = 1;
	}
		else if (x > 1200) {
		x = 1199;
	}
		else if (y < 0) {
		y = 1;
	}
		else if (y > 350) {
		y = 349;
	}
		else if (x == z) {
			endGame();
		}
		else if (q > x) {
			q = x;
		}
}

int main() {
	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);
	setKeyboardCallback(keyboardCallback);

	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	scene1 = createScene("Knight", "게임배경.png");
	scene2 = createScene("전투 장면", "게임배경-2.png");
	scene3 = createScene("gameover","gameover.png");
	scene4 = createScene("YOU WIN!!!", "youwin.png");

	knight1 = createObject("주인공-우측.png");
	locateObject(knight1, scene2, x, y);
	showObject(knight1);

	knight2 = createObject("주인공-좌.png");
	locateObject(knight2, scene2, x, y);

	monster = createObject("괴물.png");
	locateObject(monster, scene2, z, c);
	showObject(monster);

	attack = createObject("무기.png");
	locateObject(attack, scene2, q ,e );

	start = createObject("start.png");
	locateObject(start, scene1, 275, 5);
	showObject(start);

	restart = createObject("restart.png");
	locateObject(restart, scene3, 140, -40);

	TimerID timer = createTimer(ANIMATION_TIME);
	startTimer(timer);

	SoundID sound = createSound("music.MP3");
	playSound(sound);

	startGame(scene1);
}