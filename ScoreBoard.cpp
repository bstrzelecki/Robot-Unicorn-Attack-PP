#include "ScoreBoard.h"

void ScoreBoard::Save(char* name, int score)
{
	FILE* file = fopen("scores.txt", "a");
	char scoreText[256];
	sprintf(scoreText, "%s %d\n", name, score);
	fputs(scoreText, file);
	fclose(file);
}

void ScoreBoard::Load()
{
	FILE* file = fopen("scores.txt", "r");
	if (file == NULL)return;
	int score;
	char name[NAME_MAX_LENGHT]="";
	count = 0;
	while (fscanf(file, "%s %d", name, &score) == 2) {
		strcpy(names[count], name);
		scores[count] = score;
		count++;
	}
	fclose(file);

	Sort();
}

void ScoreBoard::Move(int delta)
{
	offset += delta;
	if (offset > count - PAGE_SIZE) {
		offset = count - PAGE_SIZE;
	}
	if (offset < 0)
	{
		offset = 0;
	}
}

void ScoreBoard::Sort()
{
	do {
		int moved = 0;
		for (int i = 0; i < count - 1; i++) {
			if (scores[i] < scores[i + 1]) {
				Swap(i, i + 1);
				moved = 1;
			}
		}
		if (!moved)break;
	} while (true);
}

void ScoreBoard::Swap(int a, int b)
{
	char buff[NAME_MAX_LENGHT];
	strcpy(buff, names[a]);
	strcpy(names[a], names[b]);
	strcpy(names[b], buff);
	int ibuff = scores[a];
	scores[a] = scores[b];
	scores[b] = ibuff;
}

ScoreBoard::ScoreBoard()
{
	Load();
}

void ScoreBoard::Render(double delta, RenderBatch* batch)
{
	int lenght = count < PAGE_SIZE ? count : PAGE_SIZE;
	char textBuff[BUFFSIZE];
	int c = 1;
	sprintf(textBuff, "%s", "Name .................... Score");
	batch->DrawString(30, 80, textBuff);
	for (int i = offset; i < lenght + offset; i++,c++) {
		sprintf(textBuff, "%s", names[i]);
		batch->DrawString(30, 80 + c * 10, textBuff);
		sprintf(textBuff, "%d", scores[i]);
		batch->DrawString(30 + 8 * NAME_MAX_LENGHT, 80 + c * 10, textBuff);
	}
	sprintf(textBuff, "%s", "Arrow Up/Down");
	batch->DrawString(80, 80 + c * 10, textBuff);
}

void ScoreBoard::Update(double delta)
{
}
