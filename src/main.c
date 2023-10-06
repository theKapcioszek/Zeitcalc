#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <raylib.h>

#define WWINDOW 1280
#define HWINDOW 720
//#define WWINDOW 1920
//#define HWINDOW 1080

#define WWCENTER (WWINDOW / 2)
#define HWCENTER (HWINDOW / 2)

#define WROW ((WWINDOW / 100)*40)
#define HROW ((HWINDOW / 100)*6)

#define WBUT ((WWINDOW / 100)*19)
#define HBUT ((HWINDOW / 100)*6)

#define MAX_STRING_LENGTH 10

#define COLS 10
#define ROWS 365

typedef struct {

  int posx;
  int posy;
  int width;
  int height;
  int centerw;
  int centerh;
  char *text;
  //char *date;

} TextRow;

TextRow NewTextRow(char *text, int posx, int posy){
  TextRow row;
  row.posx = posx;
  row.posy = posy;
  row.width = WROW;
  row.height = HROW;
  row.centerw = posx + (WROW / 2);
  row.centerh = posy + (HROW / 2);
  row.text = text;
  //row.date = date;

  return row;
}

TextRow NewButton(char *text, int posx, int posy, int width, int height){
  TextRow button;
  button.posx = posx;
  button.posy = posy;
  button.width = width;
  button.height = height;
  button.centerw = posx + (width / 2);
  button.centerh = posy + (height / 2);
  button.text = text;
  //button.date = NULL;

  return button;
}

void DrawRow(TextRow row, char* text,int fontSize){

  DrawRectangle(row.posx, row.posy, row.width, row.height, LIGHTGRAY);
  if(row.width != WROW){
    DrawText(row.text, row.centerw - (MeasureText(row.text,fontSize) / 2), row.centerh - (fontSize / 2), fontSize, BLACK);
  }
  else{
    DrawText(text, row.centerw - (MeasureText(text,fontSize) / 2), row.centerh - (fontSize / 2), fontSize, BLACK);
  }

  return;
}
// GLOBALS

char chpTextBuffer[MAX_STRING_LENGTH + 1] = "\0";
int iLetterCount = 0;

char* (*array)[COLS];

int iIndexOfRow = 0;
int iIndexOfPage = 0;

int iSumCurPage = 0;
int iSumLastPage = 0;
int iSumAll = 0;

int iPosyStart = (HWCENTER - (HROW / 2) - (HROW + 10)*6);

char *chpIndexOfRow;

// GLOBALS

// LOGIC SECTION

void slice(const char* str, char* result, size_t start, size_t end)
{
    strncpy(result, str + start, end - start);
} // https://stackoverflow.com/questions/26620388/c-substrings-c-string-slicing

void ResetInput(){

  array[iIndexOfPage][iIndexOfRow] = malloc(sizeof(chpTextBuffer));
  strcpy(array[iIndexOfPage][iIndexOfRow],chpTextBuffer);

  for (int i = 0; i < MAX_STRING_LENGTH + 1 ; i++) {
    chpTextBuffer[i] = '\0';
  }

  iLetterCount = 0;

  return;
}

void CalculateSumCurPage(){


    iSumCurPage = 0;

    for(int i = 0; i <= 9; i++){

      char *chpParseBuffer = array[iIndexOfPage][i];

      if(strchr(chpParseBuffer,':') != NULL){

        char* chpWhereColon = strchr(chpParseBuffer,':');
        int iIndexOfColon = (int)(chpWhereColon - chpParseBuffer);

        char chpResult1[iIndexOfColon];
        slice(chpParseBuffer,chpResult1,0,iIndexOfColon);

        char chpResult2[(strlen(chpParseBuffer)) - iIndexOfColon];
        slice(chpParseBuffer,chpResult2,iIndexOfColon + 1,strlen(chpParseBuffer));

        iSumCurPage = iSumCurPage + (atoi(chpResult1)*60) + atoi(chpResult2);
      }
      else{
        iSumCurPage = iSumCurPage + atoi(chpParseBuffer);
      }

    }

  return;
}

void CalculateSumLastPage(){

  iSumLastPage = iSumCurPage;

  return;
}

void CalculateSumAll(bool delete){

  if(delete == true){
    iSumAll = iSumAll - iSumLastPage;
  }
  else{
    iSumAll = iSumAll + iSumLastPage;
  }
  if(iIndexOfPage == 0){
    iSumAll = 0;
  }

  return;
}

void SaveProgress(){

  FILE *fpFile = fopen("cache.txt","w");

  if(fpFile != NULL){

      char chpSaveProgress[sizeof(iSumAll)];
      sprintf(chpSaveProgress, "%d", iSumAll);

      fprintf(fpFile, chpSaveProgress,0);

      fclose(fpFile);

  }
}
// LOGIC SECTION

int main(int argc, char **argv){


  InitWindow(WWINDOW,HWINDOW,"Januszex");
  SetTargetFPS(60);

  array = malloc(sizeof(*array) * ROWS);
  array = malloc(sizeof(char*[ROWS][COLS]));

  for(int i = 0; i < ROWS; i++){
    for(int j = 0;j < COLS; j++){
      array[i][j] = "";
    }
  }

//    array[0][0]="test 1";
//    array[0][1]="test 2";
//    array[0][2]="test 3";
//    array[0][3]="test 4";
//    array[0][4]="test 5";
//    array[0][5]="test 6";
//    array[0][6]="test 7";
//    array[0][7]="test 8";
//    array[0][8]="test 9";
//    array[0][9]="test 10";


//    array[1][0]="test 11";
//    array[1][1]="test 12";
//    array[1][2]="test 13";
//    array[1][3]="test 14";
//    array[1][4]="test 15";
//    array[1][5]="test 16";
//    array[1][6]="test 17";
//    array[1][7]="test 18";
//    array[1][8]="test 19";
//    array[1][9]="test 20";


  while(!WindowShouldClose()){

    BeginDrawing();

// UI SECTION

    ClearBackground(DARKBLUE);

    int iPosyLast = iPosyStart;
    for (int i = 1; i <= 10; i++){

      TextRow trTestMulti = NewTextRow(array[iIndexOfPage][i-1],WWCENTER - (WROW / 2),(iPosyLast + HROW + 10));

      if(iIndexOfRow == i - 1){
        // DrawCircle(WWCENTER - (WROW / 2) - 50, (iPosyLast + HROW + (HROW/2) + 10), 10.0, BLACK);

        Vector2 v3 = {WWCENTER - (HROW / 2) - 250, (iPosyLast + HROW + (HROW / 2) + 10)};
        Vector2 v1 = {WWCENTER - (HROW / 2) - 280, (iPosyLast + HROW + ((HROW/4)) + 2)};
        Vector2 v2 = {WWCENTER - (HROW / 2) - 280, (iPosyLast + HROW + (HROW) + 10)};
        DrawTriangle(v1, v2, v3, BLACK);
      }
    //   char *chpCombinedText;
    //   chpCombinedText = malloc(strlen(trTestMulti.date)+2+strlen(trTestMulti.text)+1);
    //   st
    //   strcat(chpCombinedText,": ");
    //   strcat(chpCombinedText,trTestMulti.text);

      DrawRow(trTestMulti,trTestMulti.text,30);
      iPosyLast = trTestMulti.posy;

    //   free(chpCombinedText);

    }

    TextRow trBackButton = NewButton("<",WWCENTER - (WROW / 2) - (WBUT + 10),(iPosyLast + HROW + 20),WBUT,HBUT);
    DrawRow(trBackButton,NULL,40);
    TextRow trForwardButton = NewButton(">",WWCENTER - (WROW / 2),(iPosyLast + HROW + 20),WBUT,HBUT);
    DrawRow(trForwardButton,NULL,40);

    {
      char chpSumCurPage[sizeof(iSumCurPage)];
      sprintf(chpSumCurPage, "%d", iSumCurPage);

      char *chpCombinedText;
      chpCombinedText = malloc(strlen("Suma: ")+strlen(chpSumCurPage)+strlen(" min"));
      strcpy(chpCombinedText,"Suma: ");
      strcat(chpCombinedText,chpSumCurPage);
      strcat(chpCombinedText," min");

      TextRow trPageResult = NewButton(chpCombinedText,WWCENTER - (WROW / 2) + (WBUT + 25),(iPosyLast + HROW + 20),WBUT,HBUT);
      DrawRow(trPageResult,NULL,20);

      free(chpCombinedText);
    }

    {
      char chpSumAll[sizeof(iSumAll)];
      sprintf(chpSumAll, "%d", iSumAll);

      char *chpCombinedText;
      chpCombinedText = malloc(strlen("Cala Suma: ")+strlen(chpSumAll)+strlen(" min"));
      strcpy(chpCombinedText,"Cala Suma: ");
      strcat(chpCombinedText,chpSumAll);
      strcat(chpCombinedText," min");

      TextRow trAllResult = NewButton(chpCombinedText,WWCENTER - (WROW / 2) + ((WBUT * 2)+35),(iPosyLast + HROW + 20),WBUT,HBUT);
      DrawRow(trAllResult,NULL,20);

      free(chpCombinedText);
    }

    {
      int iTemp1 = ROWS;
      int iTemp2 = iIndexOfPage + 1;

      char chpMaxPages[sizeof(iTemp1)];
      sprintf(chpMaxPages, "%d", iTemp1);
      char chpCurPage[sizeof(iTemp2)];
      sprintf(chpCurPage, "%d", iTemp2);

      char *chpCombinedText;
      chpCombinedText = malloc(strlen(chpMaxPages)+2+strlen(chpCurPage)+1);
      strcpy(chpCombinedText,chpCurPage);
      strcat(chpCombinedText,"/");
      strcat(chpCombinedText,chpMaxPages);

      DrawText(chpCombinedText, WWCENTER - (MeasureText(chpCombinedText,20) / 2), iPosyLast + HROW + 20 + HBUT + 10, 20, BLACK);

      free(chpCombinedText);
    }
// UI SECTION

// INPUT SECTION

    int iPressedKey = GetCharPressed();

    while(iPressedKey > 0){
      if((iPressedKey >=32) && (iPressedKey <= 125) && (iLetterCount <= MAX_STRING_LENGTH)){

        chpTextBuffer[iLetterCount] = (char)iPressedKey;
        chpTextBuffer[iLetterCount+1] = '\0';
        iLetterCount++;
        CalculateSumCurPage();

      }
      iPressedKey = GetCharPressed();
    }

    if(IsKeyPressed(KEY_BACKSPACE)){

      iLetterCount--;
      if(iLetterCount < 0){
        iLetterCount = 0;
      }
      chpTextBuffer[iLetterCount] = '\0';
      CalculateSumCurPage();

    }

    if(IsKeyPressed(KEY_DOWN)){
      if(iIndexOfRow < 9){

        ResetInput();

        iIndexOfRow++;
        CalculateSumCurPage();
      }
    }

    if(IsKeyPressed(KEY_UP)){
      if(iIndexOfRow > 0){

        ResetInput();

        iIndexOfRow--;
        CalculateSumCurPage();
      }
    }

    if(IsKeyPressed(KEY_LEFT)){
      if(iIndexOfPage > 0){

        ResetInput();

        iIndexOfPage--;
        CalculateSumAll(true);
        CalculateSumCurPage();
      }
    }

    if(IsKeyPressed(KEY_RIGHT)){
      if(iIndexOfPage < ROWS-1){

        ResetInput();

        iIndexOfPage++;
        CalculateSumLastPage();
        CalculateSumAll(false);
        CalculateSumCurPage();
      }
    }

    chpIndexOfRow = malloc(sizeof(iIndexOfRow));
    sprintf(chpIndexOfRow, "%d", iIndexOfRow);

    DrawText(chpIndexOfRow, WWCENTER - (MeasureText(chpIndexOfRow,30) / 2), iPosyStart,30,BLACK);
    array[iIndexOfPage][iIndexOfRow] = chpTextBuffer;

// INPUT SECTION

    EndDrawing();

  }

  free(array);

  SaveProgress();
  CloseWindow();

  return 0;
}
