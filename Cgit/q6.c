#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct product{
    char num[50];
    char name[50];
    char price[50];
    
    int index_l;
    int num_l;
    int name_l;
    int price_l;
}pro;

int strcmp(const char *s1, const char *s2);
char *strcpy(char *s1, const char *s2);
int atoi(const char *str);

int GetCharByte(unsigned char* str);
void showResult(pro* result, int index, int numl, int namel, int pricel, int i);
void showSpace(int max, int myself);

int Maxlength(int maxLength, int myLength);
int IndexLength(int index);

int insert(pro* list, pro* insert, char insertList[][20], int iCount);
void update(pro* update, char upList[][20]);
int delete (pro* dl, char deleteList[][20], int i);


int indexL = 2; //NOの表示バイト
int numL = 10;  //コードの表示バイト
int nameL = 6;  //商品名の表示バイト
int priceL =4 ; //単価の表示バイト

int main() {
    FILE* fp;
    int i = 0;
    
    pro p[10];
    pro* list = p; 
    pro* head = p;
    pro* sw = p;
    
    
    //read csv
    if( (fp = fopen("test.csv","r")) == NULL ) {
        printf("not");
        exit(1);
    }
    
    //csvのデータを構造体に代入
    while( fscanf(fp, "%[^,],%[^,],%s%*c" ,list->num, list->name, list->price) != EOF ) {
        
        //一つ一つの構造体が自身の各コード、商品名、単価の桁数をもつ
      list->num_l = GetCharByte(list->num);
        numL = Maxlength(numL, list->num_l);
        
        list->name_l = GetCharByte(list->name);
        nameL = Maxlength(nameL, list->name_l);
        
        list->price_l = GetCharByte(list->price);
        priceL = Maxlength(priceL, list->price_l);

        list++;
        i++;
    }

    
    //--------------------------------------------
    //出力処理
    //--------------------------------------------
    showResult(sw, indexL, numL, nameL, priceL,i);
    
    fclose(fp);
    return 0;
}

int GetCharByte(unsigned char* str)
{
    int cnt = 0;
        int i = 0;
	for (i; str[i] != '\0'; ){ //ここでは増減処理[i++]は行わない
		if (str[i] >= 0x00 && str[i] <= 0x7F) { //1byte文字
                        i += 1; //1byte分進む
                        cnt += 1;
		} else if (str[i] >= 0xC0 && str[i] <= 0xDF) { //2byte文字
			i += 2; //2byte分進む
                        cnt += 2;
		} else if (str[i] >= 0xE0 && str[i] <= 0xEF) { //3byte文字
			i += 3; //3byte分進む
                        cnt += 2;
		} else if (str[i] >= 0xF0 && str[i] <= 0xF7) { //4byte文字
			i += 4; //4byte分進む
		} else if (str[i] >= 0xF8 && str[i] <= 0xFB) { //5byte文字
			i += 5; //5byte分進む                        
		} else if (str[i] >= 0xFC && str[i] <= 0xFD) { //6byte文字
			i += 6; //6byte分進む                    
		} else {
			i += 1; //該当なしの場合1byte分進む（無限ループ回避のため）
		}
	}
	return cnt;
}


void showResult(pro* result, int index, int numl, int namel, int pricel,int i)
{
    int loop = 0;
    int totalLength = index + numl + namel + pricel;
    for(loop = 0; loop < i + 1; loop++) {
        //ヘッダ表示
        if(loop == 0) {
            printf("NO");
            showSpace(index, 2);
            printf("|");

            printf("商品コード");  
            showSpace(numl,10);
            printf("|");

            printf("商品名");
            showSpace(namel,6);
            printf("|");

            showSpace(pricel, 4);
            printf("単価");
            printf("|\n");

            for(loop; loop < totalLength + 4; loop++ ){
                printf("-");
            }
            printf("\n");
            loop = 0;
        }
        else {
            //No表示
            printf("%d",loop);
            showSpace(index, IndexLength(loop));
            printf("|");

            //コード表示
            printf("%s",result->num);
            showSpace(numl, result->num_l);
            printf("|");

            //商品名表示
            printf("%s",result->name);
            showSpace(namel, result->name_l);
            printf("|");

            //単価表示(右揃え)
            showSpace(pricel, result->price_l);
            printf("%s",result->price);
            printf("|\n");
            
            result++;
        }   
    }
}

void showSpace(int max, int myself) 
{
    int iCount = max - myself;
    
    while (iCount != 0) {
        printf(" ");
        iCount--;
    }
}

int Maxlength(int maxLength, int myLength) {
    if(maxLength < myLength) {
        maxLength = myLength;
    }
    return maxLength;
}

int IndexLength(int index) {
    int cnt = 0;
    while(index != 0) {
        index = index / 10;
        cnt++;
    }
    return cnt;
}


